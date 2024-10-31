/*
 * QTest testcase for migration
 *
 * Copyright (c) 2016-2018 Red Hat, Inc. and/or its affiliates
 *   based on the vhost-user-test.c that is:
 *      Copyright (c) 2014 Virtual Open Systems Sarl.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#include "qemu/osdep.h"

#include "libqtest.h"
#include "qapi/qmp/qdict.h"
#include "qemu/module.h"
#include "qemu/option.h"
#include "qemu/range.h"
#include "qemu/sockets.h"
#include "chardev/char.h"
#include "crypto/tlscredspsk.h"
#include "qapi/qmp/qlist.h"
#include "ppc-util.h"

#include "migration-helpers.h"
#include "tests/migration/migration-test.h"
#ifdef CONFIG_GNUTLS
# include "tests/unit/crypto-tls-psk-helpers.h"
# ifdef CONFIG_TASN1
#  include "tests/unit/crypto-tls-x509-helpers.h"
# endif /* CONFIG_TASN1 */
#endif /* CONFIG_GNUTLS */

/* For dirty ring test; so far only x86_64 is supported */
#if defined(__linux__) && defined(HOST_X86_64)
#include "linux/kvm.h"
#endif

unsigned start_address;
unsigned end_address;
// static bool uffd_feature_thread_id;
static QTestMigrationState src_state;
static QTestMigrationState dst_state;

/*
 * An initial 3 MB offset is used as that corresponds
 * to ~1 sec of data transfer with our bandwidth setting.
 */
#define MAGIC_OFFSET_BASE (3 * 1024 * 1024)
/*
 * A further 1k is added to ensure we're not a multiple
 * of TEST_MEM_PAGE_SIZE, thus avoid clash with writes
 * from the migration guest workload.
 */
#define MAGIC_OFFSET_SHUFFLE 1024
#define MAGIC_OFFSET (MAGIC_OFFSET_BASE + MAGIC_OFFSET_SHUFFLE)
#define MAGIC_MARKER 0xFEED12345678CAFEULL

/*
 * Dirtylimit stop working if dirty page rate error
 * value less than DIRTYLIMIT_TOLERANCE_RANGE
 */
#define DIRTYLIMIT_TOLERANCE_RANGE  25  /* MB/s */

#define ANALYZE_SCRIPT "scripts/analyze-migration.py"
#define VMSTATE_CHECKER_SCRIPT "scripts/vmstate-static-checker.py"

#define QEMU_VM_FILE_MAGIC 0x5145564d
#define FILE_TEST_FILENAME "migfile"
#define FILE_TEST_OFFSET 0x1000
#define FILE_TEST_MARKER 'X'
#define QEMU_ENV_SRC "QTEST_QEMU_BINARY_SRC"
#define QEMU_ENV_DST "QTEST_QEMU_BINARY_DST"

typedef enum PostcopyRecoveryFailStage {
    /*
     * "no failure" must be 0 as it's the default.  OTOH, real failure
     * cases must be >0 to make sure they trigger by a "if" test.
     */
    POSTCOPY_FAIL_NONE = 0,
    POSTCOPY_FAIL_CHANNEL_ESTABLISH,
    POSTCOPY_FAIL_RECOVERY,
    POSTCOPY_FAIL_MAX
} PostcopyRecoveryFailStage;

#if defined(__linux__)
#include <sys/syscall.h>
#include <sys/vfs.h>
#endif

#if defined(__linux__) && defined(__NR_userfaultfd) && defined(CONFIG_EVENTFD)
#include <sys/eventfd.h>
#include <sys/ioctl.h>

#else
static bool ufd_version_check(void)
{
    g_test_message("Skipping test: Userfault not available (builtdtime)");
    return false;
}

#endif

static char *tmpfs;
static char *bootpath;

/* The boot file modifies memory area in [start_address, end_address)
 * repeatedly. It outputs a 'B' at a fixed rate while it's still running.
 */
#include "tests/migration/i386/a-b-bootblock.h"
#include "tests/migration/aarch64/a-b-kernel.h"
#include "tests/migration/ppc64/a-b-kernel.h"
#include "tests/migration/s390x/a-b-bios.h"

static void bootfile_delete(void)
{
    unlink(bootpath);
    g_free(bootpath);
    bootpath = NULL;
}

static void bootfile_create(char *dir, bool suspend_me)
{
    const char *arch = qtest_get_arch();
    unsigned char *content;
    size_t len;

    if (bootpath) {
        bootfile_delete();
    }

    bootpath = g_strdup_printf("%s/bootsect", dir);
    if (strcmp(arch, "i386") == 0 || strcmp(arch, "x86_64") == 0) {
        /* the assembled x86 boot sector should be exactly one sector large */
        g_assert(sizeof(x86_bootsect) == 512);
        x86_bootsect[SYM_suspend_me - SYM_start] = suspend_me;
        content = x86_bootsect;
        len = sizeof(x86_bootsect);
    } else if (g_str_equal(arch, "s390x")) {
        content = s390x_elf;
        len = sizeof(s390x_elf);
    } else if (strcmp(arch, "ppc64") == 0) {
        content = ppc64_kernel;
        len = sizeof(ppc64_kernel);
    } else if (strcmp(arch, "aarch64") == 0) {
        content = aarch64_kernel;
        len = sizeof(aarch64_kernel);
        g_assert(sizeof(aarch64_kernel) <= ARM_TEST_MAX_KERNEL_SIZE);
    } else {
        g_assert_not_reached();
    }

    FILE *bootfile = fopen(bootpath, "wb");

    g_assert_cmpint(fwrite(content, len, 1, bootfile), ==, 1);
    fclose(bootfile);
}

/*
 * Wait for some output in the serial output file,
 * we get an 'A' followed by an endless string of 'B's
 * but on the destination we won't have the A (unless we enabled suspend/resume)
 */
static void wait_for_serial(const char *side)
{
    g_autofree char *serialpath = g_strdup_printf("%s/%s", tmpfs, side);
    FILE *serialfile = fopen(serialpath, "r");

    do {
        int readvalue = fgetc(serialfile);

        switch (readvalue) {
        case 'A':
            /* Fine */
            break;

        case 'B':
            /* It's alive! */
            fclose(serialfile);
            return;

        case EOF:
            fseek(serialfile, 0, SEEK_SET);
            usleep(1000);
            break;

        default:
            fprintf(stderr, "Unexpected %d on %s serial\n", readvalue, side);
            g_assert_not_reached();
        }
    } while (true);
}

static void wait_for_stop(QTestState *who, QTestMigrationState *state)
{
    if (!state->stop_seen) {
        qtest_qmp_eventwait(who, "STOP");
    }
}

static void wait_for_resume(QTestState *who, QTestMigrationState *state)
{
    if (!state->resume_seen) {
        qtest_qmp_eventwait(who, "RESUME");
    }
}

static void check_guests_ram(QTestState *who)
{
    /* Our ASM test will have been incrementing one byte from each page from
     * start_address to < end_address in order. This gives us a constraint
     * that any page's byte should be equal or less than the previous pages
     * byte (mod 256); and they should all be equal except for one transition
     * at the point where we meet the incrementer. (We're running this with
     * the guest stopped).
     */
    unsigned address;
    uint8_t first_byte;
    uint8_t last_byte;
    bool hit_edge = false;
    int bad = 0;

    qtest_memread(who, start_address, &first_byte, 1);
    last_byte = first_byte;

    for (address = start_address + TEST_MEM_PAGE_SIZE; address < end_address;
         address += TEST_MEM_PAGE_SIZE)
    {
        uint8_t b;
        qtest_memread(who, address, &b, 1);
        if (b != last_byte) {
            if (((b + 1) % 256) == last_byte && !hit_edge) {
                /* This is OK, the guest stopped at the point of
                 * incrementing the previous page but didn't get
                 * to us yet.
                 */
                hit_edge = true;
                last_byte = b;
            } else {
                bad++;
                if (bad <= 10) {
                    fprintf(stderr, "Memory content inconsistency at %x"
                            " first_byte = %x last_byte = %x current = %x"
                            " hit_edge = %x\n",
                            address, first_byte, last_byte, b, hit_edge);
                }
            }
        }
    }
    if (bad >= 10) {
        fprintf(stderr, "and in another %d pages", bad - 10);
    }
    g_assert(bad == 0);
}

static void cleanup(const char *filename)
{
    g_autofree char *path = g_strdup_printf("%s/%s", tmpfs, filename);

    unlink(path);
}

static long long migrate_get_parameter_int(QTestState *who,
                                           const char *parameter)
{
    QDict *rsp;
    long long result;

    rsp = qtest_qmp_assert_success_ref(
        who, "{ 'execute': 'query-migrate-parameters' }");
    result = qdict_get_int(rsp, parameter);
    qobject_unref(rsp);
    return result;
}

static void migrate_check_parameter_int(QTestState *who, const char *parameter,
                                        long long value)
{
    long long result;

    result = migrate_get_parameter_int(who, parameter);
    g_assert_cmpint(result, ==, value);
}

static void migrate_set_parameter_int(QTestState *who, const char *parameter,
                                      long long value)
{
    qtest_qmp_assert_success(who,
                             "{ 'execute': 'migrate-set-parameters',"
                             "'arguments': { %s: %lld } }",
                             parameter, value);
    migrate_check_parameter_int(who, parameter, value);
}

// static char *migrate_get_parameter_str(QTestState *who,
//                                        const char *parameter)
// {
//     QDict *rsp;
//     char *result;

//     rsp = qtest_qmp_assert_success_ref(
//         who, "{ 'execute': 'query-migrate-parameters' }");
//     result = g_strdup(qdict_get_str(rsp, parameter));
//     qobject_unref(rsp);
//     return result;
// }

static void migrate_ensure_converge(QTestState *who)
{
    /* Should converge with 30s downtime + 1 gbs bandwidth limit */
    migrate_set_parameter_int(who, "max-bandwidth", 1 * 1000 * 1000 * 1000);
    migrate_set_parameter_int(who, "downtime-limit", 30 * 1000);
}

// static void migrate_pause(QTestState *who)
// {
//     qtest_qmp_assert_success(who, "{ 'execute': 'migrate-pause' }");
// }

// static void migrate_continue(QTestState *who, const char *state)
// {
//     qtest_qmp_assert_success(who,
//                              "{ 'execute': 'migrate-continue',"
//                              "  'arguments': { 'state': %s } }",
//                              state);
// }

// static void migrate_recover(QTestState *who, const char *uri)
// {
//     qtest_qmp_assert_success(who,
//                              "{ 'execute': 'migrate-recover', "
//                              "  'id': 'recover-cmd', "
//                              "  'arguments': { 'uri': %s } }",
//                              uri);
// }

// static void migrate_cancel(QTestState *who)
// {
//     qtest_qmp_assert_success(who, "{ 'execute': 'migrate_cancel' }");
// }

typedef struct {
    /*
     * QTEST_LOG=1 may override this.  When QTEST_LOG=1, we always dump errors
     * unconditionally, because it means the user would like to be verbose.
     */
    bool hide_stderr;
    bool use_shmem;
    /* only launch the target process */
    bool only_target;
    /* Use dirty ring if true; dirty logging otherwise */
    bool use_dirty_ring;
    const char *opts_source;
    const char *opts_target;
    /* suspend the src before migrating to dest. */
    bool suspend_me;
} MigrateStart;

/*
 * A hook that runs after the src and dst QEMUs have been
 * created, but before the migration is started. This can
 * be used to set migration parameters and capabilities.
 *
 * Returns: NULL, or a pointer to opaque state to be
 *          later passed to the TestMigrateFinishHook
 */
typedef void * (*TestMigrateStartHook)(QTestState *from,
                                       QTestState *to);

/*
 * A hook that runs after the migration has finished,
 * regardless of whether it succeeded or failed, but
 * before QEMU has terminated (unless it self-terminated
 * due to migration error)
 *
 * @opaque is a pointer to state previously returned
 * by the TestMigrateStartHook if any, or NULL.
 */
typedef void (*TestMigrateFinishHook)(QTestState *from,
                                      QTestState *to,
                                      void *opaque);

typedef struct {
    /* Optional: fine tune start parameters */
    MigrateStart start;

    /* Required: the URI for the dst QEMU to listen on */
    const char *listen_uri;

    /*
     * Optional: the URI for the src QEMU to connect to
     * If NULL, then it will query the dst QEMU for its actual
     * listening address and use that as the connect address.
     * This allows for dynamically picking a free TCP port.
     */
    const char *connect_uri;

    /*
     * Optional: JSON-formatted list of src QEMU URIs. If a port is
     * defined as '0' in any QDict key a value of '0' will be
     * automatically converted to the correct destination port.
     */
    const char *connect_channels;

    /* Optional: callback to run at start to set migration parameters */
    TestMigrateStartHook start_hook;
    /* Optional: callback to run at finish to cleanup */
    TestMigrateFinishHook finish_hook;

    /*
     * Optional: normally we expect the migration process to complete.
     *
     * There can be a variety of reasons and stages in which failure
     * can happen during tests.
     *
     * If a failure is expected to happen at time of establishing
     * the connection, then MIG_TEST_FAIL will indicate that the dst
     * QEMU is expected to stay running and accept future migration
     * connections.
     *
     * If a failure is expected to happen while processing the
     * migration stream, then MIG_TEST_FAIL_DEST_QUIT_ERR will indicate
     * that the dst QEMU is expected to quit with non-zero exit status
     */
    enum {
        /* This test should succeed, the default */
        MIG_TEST_SUCCEED = 0,
        /* This test should fail, dest qemu should keep alive */
        MIG_TEST_FAIL,
        /* This test should fail, dest qemu should fail with abnormal status */
        MIG_TEST_FAIL_DEST_QUIT_ERR,
        /* The QMP command for this migration should fail with an error */
        MIG_TEST_QMP_ERROR,
    } result;

    /*
     * Optional: set number of migration passes to wait for, if live==true.
     * If zero, then merely wait for a few MB of dirty data
     */
    unsigned int iterations;

    /*
     * Optional: whether the guest CPUs should be running during a precopy
     * migration test.  We used to always run with live but it took much
     * longer so we reduced live tests to only the ones that have solid
     * reason to be tested live-only.  For each of the new test cases for
     * precopy please provide justifications to use live explicitly (please
     * refer to existing ones with live=true), or use live=off by default.
     */
    bool live;

    /* Postcopy specific fields */
    void *postcopy_data;
    bool postcopy_preempt;
    PostcopyRecoveryFailStage postcopy_recovery_fail_stage;
} MigrateCommon;

static int test_migrate_start(QTestState **from, QTestState **to,
                              const char *uri, MigrateStart *args)
{
    g_autofree gchar *arch_source = NULL;
    g_autofree gchar *arch_target = NULL;
    /* options for source and target */
    g_autofree gchar *arch_opts = NULL;
    g_autofree gchar *cmd_source = NULL;
    g_autofree gchar *cmd_target = NULL;
    const gchar *ignore_stderr;
    g_autofree char *shmem_opts = NULL;
    g_autofree char *shmem_path = NULL;
    const char *kvm_opts = NULL;
    const char *arch = qtest_get_arch();
    const char *memory_size;
    const char *machine_alias, *machine_opts = "";
    g_autofree char *machine = NULL;

    if (args->use_shmem) {
        if (!g_file_test("/dev/shm", G_FILE_TEST_IS_DIR)) {
            g_test_skip("/dev/shm is not supported");
            return -1;
        }
    }

    dst_state = (QTestMigrationState) { };
    src_state = (QTestMigrationState) { };
    bootfile_create(tmpfs, args->suspend_me);
    src_state.suspend_me = args->suspend_me;

    if (strcmp(arch, "i386") == 0 || strcmp(arch, "x86_64") == 0) {
        memory_size = "150M";

        if (g_str_equal(arch, "i386")) {
            machine_alias = "pc";
        } else {
            machine_alias = "q35";
        }
        arch_opts = g_strdup_printf(
            "-drive if=none,id=d0,file=%s,format=raw "
            "-device ide-hd,drive=d0,secs=1,cyls=1,heads=1", bootpath);
        start_address = X86_TEST_MEM_START;
        end_address = X86_TEST_MEM_END;
    } else if (g_str_equal(arch, "s390x")) {
        memory_size = "128M";
        machine_alias = "s390-ccw-virtio";
        arch_opts = g_strdup_printf("-bios %s", bootpath);
        start_address = S390_TEST_MEM_START;
        end_address = S390_TEST_MEM_END;
    } else if (strcmp(arch, "ppc64") == 0) {
        memory_size = "256M";
        start_address = PPC_TEST_MEM_START;
        end_address = PPC_TEST_MEM_END;
        machine_alias = "pseries";
        machine_opts = "vsmt=8";
        arch_opts = g_strdup_printf(
            "-nodefaults -machine " PSERIES_DEFAULT_CAPABILITIES " "
            "-bios %s", bootpath);
    } else if (strcmp(arch, "aarch64") == 0) {
        memory_size = "150M";
        machine_alias = "virt";
        machine_opts = "gic-version=3";
        arch_opts = g_strdup_printf("-cpu max -kernel %s", bootpath);
        start_address = ARM_TEST_MEM_START;
        end_address = ARM_TEST_MEM_END;
    } else {
        g_assert_not_reached();
    }

    if (!getenv("QTEST_LOG") && args->hide_stderr) {
#ifndef _WIN32
        ignore_stderr = "2>/dev/null";
#else
        /*
         * On Windows the QEMU executable is created via CreateProcess() and
         * IO redirection does not work, so don't bother adding IO redirection
         * to the command line.
         */
        ignore_stderr = "";
#endif
    } else {
        ignore_stderr = "";
    }

    if (args->use_shmem) {
        shmem_path = g_strdup_printf("/dev/shm/qemu-%d", getpid());
        shmem_opts = g_strdup_printf(
            "-object memory-backend-file,id=mem0,size=%s"
            ",mem-path=%s,share=on -numa node,memdev=mem0",
            memory_size, shmem_path);
    }

    if (args->use_dirty_ring) {
        kvm_opts = ",dirty-ring-size=4096";
    }

    if (!qtest_has_machine(machine_alias)) {
        g_autofree char *msg = g_strdup_printf("machine %s not supported", machine_alias);
        g_test_skip(msg);
        return -1;
    }

    machine = resolve_machine_version(machine_alias, QEMU_ENV_SRC,
                                      QEMU_ENV_DST);

    g_test_message("Using machine type: %s", machine);

    cmd_source = g_strdup_printf("-accel kvm%s -accel tcg "
                                 "-machine %s,%s "
                                 "-name source,debug-threads=on "
                                 "-m %s "
                                 "-serial file:%s/src_serial "
                                 "%s %s %s %s %s",
                                 kvm_opts ? kvm_opts : "",
                                 machine, machine_opts,
                                 memory_size, tmpfs,
                                 arch_opts ? arch_opts : "",
                                 arch_source ? arch_source : "",
                                 shmem_opts ? shmem_opts : "",
                                 args->opts_source ? args->opts_source : "",
                                 ignore_stderr);
    if (!args->only_target) {
        *from = qtest_init_with_env(QEMU_ENV_SRC, cmd_source);
        qtest_qmp_set_event_callback(*from,
                                     migrate_watch_for_events,
                                     &src_state);
    }

    cmd_target = g_strdup_printf("-accel kvm%s -accel tcg "
                                 "-machine %s,%s "
                                 "-name target,debug-threads=on "
                                 "-m %s "
                                 "-serial file:%s/dest_serial "
                                 "-incoming %s "
                                 "%s %s %s %s %s",
                                 kvm_opts ? kvm_opts : "",
                                 machine, machine_opts,
                                 memory_size, tmpfs, uri,
                                 arch_opts ? arch_opts : "",
                                 arch_target ? arch_target : "",
                                 shmem_opts ? shmem_opts : "",
                                 args->opts_target ? args->opts_target : "",
                                 ignore_stderr);
    *to = qtest_init_with_env(QEMU_ENV_DST, cmd_target);
    qtest_qmp_set_event_callback(*to,
                                 migrate_watch_for_events,
                                 &dst_state);

    /*
     * Remove shmem file immediately to avoid memory leak in test failed case.
     * It's valid because QEMU has already opened this file
     */
    if (args->use_shmem) {
        unlink(shmem_path);
    }

    /*
     * Always enable migration events.  Libvirt always uses it, let's try
     * to mimic as closer as that.
     */
    migrate_set_capability(*from, "events", true);
    migrate_set_capability(*to, "events", true);

    return 0;
}

static void test_migrate_end(QTestState *from, QTestState *to, bool test_dest)
{
    unsigned char dest_byte_a, dest_byte_b, dest_byte_c, dest_byte_d;

    qtest_quit(from);

    if (test_dest) {
        qtest_memread(to, start_address, &dest_byte_a, 1);

        /* Destination still running, wait for a byte to change */
        do {
            qtest_memread(to, start_address, &dest_byte_b, 1);
            usleep(1000 * 10);
        } while (dest_byte_a == dest_byte_b);

        qtest_qmp_assert_success(to, "{ 'execute' : 'stop'}");

        /* With it stopped, check nothing changes */
        qtest_memread(to, start_address, &dest_byte_c, 1);
        usleep(1000 * 200);
        qtest_memread(to, start_address, &dest_byte_d, 1);
        g_assert_cmpint(dest_byte_c, ==, dest_byte_d);

        check_guests_ram(to);
    }

    qtest_quit(to);

    cleanup("migsocket");
    cleanup("src_serial");
    cleanup("dest_serial");
    cleanup(FILE_TEST_FILENAME);
}

static void file_dirty_offset_region(void)
{
    g_autofree char *path = g_strdup_printf("%s/%s", tmpfs, FILE_TEST_FILENAME);
    size_t size = FILE_TEST_OFFSET;
    g_autofree char *data = g_new0(char, size);

    memset(data, FILE_TEST_MARKER, size);
    g_assert(g_file_set_contents(path, data, size, NULL));
}

static void file_check_offset_region(void)
{
    g_autofree char *path = g_strdup_printf("%s/%s", tmpfs, FILE_TEST_FILENAME);
    size_t size = FILE_TEST_OFFSET;
    g_autofree char *expected = g_new0(char, size);
    g_autofree char *actual = NULL;
    uint64_t *stream_start;

    /*
     * Ensure the skipped offset region's data has not been touched
     * and the migration stream starts at the right place.
     */

    memset(expected, FILE_TEST_MARKER, size);

    g_assert(g_file_get_contents(path, &actual, NULL, NULL));
    g_assert(!memcmp(actual, expected, size));

    stream_start = (uint64_t *)(actual + size);
    g_assert_cmpint(cpu_to_be64(*stream_start) >> 32, ==, QEMU_VM_FILE_MAGIC);
}

static void test_file_common(MigrateCommon *args, bool stop_src)
{
    QTestState *from, *to;
    void *data_hook = NULL;
    bool check_offset = false;

    if (test_migrate_start(&from, &to, args->listen_uri, &args->start)) {
        return;
    }

    /*
     * File migration is never live. We can keep the source VM running
     * during migration, but the destination will not be running
     * concurrently.
     */
    g_assert_false(args->live);

    if (g_strrstr(args->connect_uri, "offset=")) {
        check_offset = true;
        /*
         * This comes before the start_hook because it's equivalent to
         * a management application creating the file and writing to
         * it so hooks should expect the file to be already present.
         */
        file_dirty_offset_region();
    }

    if (args->start_hook) {
        data_hook = args->start_hook(from, to);
    }

    migrate_ensure_converge(from);
    wait_for_serial("src_serial");

    if (stop_src) {
        qtest_qmp_assert_success(from, "{ 'execute' : 'stop'}");
        wait_for_stop(from, &src_state);
    }

    if (args->result == MIG_TEST_QMP_ERROR) {
        migrate_qmp_fail(from, args->connect_uri, NULL, "{}");
        goto finish;
    }

    migrate_qmp(from, to, args->connect_uri, NULL, "{}");
    wait_for_migration_complete(from);

    /*
     * We need to wait for the source to finish before starting the
     * destination.
     */
    migrate_incoming_qmp(to, args->connect_uri, "{}");
    wait_for_migration_complete(to);

    if (stop_src) {
        qtest_qmp_assert_success(to, "{ 'execute' : 'cont'}");
    }
    wait_for_resume(to, &dst_state);

    wait_for_serial("dest_serial");

    if (check_offset) {
        file_check_offset_region();
    }

finish:
    if (args->finish_hook) {
        args->finish_hook(from, to, data_hook);
    }

    test_migrate_end(from, to, args->result == MIG_TEST_SUCCEED);
}

// static void *test_migrate_fd_start_hook(QTestState *from,
//                                         QTestState *to)
// {
//     int ret;
//     int pair[2];

//     /* Create two connected sockets for migration */
//     ret = qemu_socketpair(PF_LOCAL, SOCK_STREAM, 0, pair);
//     g_assert_cmpint(ret, ==, 0);

//     /* Send the 1st socket to the target */
//     qtest_qmp_fds_assert_success(to, &pair[0], 1,
//                                  "{ 'execute': 'getfd',"
//                                  "  'arguments': { 'fdname': 'fd-mig' }}");
//     close(pair[0]);

//     /* Start incoming migration from the 1st socket */
//     migrate_incoming_qmp(to, "fd:fd-mig", "{}");

//     /* Send the 2nd socket to the target */
//     qtest_qmp_fds_assert_success(from, &pair[1], 1,
//                                  "{ 'execute': 'getfd',"
//                                  "  'arguments': { 'fdname': 'fd-mig' }}");
//     close(pair[1]);

//     return NULL;
// }

static void test_migrate_fd_finish_hook(QTestState *from,
                                        QTestState *to,
                                        void *opaque)
{
    QDict *rsp;
    const char *error_desc;

    /* Test closing fds */
    /* We assume, that QEMU removes named fd from its list,
     * so this should fail */
    rsp = qtest_qmp(from, "{ 'execute': 'closefd',"
                          "  'arguments': { 'fdname': 'fd-mig' }}");
    g_assert_true(qdict_haskey(rsp, "error"));
    error_desc = qdict_get_str(qdict_get_qdict(rsp, "error"), "desc");
    g_assert_cmpstr(error_desc, ==, "File descriptor named 'fd-mig' not found");
    qobject_unref(rsp);

    rsp = qtest_qmp(to, "{ 'execute': 'closefd',"
                        "  'arguments': { 'fdname': 'fd-mig' }}");
    g_assert_true(qdict_haskey(rsp, "error"));
    error_desc = qdict_get_str(qdict_get_qdict(rsp, "error"), "desc");
    g_assert_cmpstr(error_desc, ==, "File descriptor named 'fd-mig' not found");
    qobject_unref(rsp);
}

static void *migrate_precopy_fd_file_start(QTestState *from, QTestState *to)
{
    g_autofree char *file = g_strdup_printf("%s/%s", tmpfs, FILE_TEST_FILENAME);
    int src_flags = O_CREAT | O_RDWR;
    int dst_flags = O_CREAT | O_RDWR;
    int fds[2];

    fds[0] = open(file, src_flags, 0660);
    assert(fds[0] != -1);

    fds[1] = open(file, dst_flags, 0660);
    assert(fds[1] != -1);


    qtest_qmp_fds_assert_success(to, &fds[0], 1,
                                 "{ 'execute': 'getfd',"
                                 "  'arguments': { 'fdname': 'fd-mig' }}");

    qtest_qmp_fds_assert_success(from, &fds[1], 1,
                                 "{ 'execute': 'getfd',"
                                 "  'arguments': { 'fdname': 'fd-mig' }}");

    close(fds[0]);
    close(fds[1]);

    return NULL;
}

static void test_migrate_precopy_fd_file(void)
{
    MigrateCommon args = {
        .listen_uri = "defer",
        .connect_uri = "fd:fd-mig",
        .start_hook = migrate_precopy_fd_file_start,
        .finish_hook = test_migrate_fd_finish_hook
    };
    test_file_common(&args, true);
}

int main(int argc, char **argv)
{
    bool has_kvm, has_tcg;
    // bool has_uffd, is_x86;
    // const char *arch;
    g_autoptr(GError) err = NULL;
    const char *qemu_src = getenv(QEMU_ENV_SRC);
    const char *qemu_dst = getenv(QEMU_ENV_DST);
    int ret;

    g_test_init(&argc, &argv, NULL);

    /*
     * The default QTEST_QEMU_BINARY must always be provided because
     * that is what helpers use to query the accel type and
     * architecture.
     */
    if (qemu_src && qemu_dst) {
        g_test_message("Only one of %s, %s is allowed",
                       QEMU_ENV_SRC, QEMU_ENV_DST);
        exit(1);
    }

    has_kvm = qtest_has_accel("kvm");
    has_tcg = qtest_has_accel("tcg");

    if (!has_tcg && !has_kvm) {
        g_test_skip("No KVM or TCG accelerator available");
        return 0;
    }

    // has_uffd = ufd_version_check();
    // arch = qtest_get_arch();
    // is_x86 = !strcmp(arch, "i386") || !strcmp(arch, "x86_64");

    tmpfs = g_dir_make_tmp("migration-test-XXXXXX", &err);
    if (!tmpfs) {
        g_test_message("Can't create temporary directory in %s: %s",
                       g_get_tmp_dir(), err->message);
    }
    g_assert(tmpfs);

    module_call_init(MODULE_INIT_QOM);

    migration_test_add("/migration/precopy/fd/file",
                    test_migrate_precopy_fd_file);

    // TODO: refer: migrate precopy file, use file: instead of fd:

    ret = g_test_run();

    g_assert_cmpint(ret, ==, 0);

    bootfile_delete();
    ret = rmdir(tmpfs);
    if (ret != 0) {
        g_test_message("unable to rmdir: path (%s): %s",
                       tmpfs, strerror(errno));
    }
    g_free(tmpfs);

    return ret;
}
