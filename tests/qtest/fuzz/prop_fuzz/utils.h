#ifndef QEMU_PROP_FUZZ_UTILS_H
#define QEMU_PROP_FUZZ_UTILS_H

#include "qemu/osdep.h"
#include "qos_prop_fuzz.h"

QDict *parse_opts(GString *opt_str);

// qdict put helper functions
void qdict_put_bool_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_int8_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_int16_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_int32_buf(QDict *qdict, const char *key, const unsigned char *value);

// Qemu Device Graph Test Options
void *net_test_setup_socket(GString *cmd_line, void *arg);
void *virtio_blk_test_setup(GString *cmd_line, void *arg);
void *virtio_scsi_test_setup(GString *cmd_line, void *arg);
void *igb_test_setup_no_socket(GString *cmd_line, void *arg);

#endif