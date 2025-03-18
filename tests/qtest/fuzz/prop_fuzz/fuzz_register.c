#include "qos_prop_fuzz.h"
#include "utils.h"

static void prop_fuzz_register_nodes(void)
{
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-rng-pci-prop-fuzz",
            .description = "Fuzz virtio-rng-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-rng-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82558b-prop-fuzz",
            .description = "Fuzz i82558b device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82558b",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "tulip-prop-fuzz",
            .description = "Fuzz tulip device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "tulip",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "ne2k_pci-prop-fuzz",
            .description = "Fuzz ne2k_pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ne2k_pci",
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
            .name = "i82550-prop-fuzz",
            .description = "Fuzz i82550 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82550",
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
            .name = "i82559c-prop-fuzz",
            .description = "Fuzz i82559c device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82559c",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "nvme-prop-fuzz",
            .description = "Fuzz nvme device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "nvme",
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
            .name = "ufs-prop-fuzz",
            .description = "Fuzz ufs device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ufs",
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
            .name = "i82562-prop-fuzz",
            .description = "Fuzz i82562 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82562",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82559er-prop-fuzz",
            .description = "Fuzz i82559er device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82559er",
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
            .name = "AC97-prop-fuzz",
            .description = "Fuzz AC97 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "AC97",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82801-prop-fuzz",
            .description = "Fuzz i82801 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82801",
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
            .name = "tpci200-prop-fuzz",
            .description = "Fuzz tpci200 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "tpci200",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82559a-prop-fuzz",
            .description = "Fuzz i82559a device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82559a",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82558a-prop-fuzz",
            .description = "Fuzz i82558a device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82558a",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82557a-prop-fuzz",
            .description = "Fuzz i82557a device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82557a",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "ES1370-prop-fuzz",
            .description = "Fuzz ES1370 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ES1370",
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
            .name = "e1000-82544gc-prop-fuzz",
            .description = "Fuzz e1000-82544gc device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000-82544gc",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82557c-prop-fuzz",
            .description = "Fuzz i82557c device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82557c",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "e1000-prop-fuzz",
            .description = "Fuzz e1000 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000",
            &(QOSGraphTestOptions){}
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
            .name = "vmxnet3-prop-fuzz",
            .description = "Fuzz vmxnet3 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "vmxnet3",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82551-prop-fuzz",
            .description = "Fuzz i82551 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82551",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "e1000e-prop-fuzz",
            .description = "Fuzz e1000e device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000e",
            &(QOSGraphTestOptions){.before = net_test_setup_socket}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "pcnet-prop-fuzz",
            .description = "Fuzz pcnet device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pcnet",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "megasas-prop-fuzz",
            .description = "Fuzz megasas device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "megasas",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "ipoctal232-prop-fuzz",
            .description = "Fuzz ipoctal232 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ipoctal232",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "e1000-82545em-prop-fuzz",
            .description = "Fuzz e1000-82545em device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000-82545em",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82559b-prop-fuzz",
            .description = "Fuzz i82559b device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82559b",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82557b-prop-fuzz",
            .description = "Fuzz i82557b device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82557b",
            &(QOSGraphTestOptions){}
            );
}

libqos_init(prop_fuzz_register_nodes);