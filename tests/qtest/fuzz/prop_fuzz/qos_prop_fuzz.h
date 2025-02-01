#ifndef QOS_PROP_FUZZ_H
#define QOS_PROP_FUZZ_H

#include "tests/qtest/fuzz/fuzz.h"
#include "tests/qtest/libqos/qgraph.h"

void fuzz_add_qos_prop_target(
		FuzzTarget *fuzz_opts,
		const char *interface,
		QOSGraphTestOptions *opts
		);

#endif