/*
 * Generic Virtual-Device Fuzzing Target Configs
 *
 * Copyright Red Hat Inc., 2020
 *
 * Authors:
 *  Alexander Bulekov   <alxndr@bu.edu>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */

#ifndef GENERIC_FUZZ_CONFIGS_H
#define GENERIC_FUZZ_CONFIGS_H

#define COMMON_USB_CMD_STORAGE \
    "-usb " \
    "-drive file=null-co://,if=none,format=raw,id=disk0 -device usb-storage,port=1,drive=disk0"

typedef struct generic_fuzz_config {
    const char *arch, *name, *args, *objects;
    gchar* (*argfunc)(void); /* Result must be freeable by g_free() */
} generic_fuzz_config;

static inline gchar *generic_fuzzer_virtio_9p_args(void){
    g_autofree char *tmpdir = g_dir_make_tmp("qemu-fuzz.XXXXXX", NULL);
    g_assert_nonnull(tmpdir);

    return g_strdup_printf("-machine q35 -nodefaults "
    "-device virtio-9p,fsdev=hshare,mount_tag=hshare "
    "-fsdev local,id=hshare,path=%s,security_model=mapped-xattr,"
    "writeout=immediate,fmode=0600,dmode=0700", tmpdir);
}

const generic_fuzz_config predefined_configs[] = {
    {
        .name = "virtio-net-pci-slirp",
        .args = "-M q35 -nodefaults "
        "-device virtio-net,netdev=net0 -netdev user,id=net0",
        .objects = "virtio*",
    },{
        .name = "virtio-blk",
        .args = "-machine q35 -device virtio-blk,drive=disk0 "
        "-drive file=null-co://,id=disk0,if=none,format=raw",
        .objects = "virtio*",
    },{
        .name = "virtio-scsi",
        .args = "-machine q35 -device virtio-scsi,num_queues=8 "
        "-device scsi-hd,drive=disk0 "
        "-drive file=null-co://,id=disk0,if=none,format=raw",
        .objects = "scsi* virtio*",
    },{
        .name = "virtio-gpu",
        .args = "-machine q35 -nodefaults -device virtio-gpu",
        .objects = "virtio*",
    },{
        .name = "virtio-vga",
        .args = "-machine q35 -nodefaults -device virtio-vga",
        .objects = "virtio*",
    },{
        .name = "virtio-rng",
        .args = "-machine q35 -nodefaults -device virtio-rng",
        .objects = "virtio*",
    },{
        .name = "virtio-balloon",
        .args = "-machine q35 -nodefaults -device virtio-balloon",
        .objects = "virtio*",
    },{
        .name = "virtio-serial",
        .args = "-machine q35 -nodefaults -device virtio-serial",
        .objects = "virtio*",
    },{
        .name = "virtio-mouse",
        .args = "-machine q35 -nodefaults -device virtio-mouse",
        .objects = "virtio*",
    },{
        .name = "virtio-9p",
        .argfunc = generic_fuzzer_virtio_9p_args,
        .objects = "virtio*",
    },{
        .name = "virtio-9p-synth",
        .args = "-machine q35 -nodefaults "
        "-device virtio-9p,fsdev=hshare,mount_tag=hshare "
        "-fsdev synth,id=hshare",
        .objects = "virtio*",
    },{
        .name = "e1000",
        .args = "-M q35 -nodefaults "
        "-device e1000,netdev=net0 -netdev user,id=net0",
        .objects = "e1000",
    },{
        .name = "e1000e",
        .args = "-M q35 -nodefaults "
        "-device e1000e,netdev=net0 -netdev user,id=net0",
        .objects = "e1000e",
    },{
        .name = "igb",
        .args = "-M q35 -nodefaults "
        "-device igb,netdev=net0 -netdev user,id=net0",
        .objects = "igb",
    },{
        .name = "cirrus-vga",
        .args = "-machine q35 -nodefaults -device cirrus-vga",
        .objects = "cirrus*",
    },{
        .name = "bochs-display",
        .args = "-machine q35 -nodefaults -device bochs-display",
        .objects = "bochs*",
    },{
        .name = "intel-hda",
        .args = "-machine q35 -nodefaults -device intel-hda,id=hda0 "
        "-audiodev driver=none,id=audio0",
        "-device hda-output,bus=hda0.0,audiodev=audio0 "
        "-device hda-micro,bus=hda0.0,audiodev=audio0 "
        "-device hda-duplex,bus=hda0.0,audiodev=audio0",
        .objects = "intel-hda",
    },{
        .name = "ide-hd",
        .args = "-machine pc -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device ide-hd,drive=disk0",
        .objects = "*ide*",
    },{
        .name = "ide-atapi",
        .args = "-machine pc -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device ide-cd,drive=disk0",
        .objects = "*ide*",
    },{
        .name = "ahci-hd",
        .args = "-machine q35 -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device ide-hd,drive=disk0",
        .objects = "*ahci*",
    },{
        .name = "ahci-atapi",
        .args = "-machine q35 -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device ide-cd,drive=disk0",
        .objects = "*ahci*",
    },{
        .name = "floppy",
        .args = "-machine pc -nodefaults -device floppy,id=floppy0 "
        "-drive id=disk0,file=null-co://,file.read-zeroes=on,if=none,format=raw "
        "-device floppy,drive=disk0,drive-type=288",
        .objects = "fd* floppy* i8257",
    },{
        .name = "xhci",
        .args = "-machine q35 -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device qemu-xhci,id=xhci -device usb-tablet,bus=xhci.0 "
        "-device usb-bot -device usb-storage,drive=disk0 "
        "-chardev null,id=cd0 -chardev null,id=cd1 "
        "-device usb-braille,chardev=cd0 -device usb-ccid -device usb-ccid "
        "-device usb-kbd -device usb-mouse -device usb-serial,chardev=cd1 "
        "-device usb-tablet -device usb-wacom-tablet "
        "-device usb-audio,audiodev=snd0 -audiodev none,id=snd0",
        .objects = "*usb* *uhci* *xhci*",
    },{
        .name = "pc-i440fx",
        .args = "-machine pc",
        .objects = "*",
    },{
        .name = "pc-q35",
        .args = "-machine q35",
        .objects = "*",
    },{
        .name = "vmxnet3",
        .args = "-machine q35 -nodefaults "
        "-device vmxnet3,netdev=net0 -netdev user,id=net0",
        .objects = "vmxnet3"
    },{
        .name = "ne2k_pci",
        .args = "-machine q35 -nodefaults "
        "-device ne2k_pci,netdev=net0 -netdev user,id=net0",
        .objects = "ne2k*"
    },{
        .name = "pcnet",
        .args = "-machine q35 -nodefaults "
        "-device pcnet,netdev=net0 -netdev user,id=net0",
        .objects = "pcnet"
    },{
        .name = "rtl8139",
        .args = "-machine q35 -nodefaults "
        "-device rtl8139,netdev=net0 -netdev user,id=net0",
        .objects = "rtl8139"
    },{
        .name = "i82550",
        .args = "-machine q35 -nodefaults "
        "-device i82550,netdev=net0 -netdev user,id=net0",
        .objects = "i8255*"
    },{
        .name = "sdhci-v3",
        .args = "-nodefaults -device sdhci-pci,sd-spec-version=3 "
        "-device sd-card,drive=mydrive "
        "-drive if=none,index=0,file=null-co://,format=raw,id=mydrive -nographic",
        .objects = "sd*"
    },{
        .name = "ehci",
        .args = "-machine q35 -nodefaults "
        "-device ich9-usb-ehci1,bus=pcie.0,addr=1d.7,"
        "multifunction=on,id=ich9-ehci-1 "
        "-device ich9-usb-uhci1,bus=pcie.0,addr=1d.0,"
        "multifunction=on,masterbus=ich9-ehci-1.0,firstport=0 "
        "-device ich9-usb-uhci2,bus=pcie.0,addr=1d.1,"
        "multifunction=on,masterbus=ich9-ehci-1.0,firstport=2 "
        "-device ich9-usb-uhci3,bus=pcie.0,addr=1d.2,"
        "multifunction=on,masterbus=ich9-ehci-1.0,firstport=4 "
        "-drive if=none,id=usbcdrom,media=cdrom "
        "-device usb-tablet,bus=ich9-ehci-1.0,port=1,usb_version=1 "
        "-device usb-storage,bus=ich9-ehci-1.0,port=2,drive=usbcdrom",
        .objects = "*usb* *hci*",
    },{
        .name = "ohci",
        .args = "-machine q35 -nodefaults  -device pci-ohci -device usb-kbd",
        .objects = "*usb* *ohci*",
    },{
        .name = "megaraid",
        .args = "-machine q35 -nodefaults -device megasas -device scsi-cd,drive=null0 "
        "-blockdev driver=null-co,read-zeroes=on,node-name=null0",
        .objects = "megasas*",
    },{
        .name = "am53c974",
        .args = "-device am53c974,id=scsi -device scsi-hd,drive=disk0 "
                 "-drive id=disk0,if=none,file=null-co://,format=raw "
                 "-nodefaults",
        .objects = "*esp* *scsi* *am53c974*",
    },{
        .name = "ac97",
        .args = "-machine q35 -nodefaults "
        "-device ac97,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "ac97*",
    },{
        .name = "cs4231a",
        .args = "-machine q35 -nodefaults "
        "-device cs4231a,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "cs4231a* i8257*",
    },{
        .name = "es1370",
        .args = "-machine q35 -nodefaults "
        "-device es1370,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "es1370*",
    },{
        .name = "sb16",
        .args = "-machine q35 -nodefaults "
        "-device sb16,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "sb16* i8257*",
    },{
        .name = "parallel",
        .args = "-machine q35 -nodefaults "
        "-parallel file:/dev/null",
        .objects = "parallel*",
    }
};

const generic_fuzz_config prop_fuzz_predefined_configs[] = {
    {
        .arch = "x86_64",
        .name = "ufs",
        .args = "-M q35 -nodefaults -drive file=null-co://,if=none,id=disk0 "
        "-device ufs,id=ufs_bus -device ufs-lu,drive=disk0,bus=ufs_bus",
       .objects = "ufs*",
    },{
        .arch = "x86_64",
        .name = "virtio-net-pci_slirp",
        .args = "-M q35 -nodefaults "
        "-device virtio-net-pci,netdev=net0,mq=true,rss=true,hash=true,guest_rsc_ext=true -netdev user,id=net0",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-net-pci",
        .args = "-M q35 -nodefaults "
        "-device virtio-net-pci,netdev=net0 -netdev user,id=net0",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-net-pci_socket",
        .args = "-M q35 -nodefaults "
        "-device virtio-net-pci,netdev=net0 -netdev socket,id=net0,fd=5",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-blk-pci",
        .args = "-machine q35 -device virtio-blk-pci,drive=drive0 "
        "-drive file=null-co://,id=drive0,if=none,format=raw ",
        // "-blockdev node-name=drive0,driver=host_device,filename=/dev/nullb0,cache.direct=on",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-sound-pci",
        .args = "-machine q35 -device virtio-sound-pci,audiodev=my_audiodev,streams=2 -audiodev wav,id=my_audiodev",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-scsi-pci",
        .args = "-machine q35 -device virtio-scsi-pci,num_queues=8 "
        "-device scsi-hd,drive=disk0 "
        "-drive file=null-co://,id=disk0,if=none,format=raw",
        .objects = "scsi* virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-gpu-pci",
        // .args = "-machine q35 -nodefaults -device virtio-gpu-pci,blob=true -object memory-backend-memfd,id=mem1,size=8192M",
        .args = "-machine q35 -nodefaults -device virtio-gpu-pci -object memory-backend-memfd,id=mem1,size=8192M",
        .objects = "virtio*",
    },{
    //     .arch = "x86_64",
    //     .name = "virtio-gpu-gl",
    //     // .args = "-machine q35 -nodefaults -device virtio-gpu-gl,blob=true -display egl-headless,rendernode=/dev/dri/renderD128",
    //     .args = "-machine q35 -nodefaults -device virtio-gpu-gl -display egl-headless,rendernode=/dev/dri/renderD128",
    //     .objects = "virtio*",
    // },{
        .arch = "x86_64",
        .name = "virtio-vga",
        .args = "-machine q35 -nodefaults -device virtio-vga",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-multitouch-pci",
        .args = "-machine q35 -nodefaults -device virtio-multitouch-pci",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-rng-pci",
        .args = "-machine q35 -nodefaults -device virtio-rng-pci",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-balloon-pci",
        .args = "-machine q35 -nodefaults -device virtio-balloon-pci,free-page-reporting=true",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-tablet-pci",
        .args = "-machine q35 -nodefaults -device virtio-tablet-pci",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-serial-pci",
        .args = "-machine q35 -nodefaults -device virtio-serial-pci -chardev socket,path=/tmp/foo,server=on,wait=off,id=foo -chardev socket,path=/tmp/bar,server=on,wait=off,id=bar -device virtconsole,chardev=foo -device virtserialport,chardev=bar",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-crypto-pci",
        .args = "-machine q35 -nodefaults "
            "-object cryptodev-backend-builtin,id=cryptodev0 "
            // "-object cryptodev-backend-lkfc,id=cryptodev0 "
            "-device virtio-crypto-pci,id=crypto0,cryptodev=cryptodev0",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-iommu-pci",
        .args = "-machine q35 -nodefaults -device virtio-iommu-pci",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-mem-pci",
        .args = "-machine q35 -nodefaults -m 2G,maxmem=4G -object memory-backend-ram,id=mem0,size=2G -device virtio-mem-pci,id=vm0,memdev=mem0,node=0,requested-size=0x1000000",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-pmem-pci",
        .args = "-machine q35 -nodefaults -m 2G,maxmem=4G -object memory-backend-ram,id=mem0,size=2G -device virtio-pmem-pci,id=vm0,memdev=mem0",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-keyboard-pci",
        .args = "-machine q35 -nodefaults -device virtio-keyboard-pci",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-mouse-pci",
        .args = "-machine q35 -nodefaults -device virtio-mouse-pci",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-9p-pci",
        // .args = "",
        .argfunc = generic_fuzzer_virtio_9p_args,
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "virtio-9p-pci_synth",
        .args = "-machine q35 -nodefaults "
        "-device virtio-9p-pci,fsdev=hshare,mount_tag=hshare "
        "-fsdev synth,id=hshare",
        .objects = "virtio*",
    },{
        .arch = "x86_64",
        .name = "e1000",
        .args = "-M q35 -nodefaults "
        "-device e1000,netdev=net0 -netdev user,id=net0",
        .objects = "e1000",
    },{
        .arch = "x86_64",
        .name = "e1000e",
        .args = "-M q35 -nodefaults "
        "-device e1000e,netdev=net0 -netdev user,id=net0",
        .objects = "e1000e",
    },{
        .arch = "x86_64",
        .name = "igb",
        .args = "-M q35 -nodefaults "
        "-device igb,netdev=net0 -netdev user,id=net0",
        .objects = "igb*",
    },{
        .arch = "x86_64",
        .name = "cirrus-vga",
        .args = "-machine q35 -nodefaults -device cirrus-vga",
        .objects = "cirrus*",
    },{
        .arch = "x86_64",
        .name = "secondary-vga",
        .args = "-machine q35 -nodefaults -device secondary-vga",
        .objects = "secondary-vga*",
    },{
        .arch = "x86_64",
        .name = "ati-vga",
        .args = "-machine q35 -nodefaults -device ati-vga",
        .objects = "ati*",
    },{
    //     .arch = "x86_64",
    //     .name = "sm501",
    //     .args = "-machine q35 -nodefaults -device sm501",
    //     .objects = "sm501",
    // },{
        .arch = "x86_64",
        .name = "vmware-svga",
        .args = "-machine q35 -nodefaults -device vmware-svga",
        .objects = "vmware-svga*",
    },{
        .arch = "x86_64",
        .name = "VGA",
        .args = "-machine q35 -nodefaults -device VGA",
        .objects = "vga*",
    },{
        .arch = "x86_64",
        .name = "bochs-display",
        .args = "-machine q35 -nodefaults -device bochs-display",
        .objects = "bochs*",
    },{
        .arch = "x86_64",
        .name = "amd-iommu",
        .args = "-machine q35 -nodefaults -device amd-iommu",
        .objects = "amd*",
    },{
        .arch = "x86_64",
        .name = "intel-iommu",
        .args = "-machine q35 -nodefaults -device intel-iommu",
        .objects = "intel*",
    },{
    //     .arch = "x86_64",
    //     .name = "apic",
    //     .args = "-machine q35 -nodefaults",
    //     .objects = "apic*",
    // },{
    //     .arch = "x86_64",
    //     .name = "hpet",
    //     .args = "-machine q35 -nodefaults",
    //     .objects = "hpet*",
    // },{
    //     .arch = "x86_64",
    //     .name = "qxl",
    //     .args = "-machine q35 -nodefaults -device qxl",
    //     .objects = "qxl*",
    // },{
        .arch = "x86_64",
        .name = "intel-hda",
        .args = "-machine q35 -nodefaults -device intel-hda,id=hda0 "
        "-audiodev driver=none,id=audio0",
        "-device hda-output,bus=hda0.0 -device hda-micro,bus=hda0.0 "
        "-device hda-duplex,bus=hda0.0",
        .objects = "intel-hda",
    },{
        .arch = "x86_64",
        .name = "ide-hd",
        .args = "-machine pc -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device ide-hd,drive=disk0",
        .objects = "*ide*",
    },{
        .arch = "x86_64",
        .name = "ide-cd",
        .args = "-machine pc -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device ide-cd,drive=disk0",
        .objects = "*ide*",
    },{
    // Same config with different monitoring devices
    //     .arch = "x86_64",
    //     .name = "ide-hd",
    //     .args = "-machine q35 -nodefaults "
    //     "-drive file=null-co://,if=none,format=raw,id=disk0 "
    //     "-device ide-hd,drive=disk0",
    //     .objects = "*ahci*",
    // },{
    //     .arch = "x86_64",
    //     .name = "ide-cd",
    //     .args = "-machine q35 -nodefaults "
    //     "-drive file=null-co://,if=none,format=raw,id=disk0 "
    //     "-device ide-cd,drive=disk0",
    //     .objects = "*ahci*",
    // },{
        .arch = "x86_64",
        .name = "floppy",
        .args = "-machine pc -nodefaults -device floppy,id=floppy0 "
        "-drive id=disk0,file=null-co://,file.read-zeroes=on,if=none,format=raw "
        "-device floppy,drive=disk0,drive-type=288",
        .objects = "fd* floppy* i8257",
    },{
        .arch = "x86_64",
        .name = "qemu-xhci",
        .args = "-machine q35 -nodefaults "
        "-drive file=null-co://,if=none,format=raw,id=disk0 "
        "-device qemu-xhci,id=xhci -device usb-tablet,bus=xhci.0 "
        "-device usb-bot -device usb-storage,drive=disk0 "
        "-chardev null,id=cd0 -chardev null,id=cd1 "
        "-device usb-braille,chardev=cd0 -device usb-ccid -device usb-ccid "
        "-device usb-kbd -device usb-mouse -device usb-serial,chardev=cd1 "
        // "-device usb-tablet -device usb-wacom-tablet -device usb-audio",
        "-device usb-tablet -device usb-wacom-tablet",
        .objects = "*usb* *uhci* *xhci*",
    },{
    //     .arch = "x86_64",
    //     .name = "pc-i440fx",
    //     .args = "-machine pc",
    //     .objects = "*",
    // },{
    //     .arch = "x86_64",
    //     .name = "pc-q35",
    //     .args = "-machine q35",
    //     .objects = "*",
    // },{
        .arch = "x86_64",
        .name = "rocker",
        .args = "-machine q35 -nodefaults -device rocker",
        .objects = "rocker"
    },{
        .arch = "x86_64",
        .name = "vmxnet3",
        .args = "-machine q35 -nodefaults "
        "-device vmxnet3,netdev=net0 -netdev user,id=net0",
        .objects = "vmxnet3"
    },{
        .arch = "x86_64",
        .name = "ne2k_pci",
        .args = "-machine q35 -nodefaults "
        "-device ne2k_pci,netdev=net0 -netdev user,id=net0",
        .objects = "ne2k*"
    },{
        .arch = "x86_64",
        .name = "pcnet",
        .args = "-machine q35 -nodefaults "
        "-device pcnet,netdev=net0 -netdev user,id=net0",
        .objects = "pcnet"
    },{
        .arch = "x86_64",
        .name = "tulip",
        .args = "-machine q35 -nodefaults "
        "-device tulip,netdev=net0 -netdev user,id=net0",
        .objects = "tulip"
    },{
    //     .arch = "x86_64",
    //     .name = "sunhme",
    //     .args = "-machine q35 -nodefaults "
    //     "-device sunhme,netdev=net0 -netdev user,id=net0",
    //     .objects = "sunhme*"
    // },{
    //     .arch = "x86_64",
    //     .name = "sungem",
    //     .args = "-machine q35 -nodefaults "
    //     "-device sungem,netdev=net0 -netdev user,id=net0",
    //     .objects = "sungem*"
    // },{
        .arch = "x86_64",
        .name = "rtl8139",
        .args = "-machine q35 -nodefaults "
        "-device rtl8139,netdev=net0 -netdev user,id=net0",
        .objects = "rtl8139"
    },{
        .arch = "x86_64",
        .name = "i82550",
        .args = "-machine q35 -nodefaults "
        "-device i82550,netdev=net0 -netdev user,id=net0",
        .objects = "i8255*"
    },{
        .arch = "x86_64",
        .name = "sdhci-pci",
        .args = "-nodefaults -device sdhci-pci,sd-spec-version=3 "
        "-device sd-card,drive=mydrive "
        "-drive if=none,index=0,file=null-co://,format=raw,id=mydrive -nographic",
        .objects = "sd*"
    },{
        .arch = "x86_64",
        .name = "ich9-usb-ehci1",
        .args = "-machine q35 -nodefaults "
        "-device ich9-usb-ehci1,bus=pcie.0,addr=1d.7,"
        "multifunction=on,id=ich9-ehci-1 "
        "-device ich9-usb-uhci1,bus=pcie.0,addr=1d.0,"
        "multifunction=on,masterbus=ich9-ehci-1.0,firstport=0 "
        "-device ich9-usb-uhci2,bus=pcie.0,addr=1d.1,"
        "multifunction=on,masterbus=ich9-ehci-1.0,firstport=2 "
        "-device ich9-usb-uhci3,bus=pcie.0,addr=1d.2,"
        "multifunction=on,masterbus=ich9-ehci-1.0,firstport=4 "
        "-drive if=none,id=usbcdrom,media=cdrom "
        "-device usb-tablet,bus=ich9-ehci-1.0,port=1,usb_version=1 "
        "-device usb-storage,bus=ich9-ehci-1.0,port=2,drive=usbcdrom",
        .objects = "*usb* uhci*",
    },{
        .arch = "x86_64",
        .name = "pci-ohci",
        .args = "-machine q35 -nodefaults  -device pci-ohci -device usb-kbd",
        .objects = "*usb* *ohci*",
    // },{
    //     .arch = "x86_64",
    //     .name = "dc390",
    //     .args = "-machine q35 -nodefaults -device dc390 -device scsi-cd,drive=null0 "
    //     "-blockdev driver=null-co,read-zeroes=on,node-name=null0",
    //     .objects = "*esp* *scsi*",
    },{
        .arch = "x86_64",
        .name = "mptsas1068",
        .args = "-machine q35 -nodefaults -device mptsas1068 -device scsi-cd,drive=null0 "
        "-blockdev driver=null-co,read-zeroes=on,node-name=null0",
        .objects = "mptsas1068",
    },{
        .arch = "x86_64",
        .name = "pvscsi",
        .args = "-machine q35 -nodefaults -device pvscsi -device scsi-cd,drive=null0 "
        "-blockdev driver=null-co,read-zeroes=on,node-name=null0",
        .objects = "pvscsi",
    },{
        .arch = "x86_64",
        .name = "lsi53c810",
        .args = "-machine q35 -nodefaults -device lsi53c810 -device scsi-cd,drive=null0 "
        "-blockdev driver=null-co,read-zeroes=on,node-name=null0",
        .objects = "lsi53c810",
    },{
        .arch = "x86_64",
        .name = "megasas",
        .args = "-machine q35 -nodefaults -device megasas -device scsi-cd,drive=null0 "
        "-blockdev driver=null-co,read-zeroes=on,node-name=null0",
        .objects = "megasas*",
    },{
        .arch = "x86_64",
        .name = "am53c974",
        .args = "-device am53c974,id=scsi -device scsi-hd,drive=disk0 "
                 "-drive id=disk0,if=none,file=null-co://,format=raw "
                 "-nodefaults",
        .objects = "*esp* *scsi* *am53c974*",
    },{
        .arch = "x86_64",
        .name = "AC97",
        .args = "-machine q35 -nodefaults "
        "-device AC97,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "ac97*",
    },{
        .arch = "x86_64",
        .name = "gus",
        .args = "-machine q35 -nodefaults "
        "-device gus,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "gus*",
    },{
        .arch = "x86_64",
        .name = "cs4231a",
        .args = "-machine q35 -nodefaults "
        "-device cs4231a,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "cs4231a* i8257*",
    },{
        .arch = "x86_64",
        .name = "ES1370",
        .args = "-machine q35 -nodefaults "
        "-device ES1370,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "es1370*",
    },{
        .arch = "x86_64",
        .name = "sb16",
        .args = "-machine q35 -nodefaults "
        "-device sb16,audiodev=snd0 -audiodev none,id=snd0 -nodefaults",
        .objects = "sb16* i8257*",
    },{
        .arch = "x86_64",
        .name = "pci-serial",
        .args = "-machine q35 -nodefaults -device pci-serial",
        .objects = "pci-serial",
    },{
        .arch = "x86_64",
        .name = "tpci200",
        .args = "-machine q35 -nodefaults -device tpci200",
        .objects = "tpci200*",
    },{
        .arch = "x86_64",
        .name = "i6300esb",
        .args = "-machine q35 -nodefaults -device i6300esb",
        .objects = "i6300esb",
    },{
    //     .arch = "x86_64",
    //     .name = "ich9-smb",
    //     .args = "-machine q35 -nodefaults -device twl92230 -device m41t80 -device ds1338 -device max7310 -device tmp421 -device lsm303dlhc_mag -device pca9552 -device axp221_pmu -device i2c-echo -device i2c-ddc -device ssd0303 -device sii9022 -device lm8323 -device emc1413",
    //     .objects = "ICH9-SMB",
    // },{
        .arch = "x86_64",
        .name = "ib700",
        .args = "-machine q35 -nodefaults -device ib700",
        .objects = "ib700",
    },{
        .arch = "x86_64",
        .name = "isa-fdc",
        .args = "-machine pc -nodefaults -device isa-fdc",
        // "-drive id=disk0,file=null-co://,file.read-zeroes=on,if=none,format=raw "
        // "-device floppy,unit=0,drive=disk0",
        .objects = "*fdc*",
    },{
        .arch = "x86_64",
        .name = "isa-cirrus-vga",
        .args = "-machine q35 -nodefaults -device isa-cirrus-vga",
        .objects = "isa-cirrus-vga",
    },{
        .arch = "x86_64",
        .name = "isa-vga",
        .args = "-machine q35 -nodefaults -device isa-vga",
        .objects = "isa-vga",
    },{
        .arch = "x86_64",
        .name = "i8042",
        .args = "-machine q35 -nodefaults -device i8042",
        .objects = "i8042",
    },{
        .arch = "x86_64",
        .name = "isa-applesmc",
        .args = "-machine q35 -nodefaults -device isa-applesmc",
        .objects = "isa-applesmc",
    },{
        .arch = "x86_64",
        .name = "mc146818rtc",
        .args = "-machine q35 -nodefaults -device mc146818rtc",
        .objects = "mc146818rtc",
    },{
        .arch = "x86_64",
        .name = "nvme",
        .args = "-machine q35 -nodefaults -device nvme,serial=deadbeef -device nvme-ns,drive=disk0,nsid=1 -drive file=null-co://,id=disk0,if=none,format=raw",
        .objects = "nvme*",
    },{
    //     .arch = "x86_64",
    //     .name = "parallel",
    //     .args = "-machine q35 -nodefaults "
    //     "-parallel file:/dev/null",
    //     .objects = "parallel*",
    // },{
        .arch = "x86_64",
        .name = "kvaser_pci",
        .args = "-machine q35 -nodefaults "
        "-object can-bus,id=canbus0 -device kvaser_pci,canbus=canbus0",
        .objects = "kvaser*",
    },{
        .arch = "x86_64",
        .name = "ctucan_pci",
        .args = "-machine q35 -nodefaults "
        "-object can-bus,id=canbus -device ctucan_pci,canbus0=canbus,canbus1=canbus",
        .objects = "ctucan*",
    },{
        .arch = "x86_64",
        .name = "pcm3680_pci",
        .args = "-machine q35 -nodefaults "
        "-object can-bus,id=canbus -device pcm3680_pci,canbus0=canbus,canbus1=canbus",
        .objects = "pcm3680*",
    },{
        .arch = "x86_64",
        .name = "mioe3680_pci",
        .args = "-machine q35 -nodefaults "
        "-object can-bus,id=canbus -device mioe3680_pci,canbus0=canbus,canbus1=canbus",
        .objects = "mioe3680*",
    },{
    //     .arch = "x86_64",
    //     .name = "fw-cfg",
    //     .args = "-machine q35 -nodefaults "
    //     "-fw_cfg name=truman,string=fuzz "
    //     "-fw_cfg name=is,string=promising ",
    //     "*fwcfg*",
    //     .objects = "*fwcfg.ctl* *fwcfg.data* *fwcfg.dma* *fwcfg*",
    // }, {
        .arch = "x86_64",
        .name = "acpi-erst",
        .args = "-machine q35 -nodefaults "
        "-object memory-backend-file,id=erstnvram,mem-path=acpi-erst.backing,size=0x10000,share=on "
        "-device acpi-erst,memdev=erstnvram",
        .objects = "*acpi-erst*",
    }, {
        .arch = "x86_64",
        .name = "pci-ipmi-kcs",
        .args = "-machine q35 -nodefaults -device ipmi-bmc-sim,id=bmc -device pci-ipmi-kcs,bmc=bmc",
        .objects = "*ipmi*",
    }, {
        .arch = "x86_64",
        .name = "pci-ipmi-bt",
        .args = "-machine q35 -nodefaults -device ipmi-bmc-sim,id=bmc -device pci-ipmi-bt,bmc=bmc",
        .objects = "*ipmi*",
    // }, {
    //     .arch = "x86_64",
    //     .name = "cxl",
    //     .args = "-machine q35,cxl=on -nodefaults "
    //     "-object memory-backend-file,id=cxl-mem1,share=on,mem-path=/tmp/cxltest.raw,size=256M "
    //     "-object memory-backend-file,id=cxl-lsa1,share=on,mem-path=/tmp/lsa.raw,size=256M "
    //     "-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1 "
    //     "-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2 "
    //     "-device cxl-type3,bus=root_port13,persistent-memdev=cxl-mem1,lsa=cxl-lsa1,id=cxl-pmem0 "
    //     "-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G",
    //     .objects = "*",
    },{
        .arch = "x86_64",
        .name = "i82557c",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82559c",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82557a",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "e1000-82545em",
        .args = "",
        .objects = "e1000*",
    },{
        .arch = "x86_64",
        .name = "i82559a",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82551",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82558b",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82557b",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "ipoctal232",
        .args = "",
        .objects = "ipoctal*",
    },{
        .arch = "x86_64",
        .name = "i82559er",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82559b",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "e1000-82544gc",
        .args = "",
        .objects = "e1000*",
    },{
        .arch = "x86_64",
        .name = "i82801",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82558a",
        .args = "",
        .objects = "i8255*",
    },{
        .arch = "x86_64",
        .name = "i82562",
        .args = "",
        .objects = "i8255*",
    },

    // aarch64
    {
		.arch = "aarch64",
		.name = "virt",
		.args = "-machine virt",
		.objects = "virtio* fwcfg* io*",
	},{
		.arch = "aarch64",
		.name = "akita",
		.args = "-machine akita",
		.objects = "sl* scoop* io*",
	},{
		.arch = "aarch64",
		.name = "pxa2xx",
		.args = "-machine akita",
		.objects = "pxa2xx*",
	},{
		.arch = "aarch64",
		.name = "ast1030",
		.args = "-machine ast1030-evb",
		.objects = "aspeed*",
	},{
		.arch = "aarch64",
		.name = "ast2500",
		.args = "-machine ast2500-evb",
		.objects = "aspeed*",
	},{
		.arch = "aarch64",
		.name = "ast2600",
		.args = "-machine ast2600-evb",
		.objects = "aspeed*",
	},{
		.arch = "aarch64",
		.name = "ast2700",
		.args = "-machine ast2700-evb",
		.objects = "aspeed*",
	},{
		.arch = "aarch64",
		.name = "gic",
		.args = "-machine ast2600-evb",
		.objects = "gic*",
	},{
		.arch = "aarch64",
		.name = "stm32l4x5",
		.args = "-machine b-l475e-iot01a",
		.objects = "stm32l4x5*",
	},{
		.arch = "aarch64",
		.name = "canon-a1100",
		.args = "-machine canon-a1100 -m 64",
		.objects = "digic*",
    },{
        .arch = "aarch64",
        .name = "strongarm",
        .args = "-machine collie",
        .objects = "ssp* *ppc* *gpio* rtc* pic*",
	},{
        .arch = "aarch64",
        .name = "collie",
        .args = "-machine collie",
        .objects = "*collie.fl1* *collie.fl2*",
    },{
		.arch = "aarch64",
		.name = "cubieboard",
		.args = "-machine cubieboard",
        "-net nic,model=allwinner-emac,netdev=net0 -netdev user,id=net0",
		.objects = "a10* allwinner* aw_emac*",
	},{
		.arch = "aarch64",
		.name = "integratorcp",
		.args = "-machine integratorcp",
		.objects = "integratorcm* icp* dbg*",
	},{
		.arch = "aarch64",
		.name = "kudo-bmc",
		.args = "-machine kudo-bmc",
		.objects = "ctrl* l2x0_cc* arm_mptimer_timer* capabilities* ports* ohci*",
	},{
		.arch = "aarch64",
		.name = "lm3s6965evb",
		.args = "-machine lm3s6965evb",
		.objects = "cmsdk* i2c* gptm* adc* ssys*",
	},{
		.arch = "aarch64",
		.name = "mps2-an500",
		.args = "-machine mps2-an500 -m 16",
		.objects = "cmsdk* i2s* mps2* VGA*",
	},{
		.arch = "aarch64",
		.name = "mps2-an505",
		.args = "-machine mps2-an505 -m 16",
		.objects = "tz-mpc-upstream*",
	},{
		.arch = "aarch64",
		.name = "musicpal",
		.args = "-machine musicpal -m 32",
		.objects = "musicpal* mv88w8618*",
	},{
		.arch = "aarch64",
		.name = "omap",
		.args = "-machine n810 -m 128",
		.objects = "omap*",
	},{
		.arch = "aarch64",
		.name = "netduino2",
		.args = "-machine netduino2",
		.objects = "stm32*",
	},{
		.arch = "aarch64",
		.name = "allwinner",
		.args = "-machine orangepi-pc -m 1G",
		.objects = "allwinner*",
	},{
		.arch = "aarch64",
		.name = "bcm2835",
		.args = "-machine raspi3b -m 1G",
		.objects = "bcm283* mphi*",
	},{
		.arch = "aarch64",
		.name = "pl",
		.args = "-machine realview-pb-a8",
		.objects = "pl* arm_sbcon_i2c* arm-sysctl*",
	},{
		.arch = "aarch64",
		.name = "smdkc210",
		.args = "-machine smdkc210",
		.objects = "dma*",
	},{
		.arch = "aarch64",
		.name = "sx1-v1",
		.args = "-machine sx1-v1 -m 32",
		.objects = "sx1*",
	},{
		.arch = "aarch64",
		.name = "xilinx-zynq-a9",
		.args = "-machine xilinx-zynq-a9",
		.objects = "spi* timer* zynq* lqspi*",
	},{
		.arch = "aarch64",
		.name = "xlnx-versal-virt",
		.args = "-machine xlnx-versal-virt",
		.objects = "xlnx*",
	},{
        .arch = "aarch64",
        .name = "xlnx-zynqmp-can",
        .args = "-machine xlnx-zcu102,canbus0=canbus0 "
        "-object can-bus,id=canbus0",
        .objects = "*xlnx.zynqmp-can*",
    },{
        .arch = "aarch64",
        .name = "imx-usb-phy",
        .args = "-machine sabrelite",
        .objects = "*imx-usbphy*",
    },{
        .arch = "aarch64",
        .name = "xgmac",
        .args = "-machine midway",
        .objects = "*xgmac*",
    },{
        .arch = "aarch64",
        .name = "stellaris-enet",
        .args = "-machine lm3s6965evb",
        .objects = "*stellaris_enet*",
    },{
        .arch = "aarch64",
        .name = "smc91c111",
        .args = "-machine mainstone",
        .objects = "*smc91c111-mmio* fpga*",
    },{
        .arch = "aarch64",
        .name = "dwc2",
        // aarch64 supports raspi0/1ap/2b, aarch64 supports raspi3
        .args = "-machine raspi2b -m 1G -nodefaults "
        COMMON_USB_CMD_STORAGE,
        .objects = "*dwc2-io* *dwc2-fifo*",
    },{
        .arch = "aarch64",
        .name = "npcm7xx",
        .args = "-machine npcm750-evb",
        .objects = "*npcm*",
    },{
        .arch = "aarch64",
        .name = "msf2-emac",
        .args= "-machine emcraft-sf2",
        .objects = "*msf2-emac*",
    },{
        .arch = "aarch64",
        .name = "lan9118",
        .args = "-machine smdkc210",
        .objects = "*lan9118-mmio*",
    },{
        .arch = "aarch64",
        .name = "cadence-gem",
        .args = "-machine xlnx-versal-virt "
        "-net nic,model=cadence_gem,netdev=net0 -netdev user,id=net0",
        .objects = "*enet*",
    },{
        .arch = "aarch64",
        .name = "xlnx-dp",
        .args = "-machine xlnx-zcu102",
        .objects = "*.core* *.v_blend* *.av_buffer_manager* *.audio*",
    },{
        .arch = "aarch64",
        .name = "exynos4210",
        .args = "-machine smdkc210",
        .objects = "*exynos4210*",
    },{
        .arch = "aarch64",
        .name = "tc6393xb",
        .args = "-machine tosa",
        .objects = "*tc6393xb*",
    },{
        .arch = "aarch64",
        .name = "pflash-cfi02",
        .args = "-machine xilinx-zynq-a9",
        .objects = "*zynq.pflash*",
    },{
        .arch = "aarch64",
        .name = "onenand",
        .args = "-machine n810 -m 128M",
        .objects = "*onenand*",
    },{
        .arch = "aarch64",
        .name = "sp804",
        .args = "-machine midway",
        .objects = "*sp804*",
    }, {
        .arch = "aarch64",
        .name = "cadence-uart",
        .args = "-machine xlnx-zcu102",
        .objects = "*uart*",
    }, {
        .arch = "aarch64",
        .name = "xlnx-zynqmp-qspips",
        .args = "-machine xlnx-zcu102",
        .objects = "*spi* *lqspi*",
    }, {
        .arch = "aarch64",
        .name = "aarch64-gicv3",
        .args = "-machine sbsa-ref",
        .objects = "*gicv3*",
    },{
        .arch = "aarch64",
        .name = "wdt-sbsa",
        .args = "-machine sbsa-ref",
        .objects = "*sbsa_gwdt.refresh* *sbsa_gwdt.control*",
    },

    // s390x
    // {
    //     .arch = "s390x",
    //     .name = "s390x",
    //     .args = "-device diag288",
    //     .objects = "*",
    // },

    // m68k
    {
        .arch = "m68k",
        .name = "m68k-virt",
        .args = "-machine virt",
        .objects = "goldfish* virt-*",
    }, {
        .arch = "m68k",
        .name = "m68k-an5206",
        .args = "-machine an5206",
        .objects = "mbar*",
    }, {
        .arch = "m68k",
        .name = "m68k-mcf5208evb",
        .args = "-machine mcf5208evb",
        .objects = "fec* mcf* uart* m5208*",
    }, {
        .arch = "m68k",
        .name = "m68k-next-cube",
        .args = "-machine next-cube",
        .objects = "next* escc* esp*",
    }, {
        .arch = "m68k",
        .name = "m68k-q800",
        .args = "-machine q800",
        .objects = "via* dp* dj* asc* IOSB* iwm*",
    }, {
        .arch = "m68k",
        .name = "m68k-macfb",
        .args = "-machine q800 -device nubus-macfb",
        .objects = "macfb*",
    },

    // sparc
    {
        .arch = "sparc",
        .name = "sparc-iommu",
        .args = "-machine LX -m 256",
        .objects = "iommu*",
    }, {
        .arch = "sparc",
        .name = "sparc-tcx",
        .args = "-machine LX -m 256",
        .objects = "tcx*",
    }, {
        .arch = "sparc",
        .name = "sparc-LX",
        .args = "-machine LX -m 256",
        .objects = "m48t59* fdc* leds* configuration* misc* software* diagnostic* modem* system* esp* ledma* lance* fwcfg*",
    }, {
        .arch = "sparc",
        .name = "sparc-timer",
        .args = "-machine LX -m 256",
        .objects = "timer*",
    }, {
        .arch = "sparc",
        .name = "sparc-interrupt",
        .args = "-machine LX -m 256",
        .objects = "slave* master*",
    }, {
        .arch = "sparc",
        .name = "sparc-leon3",
        .args = "-machine leon3_generic -m 256",
        .objects = "uart* irqmp* gptimer* grlib*",
    },

    // ppc
    {
        .arch = "ppc",
        .name = "ppc-mpc8544ds",
        .args = "-machine mpc8544ds -m 192",
        .objects = "mpc* glb* tmr* msi* summary* src* cpu* mpc* e500*",
    }, {
        .arch = "ppc",
        .name = "ppc-ppce500",
        .args = "-machine ppce500 -m 192",
        .objects = "esdhc* mpc*",
    }, {
        .arch = "ppc",
        .name = "ppc-virtex-ml507",
        .args = "-machine virtex-ml507",
        .objects = "xlnx*",
    },

    // loongarch64
    {
        .arch = "loongarch64",
        .name = "loongarch64",
        .args = "-machine virt -m 1G",
        .objects = "*",
    },

    // mips
    {
        .arch = "mips",
        .name = "mips-malta",
        .args = "-machine malta",
        .objects = "*",
    }, {
        .arch = "mips",
        .name = "mips-mipssim",
        .args = "-machine mipssim",
        .objects = "*",
    },

    // sh4
    {
        .arch = "sh4",
        .name = "sh4-timer",
        .args = "",
        .objects = "timer*",
    }, {
        .arch = "sh4",
        .name = "sh4-intc",
        .args = "",
        .objects = "intc*",
    }, {
        .arch = "sh4",
        .name = "sh4-sci",
        .args = "",
        .objects = "sci*",
    },

    // riscv64
    {
        .arch = "riscv64",
        .name = "riscv64-microchip",
        .args = "-machine microchip-icicle-kit -m 2G",
        .objects = "*",
    }, {
        .arch = "riscv64",
        .name = "riscv64-shakti_c",
        .args = "-machine shakti_c -m 2G",
        .objects = "riscv*",
    }, {
        .arch = "riscv64",
        .name = "riscv64-spike",
        .args = "-machine spike -m 2G",
        .objects = "riscv*",
    },
    
    {
        .arch = "avr",
        .name = "avr-mega",
        .args = "-machine mega",
        .objects = "*",
    },
    {
        .arch = "cris",
        .name = "cris",
        .args = "",
        .objects = "*",
    },
    {
        .arch = "hppa",
        .name = "hppa",
        .args = "",
        .objects = "lasips2* dino* cpu0*",
    },
    {
        .arch = "alpha",
        .name = "alpha",
        .args = "",
        .objects = "*",
    },
    {
        .arch = "microblaze",
        .name = "microblaze-petalogix",
        .args = "-machine petalogix-s3adsp1800",
        .objects = "xlnx*",
    },
    {
        .arch = "microblaze",
        .name = "microblaze-xlnx",
        .args = "-machine xlnx-zynqmp-pmu",
        .objects = "xlnx*",
    },
    {
        .arch = "rx",
        .name = "rx",
        .args = "-machine gdbsim-r5f562n8",
        .objects = "*",
    },
    {
        .arch = "tricore",
        .name = "tricore",
        .args = "-machine KIT_AURIX_TC277_TRB",
        .objects = "*",
    },
    {
        .arch = "or1k",
        .name = "or1k",
        .args = "",
        .objects = "open_eth*",
    },
};


#endif
