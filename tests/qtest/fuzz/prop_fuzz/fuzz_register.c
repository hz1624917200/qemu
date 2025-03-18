#include "qos_prop_fuzz.h"
#include "utils.h"

static void prop_fuzz_register_nodes(void)
{
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i440FX-pcihost-prop-fuzz",
            .description = "Fuzz i440FX-pcihost device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i440FX-pcihost",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "pci-bus-pc-prop-fuzz",
            .description = "Fuzz pci-bus-pc device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pci-bus-pc",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-9p-pci-prop-fuzz",
            .description = "Fuzz virtio-9p-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-9p-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "vhost-user-gpio-pci-prop-fuzz",
            .description = "Fuzz vhost-user-gpio-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "vhost-user-gpio-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-iommu-pci-prop-fuzz",
            .description = "Fuzz virtio-iommu-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-iommu-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-serial-pci-prop-fuzz",
            .description = "Fuzz virtio-serial-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-serial-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-scsi-pci-prop-fuzz",
            .description = "Fuzz virtio-scsi-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-scsi-pci",
            &(QOSGraphTestOptions){.before = virtio_scsi_test_setup}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-rng-pci-prop-fuzz",
            .description = "Fuzz virtio-rng-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-rng-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-net-pci-prop-fuzz",
            .description = "Fuzz virtio-net-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-net-pci",
            &(QOSGraphTestOptions){.before = net_test_setup_socket}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "vhost-user-blk-pci-prop-fuzz",
            .description = "Fuzz vhost-user-blk-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "vhost-user-blk-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-blk-pci-prop-fuzz",
            .description = "Fuzz virtio-blk-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-blk-pci",
            &(QOSGraphTestOptions){.before = virtio_blk_test_setup}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-balloon-pci-prop-fuzz",
            .description = "Fuzz virtio-balloon-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-balloon-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "tpci200-prop-fuzz",
            .description = "Fuzz tpci200 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "tpci200",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "sdhci-pci-prop-fuzz",
            .description = "Fuzz sdhci-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "sdhci-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "igb-prop-fuzz",
            .description = "Fuzz igb device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "igb",
            &(QOSGraphTestOptions){.before = igb_test_setup_no_socket}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "e1000e-prop-fuzz",
            .description = "Fuzz e1000e device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000e",
            &(QOSGraphTestOptions){.before = net_test_setup_socket}
            );
}

libqos_init(prop_fuzz_register_nodes);