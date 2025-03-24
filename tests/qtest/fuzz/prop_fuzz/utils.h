#ifndef QEMU_PROP_FUZZ_UTILS_H
#define QEMU_PROP_FUZZ_UTILS_H

#include "qemu/osdep.h"
#include "qos_prop_fuzz.h"
#include "../../libqos/pci.h"

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

// For qgraph node creation
typedef struct GENERIC_DEVICE {
	QOSGraphObject obj;
} GENERIC_DEVICE;

typedef struct GENERIC_PCI_DEVICE {
	QOSGraphObject obj;
	QPCIDevice pci_dev;
} GENERIC_PCI_DEVICE;


void *dumb_get_driver(void *obj, const char *interface);
void dumb_start_hw(QOSGraphObject *obj);
void dumb_pci_start_hw(QOSGraphObject *obj);
void dumb_destructor(QOSGraphObject *obj);
void *generic_pci_create(void *pci_bus, QGuestAllocator *alloc, void *addr);
void *generic_create(void *pci_bus, QGuestAllocator *alloc, void *addr);

#endif