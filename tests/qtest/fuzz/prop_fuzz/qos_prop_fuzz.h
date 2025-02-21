#ifndef QOS_PROP_FUZZ_H
#define QOS_PROP_FUZZ_H

#include "qemu/osdep.h"

#include "tests/qtest/fuzz/fuzz.h"
#include "tests/qtest/fuzz/qos_fuzz.h"
#include "tests/qtest/libqos/qgraph.h"

typedef enum {
	PROP_TYPE_BOOL,			// 0
	PROP_TYPE_INT8,			// 1
	PROP_TYPE_INT16,		// 2
	PROP_TYPE_INT32,		// 3
	PROP_TYPE_UNSIGNED,		// 4, for alignment of unsigned int
	PROP_TYPE_UINT8,		// 5
	PROP_TYPE_UINT16,		// 6
	PROP_TYPE_UINT32,		// 7
} PropTypeEnum;

typedef struct {
	int size;
	void (*qdict_put_handler)(QDict *qdict, const char *key, const unsigned char *value);
} PropType;

void fuzz_add_qos_prop_target(
		FuzzTarget *fuzz_opts,
		const char *interface,
		QOSGraphTestOptions *opts
		);

void prop_fuzz(QTestState *s, const unsigned char *Data, size_t Size);

#endif