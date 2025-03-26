/*
 * QOS-assisted fuzzing helpers
 *
 * Copyright (c) 2018 Emanuele Giuseppe Esposito <e.emanuelegiuseppe@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>
 */

#include "qemu/osdep.h"
#include "qemu/units.h"
#include "qapi/error.h"
#include "exec/memory.h"
#include "qemu/main-loop.h"
#include "monitor/qdev.h"

#include "tests/qtest/libqtest.h"
#include "tests/qtest/libqos/libqos-malloc.h"
#include "tests/qtest/libqos/qgraph.h"
#include "tests/qtest/libqos/qgraph_internal.h"
#include "tests/qtest/libqos/qos_external.h"

#include "qos_prop_fuzz.h"
#include "utils.h"

#include "qapi/qapi-commands-machine.h"
#include "qapi/qapi-commands-qom.h"


static const char *fuzz_target_name;
static char **fuzz_path_vec;

static bool verbose = false;

// For device property
static char* fuzz_driver;
static char* fuzz_device_cmdline;
static QDict* fuzz_device_extraopt;
static void* fuzz_edge_arg;

typedef struct {
    char *name;
    PropTypeEnum type;
} FuzzProp;

static FuzzProp *prop_list;
static int prop_list_size;

static PropType prop_type[] = {
    [PROP_TYPE_BOOL] = {
        .size = sizeof(bool),
        .qdict_put_handler = qdict_put_bool_buf,
    },
    [PROP_TYPE_INT8] = {
        .size = sizeof(int8_t),
        .qdict_put_handler = qdict_put_int8_buf,
    },
    [PROP_TYPE_INT16] = {
        .size = sizeof(int16_t),
        .qdict_put_handler = qdict_put_int16_buf,
    },
    [PROP_TYPE_INT32] = {
        .size = sizeof(int32_t),
        .qdict_put_handler = qdict_put_int32_buf,
    },

};

#define qdict_put_generic(qdict, key, value) _Generic((value), \
    bool: qdict_put_bool, \
    int8_t: qdict_put_int, \
    int16_t: qdict_put_int, \
    int32_t: qdict_put_int) \
    (qdict, key, value)

static void init_prop_list(void)
{
    const char *prop_name_file;
    prop_name_file = (const char *)g_getenv("PROP_FILE");
    if (!prop_name_file) {  // set to default value
        prop_name_file = "prop_list.txt";
    }

    FILE *prop_file = fopen(prop_name_file, "r");
    if (!prop_file) {
        fprintf(stderr, "Error opening file %s\n", prop_name_file);
        abort();
    }

    fscanf(prop_file, "%d\n", &prop_list_size);
    prop_list = g_new0(FuzzProp, prop_list_size);
    bool valid = true;
    for (int i = 0; i < prop_list_size; i++) {
        if (valid)
            prop_list[i].name = g_new0(char, 64);
        fscanf(prop_file, "%63s %d\n", prop_list[i].name, &prop_list[i].type);
        if (qdict_haskey(fuzz_device_extraopt, prop_list[i].name)) {
            valid = false;
            i--; prop_list_size--;
            continue;
        }
        valid = true;
    }

    fclose(prop_file);
}

static GString *qos_prop_build_main_args(void)
{
    char **path = fuzz_path_vec;
    QOSGraphNode *test_node;
    GString *cmd_line;
    void *test_arg;

    if (!path) {
        fprintf(stderr, "QOS Path not found\n");
        abort();
    }

    init_prop_list();

    /* Before test */
    cmd_line = g_string_new(path[0]);
    current_path = path;
    test_node = qos_graph_get_node(path[(g_strv_length(path) - 1)]);
    test_arg = test_node->u.test.arg;
    if (test_node->u.test.before) {
        test_arg = test_node->u.test.before(cmd_line, test_arg);
    }
    /* Prepend the arguments that we need */
    g_string_prepend(cmd_line,
            TARGET_NAME " -display none -machine accel=qtest -m 64 ");
    printf("Starting with cmdline: %s\n", cmd_line->str);
    return cmd_line;
}

/*
 * This function is largely a copy of qos-test.c:walk_path. Since walk_path
 * is itself a callback, its a little annoying to add another argument/layer of
 * indirection
 */
static int walk_path(QOSGraphNode *orig_path, int len)
{
    // For enumerate device nodes
    // return 0;

    QOSGraphNode *path;
    QOSGraphEdge *edge;

    /*
     * etype set to QEDGE_CONSUMED_BY so that machine can add to the command
     * line
     */
    QOSEdgeType etype = QEDGE_CONSUMED_BY;

    char *after_cmd, *before_cmd, *after_device;
    char *node_name = orig_path->name, *path_str;

    /* Check that this is the test we care about: */
    char* edge_name;
    path = qos_graph_get_node(node_name); /* root */
    while (path->path_edge) {
        edge_name = qos_graph_edge_get_name(path->path_edge);
        node_name = qos_graph_edge_get_dest(path->path_edge);
        path = qos_graph_get_node(node_name);
    }
    char* test_name = strrchr(edge_name, '/') + 1;
    if (strcmp(test_name, fuzz_target_name) != 0) {
        return 0;
    }

    path = qos_graph_get_node(orig_path->name); /* root */
    node_name = qos_graph_edge_get_dest(path->path_edge); /* machine name */

    /* twice QOS_PATH_MAX_ELEMENT_SIZE since each edge can have its arg */
    char **path_vec = g_new0(char *, (QOS_PATH_MAX_ELEMENT_SIZE * 2));
    int path_vec_size = 0;

    GString *cmd_line = g_string_new("");
    GString *cmd_line2 = g_string_new("");
    GString *after_device_str = g_string_new("");

    path_vec[path_vec_size++] = node_name;
    path_vec[path_vec_size++] = qos_get_machine_type(node_name);

    for (int depth = 2; ; depth++) {
        path = qos_graph_get_node(node_name);
        if (!path->path_edge) {
            break;
        }

        node_name = qos_graph_edge_get_dest(path->path_edge);

        /* append node command line + previous edge command line */
        if (path->command_line && etype == QEDGE_CONSUMED_BY) {
            if (depth == len) { // current node is the device under test
                fuzz_driver = g_strdup(path->name);
                fuzz_device_cmdline = g_strdup(path->command_line);
                fuzz_device_extraopt = parse_opts(after_device_str);
                fuzz_edge_arg = qos_graph_edge_get_arg(edge);
            } else {
                g_string_append(cmd_line, path->command_line);
                g_string_append(cmd_line, after_device_str->str);
            }
            g_string_truncate(after_device_str, 0);
        }

        path_vec[path_vec_size++] = qos_graph_edge_get_name(path->path_edge);
        /* detect if edge has command line args */
        if (depth < len - 1) {  // device under test node cannot add after_cmd devices, dependency occurred
            after_cmd = qos_graph_edge_get_after_cmd_line(path->path_edge);
        }
        after_device = qos_graph_edge_get_extra_device_opts(path->path_edge);
        before_cmd = qos_graph_edge_get_before_cmd_line(path->path_edge);
        edge = qos_graph_get_edge(path->name, node_name);
        etype = qos_graph_edge_get_type(edge);

        if (before_cmd) {
            g_string_append(cmd_line, before_cmd);
        }
        if (after_cmd) {
            g_string_append(cmd_line2, after_cmd);
        }
        if (after_device) {
            g_string_append(after_device_str, after_device);
        }
    }

    path_vec[path_vec_size++] = NULL;
    g_string_append(cmd_line, after_device_str->str);
    g_string_free(after_device_str, true);

    g_string_append(cmd_line, cmd_line2->str);
    g_string_free(cmd_line2, true);

    // Debug print
    // printf("%s: %s\n", test_name, cmd_line->str);
    // if (fuzz_device_cmdline) {
    //     printf("%s\n%s\n", fuzz_device_cmdline, fuzz_device_extraopt);
    //     g_free(fuzz_device_cmdline);
    //     g_free(fuzz_device_extraopt);
    //     fuzz_device_cmdline = fuzz_device_extraopt = NULL;
    // } else {
    //     printf("null\n");
    // }

    /*
     * here position 0 has <arch>/<machine>, position 1 has <machine>.
     * The path must not have the <arch>, qtest_add_data_func adds it.
     */
    path_str = g_strjoinv("/", path_vec + 1);

    /*
    * put arch/machine in position 1 so run_one_test can do its work
    * and add the command line at position 0.
    */
    path_vec[1] = path_vec[0];
    path_vec[0] = g_string_free(cmd_line, false);

    fuzz_path_vec = path_vec;
    
    if (verbose) {
        printf("Starting with cmdline: %s\n", path_vec[0]);
    }

    g_free(path_str);
    return 1;
}

static GString *qos_prop_get_cmdline(FuzzTarget *t)
{
    // some extra initialization
    if (g_getenv("VERBOSE")) {
        verbose = true;
    }
    /*
     * Set a global variable that we use to identify the qos_path for our
     * fuzz_target
     */
    fuzz_target_name = t->name;
    qos_set_machines_devices_available();
    qos_graph_foreach_test_path(walk_path);
    return qos_prop_build_main_args();
}

void fuzz_add_qos_prop_target(
        FuzzTarget *fuzz_opts,
        const char *interface,
        QOSGraphTestOptions *opts
        )
{
    qos_add_test(fuzz_opts->name, interface, NULL, opts);
    fuzz_opts->get_init_cmdline = qos_prop_get_cmdline;
    fuzz_add_target(fuzz_opts);
}

void prop_fuzz(QTestState *s,
        const unsigned char *Data, size_t Size)
{
    // for debug
    // Size = 3;
    // Data = (unsigned char*)"\x30\x11\x0a";

    if (verbose) {
        printf("Data size: %ld\n", Size);
        for (size_t i = 0; i < Size; i++) {
            printf("%02x ", Data[i]);
            if ((i + 1) % 16 == 0) {
                printf("\n");
            }
        }
        if (Size % 16 != 0) {
            printf("\n");
        }
    } else {
        // Still need to print the data for tracing the input
        for (size_t i = 0; i < Size; i++) {
            printf("%02x ", Data[i]);
        }
        printf("\n");
    }
    // Create Property QDict for qdev_device_add
    QDict *qdict = qdict_clone_shallow(fuzz_device_extraopt);
    qdict_put_str(qdict, "driver", fuzz_driver);

    // add device properties
    for (int i = 0; i < prop_list_size && Size; i++) {
        int type_id = prop_list[i].type;
        if (type_id > PROP_TYPE_UNSIGNED) {
            type_id -= PROP_TYPE_UNSIGNED;
        }
        if (Size < prop_type[type_id].size) {
            continue;
        }
        prop_type[type_id].qdict_put_handler(qdict, prop_list[i].name, Data);
        Data += prop_type[type_id].size;
        Size -= prop_type[type_id].size;
    }

    Error *err = NULL;
    DeviceState *dev = qdev_device_add_from_qdict(qdict, false, &err);
    if (err) {
        error_report_err(err);
    }
    if (!dev) {     // sam as `qmp_device_add`
        goto clean;
    }

    // continue initialization and tests that not completed
    QOSGraphNode *node = qos_graph_get_node(fuzz_driver);
    void *obj = qos_driver_new(node, fuzz_device_parent, fuzz_qos_alloc, fuzz_edge_arg);
    qos_object_start_hw(obj);
    qos_object_destroy(obj);

    // do some clean 

    // currently asynchoronous unplug request not handled
    // so we need to use unrealize manually
    // qdev_unplug(dev, error_abort);  
    if (dev) {
        qdev_unrealize(dev);
        object_unparent(OBJECT(dev));
        // drain_call_rcu();
        // printf("obj refcnt: %d\n", OBJECT(dev)->ref);
        object_unref(OBJECT(dev));
    }
clean:
    drain_call_rcu();   // wait for RCU to recycle the objects
    qdict_unref(qdict);
}
