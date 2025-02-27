#include "qos_prop_fuzz.h"
#include "utils.h"

static void prop_fuzz_register_nodes(void)
{
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "e1000e-prop-fuzz",
            .description = "Fuzz the e1000e device properties",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000e",
            &(QOSGraphTestOptions){.before = net_test_setup_socket}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-net-pci-prop-fuzz",
            .description = "Fuzz the virtio-net-pci device properties",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-net-pci",
            &(QOSGraphTestOptions){.before = net_test_setup_socket}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "igb-prop-fuzz",
            .description = "Fuzz the igb device properties",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "igb",
            &(QOSGraphTestOptions){}
            );
}

libqos_init(prop_fuzz_register_nodes);