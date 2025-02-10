#include "qemu/osdep.h"
#include "qos_prop_fuzz.h"

void *net_test_setup_socket(GString *cmd_line, void *arg);
unsigned char* add_prop(QDict *qdict, PropType type, const char *name, const unsigned char *Data, size_t Size);
