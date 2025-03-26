#include "qos_prop_fuzz.h"
#include "utils.h"

static void prop_fuzz_register_nodes(void)
{
// TEMPLATE
    fuzz_add_qos_prop_target(&(FuzzTarget){{
            .name = "{name}-prop-fuzz",
            .description = "Fuzz {name} device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,}},
            "{name}",
            &(QOSGraphTestOptions){{{pre_fuzz}}}
            );
// TEMPLATE
}

fuzz_target_init(prop_fuzz_register_nodes);