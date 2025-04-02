#include "qos_prop_fuzz.h"
#include "utils.h"

static void prop_fuzz_register_nodes(void)
{
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82557a-prop-fuzz",
            .description = "Fuzz i82557a device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82557a",
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
            .name = "tulip-prop-fuzz",
            .description = "Fuzz tulip device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "tulip",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "sb16-prop-fuzz",
            .description = "Fuzz sb16 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "sb16",
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
            .name = "i82559c-prop-fuzz",
            .description = "Fuzz i82559c device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82559c",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "ctucan_pci-prop-fuzz",
            .description = "Fuzz ctucan_pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ctucan_pci",
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
            .name = "megasas-prop-fuzz",
            .description = "Fuzz megasas device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "megasas",
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
            .name = "qemu-xhci-prop-fuzz",
            .description = "Fuzz qemu-xhci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "qemu-xhci",
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
            .name = "virtio-rng-pci-prop-fuzz",
            .description = "Fuzz virtio-rng-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-rng-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "floppy-prop-fuzz",
            .description = "Fuzz floppy device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "floppy",
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
            .name = "virtio-sound-pci-prop-fuzz",
            .description = "Fuzz virtio-sound-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-sound-pci",
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
            .name = "ide-cd-prop-fuzz",
            .description = "Fuzz ide-cd device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ide-cd",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "mptsas1068-prop-fuzz",
            .description = "Fuzz mptsas1068 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "mptsas1068",
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
            .name = "i82801-prop-fuzz",
            .description = "Fuzz i82801 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82801",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "pci-ipmi-bt-prop-fuzz",
            .description = "Fuzz pci-ipmi-bt device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pci-ipmi-bt",
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
            .name = "cs4231a-prop-fuzz",
            .description = "Fuzz cs4231a device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "cs4231a",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-mouse-pci-prop-fuzz",
            .description = "Fuzz virtio-mouse-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-mouse-pci",
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
            .name = "isa-cirrus-vga-prop-fuzz",
            .description = "Fuzz isa-cirrus-vga device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "isa-cirrus-vga",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "lsi53c810-prop-fuzz",
            .description = "Fuzz lsi53c810 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "lsi53c810",
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
            .name = "i82557c-prop-fuzz",
            .description = "Fuzz i82557c device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82557c",
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
            .name = "i6300esb-prop-fuzz",
            .description = "Fuzz i6300esb device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i6300esb",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "isa-applesmc-prop-fuzz",
            .description = "Fuzz isa-applesmc device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "isa-applesmc",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "mc146818rtc-prop-fuzz",
            .description = "Fuzz mc146818rtc device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "mc146818rtc",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-crypto-pci-prop-fuzz",
            .description = "Fuzz virtio-crypto-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-crypto-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "isa-fdc-prop-fuzz",
            .description = "Fuzz isa-fdc device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "isa-fdc",
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
            .name = "e1000e-prop-fuzz",
            .description = "Fuzz e1000e device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000e",
            &(QOSGraphTestOptions){.before = net_test_setup_socket}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-mem-pci-prop-fuzz",
            .description = "Fuzz virtio-mem-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-mem-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "isa-vga-prop-fuzz",
            .description = "Fuzz isa-vga device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "isa-vga",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "kvaser_pci-prop-fuzz",
            .description = "Fuzz kvaser_pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "kvaser_pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "pci-serial-prop-fuzz",
            .description = "Fuzz pci-serial device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pci-serial",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-tablet-pci-prop-fuzz",
            .description = "Fuzz virtio-tablet-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-tablet-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "am53c974-prop-fuzz",
            .description = "Fuzz am53c974 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "am53c974",
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
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i82559b-prop-fuzz",
            .description = "Fuzz i82559b device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82559b",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "intel-hda-prop-fuzz",
            .description = "Fuzz intel-hda device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "intel-hda",
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
            .name = "sdhci-pci-prop-fuzz",
            .description = "Fuzz sdhci-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "sdhci-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-keyboard-pci-prop-fuzz",
            .description = "Fuzz virtio-keyboard-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-keyboard-pci",
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
            .name = "pcm3680_pci-prop-fuzz",
            .description = "Fuzz pcm3680_pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pcm3680_pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "rtl8139-prop-fuzz",
            .description = "Fuzz rtl8139 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "rtl8139",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "secondary-vga-prop-fuzz",
            .description = "Fuzz secondary-vga device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "secondary-vga",
            &(QOSGraphTestOptions){}
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
            .name = "e1000-prop-fuzz",
            .description = "Fuzz e1000 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "e1000",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "mioe3680_pci-prop-fuzz",
            .description = "Fuzz mioe3680_pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "mioe3680_pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "pci-ipmi-kcs-prop-fuzz",
            .description = "Fuzz pci-ipmi-kcs device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pci-ipmi-kcs",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "ide-hd-prop-fuzz",
            .description = "Fuzz ide-hd device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ide-hd",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "pvscsi-prop-fuzz",
            .description = "Fuzz pvscsi device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pvscsi",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "i8042-prop-fuzz",
            .description = "Fuzz i8042 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i8042",
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
            .name = "rocker-prop-fuzz",
            .description = "Fuzz rocker device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "rocker",
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
            .name = "gus-prop-fuzz",
            .description = "Fuzz gus device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "gus",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-pmem-pci-prop-fuzz",
            .description = "Fuzz virtio-pmem-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-pmem-pci",
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
            .name = "i82550-prop-fuzz",
            .description = "Fuzz i82550 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "i82550",
            &(QOSGraphTestOptions){}
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
            .name = "pcnet-prop-fuzz",
            .description = "Fuzz pcnet device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "pcnet",
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
            .name = "bochs-display-prop-fuzz",
            .description = "Fuzz bochs-display device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "bochs-display",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "virtio-multitouch-pci-prop-fuzz",
            .description = "Fuzz virtio-multitouch-pci device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "virtio-multitouch-pci",
            &(QOSGraphTestOptions){}
            );
    fuzz_add_qos_prop_target(&(FuzzTarget){
            .name = "ib700-prop-fuzz",
            .description = "Fuzz ib700 device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ib700",
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
            .name = "ufs-prop-fuzz",
            .description = "Fuzz ufs device property",
            .pre_fuzz = &qos_init_path,
            .fuzz = prop_fuzz,},
            "ufs",
            &(QOSGraphTestOptions){}
            );
}

fuzz_target_init(prop_fuzz_register_nodes);