#ifndef QEMU_PROP_FUZZ_UTILS_H
#define QEMU_PROP_FUZZ_UTILS_H

#include "qemu/osdep.h"
#include "qos_prop_fuzz.h"

void *net_test_setup_socket(GString *cmd_line, void *arg);

void qdict_put_bool_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_int8_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_int16_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_int32_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_uint8_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_uint16_buf(QDict *qdict, const char *key, const unsigned char *value);
void qdict_put_uint32_buf(QDict *qdict, const char *key, const unsigned char *value);

#endif