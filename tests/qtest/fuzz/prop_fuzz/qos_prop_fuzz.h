#ifndef QOS_PROP_FUZZ_H
#define QOS_PROP_FUZZ_H

#include "tests/qtest/fuzz/fuzz.h"
#include "tests/qtest/libqos/qgraph.h"

typedef enum {
	PROP_TYPE_UINT32,
	PROP_TYPE_INT32,
	PROP_TYPE_BOOL
} PropType;

void fuzz_add_qos_prop_target(
		FuzzTarget *fuzz_opts,
		const char *interface,
		QOSGraphTestOptions *opts
		);

#endif