#include "utils.h"
#include "qemu/osdep.h"
#include "tests/qtest/libqtest-single.h"

static int sockfds[2];
static bool sockfds_initialized;

// set opts to a new QDict
QDict *parse_opts(GString *opt_str)
{
    char *opt = g_strdup(opt_str->str);
    char *saveptr;
    char *token = strtok_r(opt, ",", &saveptr);
    QDict *opt_dict = qdict_new();

    while (token) {
        char *key = g_strdup(token);
        char *value = strchr(key, '=');
        if (value) {
            *value = '\0';
            value++;
            qdict_put_str(opt_dict, key, value);
        }
        g_free(key);
        token = strtok_r(NULL, ",", &saveptr);
    }
    g_free(opt);
    return opt_dict;
}

// qdict put helper functions

void qdict_put_bool_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    if (value) {
        qdict_put_str(qdict, key, "on");
    } else {
        qdict_put_str(qdict, key, "off");
    }
}

void qdict_put_int8_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    char buf[10];
    int8_t val = *(int8_t *)value;
    val &= 0x7F;    // avoid negative values
	// qdict_put_int(qdict, key, val);
    sprintf(buf, "%hhd", val);
    qdict_put_str(qdict, key, buf);
}

void qdict_put_int16_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    char buf[10];
    int16_t val = *(int16_t *)value;
    val &= 0x7FFF;    // avoid negative values
	// qdict_put_int(qdict, key, val);
    sprintf(buf, "%hd", val);
    qdict_put_str(qdict, key, buf);
}

void qdict_put_int32_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    char buf[20];
    int32_t val = *(int32_t *)value;
    val &= 0x7FFFFFFF;    // avoid negative values
	// qdict_put_int(qdict, key, val);
    sprintf(buf, "%d", val);
    qdict_put_str(qdict, key, buf);
}

// Qemu Device Graph Test Options

void *net_test_setup_socket(GString *cmd_line, void *arg)
{
	int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sockfds);
    g_assert_cmpint(ret, !=, -1);
    g_unix_set_fd_nonblocking(sockfds[0], true, NULL);
    sockfds_initialized = true;
    g_string_append_printf(cmd_line, " -netdev socket,fd=%d,id=hs0 ",
                           sockfds[1]);
    return arg;
}

#define TEST_IMAGE_SIZE         (64 * 1024 * 1024)

static void drive_destroy(void *path)
{
    unlink(path);
    g_free(path);
}

static char *drive_create(void)
{
    int fd, ret;
    char *t_path;

    /* Create a temporary raw image */
    fd = g_file_open_tmp("qtest.XXXXXX", &t_path, NULL);
    g_assert_cmpint(fd, >=, 0);
    ret = ftruncate(fd, TEST_IMAGE_SIZE);
    g_assert_cmpint(ret, ==, 0);
    close(fd);

    g_test_queue_destroy(drive_destroy, t_path);
    return t_path;
}

void *virtio_blk_test_setup(GString *cmd_line, void *arg)
{
    char *tmp_path = drive_create();

    g_string_append_printf(cmd_line,
                           " -drive if=none,id=drive0,file=%s,"
                           "format=raw,auto-read-only=off ",
                           tmp_path);

    return arg;
}

void *virtio_scsi_test_setup(GString *cmd_line, void *arg)
{
    g_string_append(cmd_line,
                    " -drive file=blkdebug::null-co://,"
                    "file.image.read-zeroes=on,"
                    "if=none,id=dr1,format=raw,file.align=4k "
                    "-device scsi-hd,drive=dr1,lun=0,scsi-id=1");
    return arg;
}

void *igb_test_setup_no_socket(GString *cmd_line, void *arg)
{
    g_string_append(cmd_line, " -netdev hubport,hubid=0,id=hs0 ");
    return arg;
}

// for dependency of generic driver nodes
void qos_invalidate_command_line(void)
{
    return;
}

// For qgraph node creation
void *dumb_get_driver(void *obj, const char *interface)
{
    return NULL;
}

void dumb_start_hw(QOSGraphObject *obj)
{
    return;
}

void dumb_pci_start_hw(QOSGraphObject *obj)
{
    GENERIC_PCI_DEVICE *d = (GENERIC_PCI_DEVICE *) obj;

    qpci_device_enable(&d->pci_dev);
}

void dumb_destructor(QOSGraphObject *obj)
{
    return;
}

void *generic_pci_create(void *pci_bus, QGuestAllocator *alloc, void *addr)
{
    GENERIC_PCI_DEVICE *d = g_new0(GENERIC_PCI_DEVICE, 1);
    QPCIBus *bus = pci_bus;
    QPCIAddress *address = addr;

    qpci_device_init(&d->pci_dev, bus, address);
    
    d->obj.get_driver = dumb_get_driver;
    d->obj.start_hw = dumb_pci_start_hw;
    d->obj.destructor = dumb_destructor;

    return &d->obj;
}

void *generic_create(void *pci_bus, QGuestAllocator *alloc, void *addr)
{
    GENERIC_DEVICE *d = g_new0(GENERIC_DEVICE, 1);
    d->obj.get_driver = dumb_get_driver;
    d->obj.start_hw = dumb_start_hw;
    d->obj.destructor = dumb_destructor;
    return &d->obj;
}