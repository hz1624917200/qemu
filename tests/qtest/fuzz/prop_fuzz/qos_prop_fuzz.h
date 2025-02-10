#ifndef QOS_PROP_FUZZ_H
#define QOS_PROP_FUZZ_H

#include "tests/qtest/fuzz/fuzz.h"
#include "tests/qtest/libqos/qgraph.h"

typedef enum {
	PROP_TYPE_UINT32,	// 0
	PROP_TYPE_INT32,	// 1
	PROP_TYPE_BOOL,		// 2
	PROP_TYPE_UINT8,	// 3
	PROP_TYPE_INT8,		// 4
	PROP_TYPE_UINT16,	// 5
	PROP_TYPE_INT16,	// 6
} PropType;

void fuzz_add_qos_prop_target(
		FuzzTarget *fuzz_opts,
		const char *interface,
		QOSGraphTestOptions *opts
		);

#endif