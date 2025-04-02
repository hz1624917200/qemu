#ifndef GENERIC_PROP_FUZZ_CONFIGS_H
#define GENERIC_PROP_FUZZ_CONFIGS_H

#define COMMON_USB_CMD_STORAGE     "-usb "     "-drive file=null-co://,if=none,format=raw,id=disk0 -device usb-storage,port=1,drive=disk0"

#include "../generic_fuzz_configs.h"

const generic_fuzz_config prop_fuzz_predefined_configs[] = {
	{
		.arch = "x86_64",
		.name = "virtio-net-pci",
		.args = "-netdev socket,fd=5,id=hs0",
		.extra_opts = ",netdev=hs0",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "i82559a",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-sound-pci",
		.args = "-machine q35 -audiodev wav,id=my_audiodev",
		.extra_opts = ",audiodev=my_audiodev,streams=2",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "mptsas1068",
		.args = "-machine q35 -nodefaults -blockdev driver=null-co,read-zeroes=on,node-name=null0 -device scsi-cd,drive=null0",
		.extra_opts = "",
		.objects = "mptsas1068",
	},

	{
		.arch = "x86_64",
		.name = "nvme",
		.args = "-machine q35 -drive id=drv0,if=none,file=null-co://,file.read-zeroes=on,format=raw -object memory-backend-ram,id=pmr0,share=on,size=8",
		.extra_opts = ",drive=drv0,serial=foo",
		.objects = "nvme*",
	},

	{
		.arch = "x86_64",
		.name = "sdhci-pci",
		.args = "",
		.extra_opts = "",
		.objects = "sd*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-pmem-pci",
		.args = "-machine q35 -nodefaults -m 2G,maxmem=4G -object memory-backend-ram,id=mem0,size=2G",
		.extra_opts = ",id=vm0,memdev=mem0",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "am53c974",
		.args = "-drive id=disk0,if=none,file=null-co://,format=raw -nodefaults -device scsi-hd,drive=disk0",
		.extra_opts = ",id=scsi",
		.objects = "*esp* *scsi* *am53c974*",
	},

	{
		.arch = "x86_64",
		.name = "tpci200",
		.args = "-machine q35 ",
		.extra_opts = ",id=ipack0",
		.objects = "tpci200*",
	},

	{
		.arch = "x86_64",
		.name = "igb",
		.args = "-netdev hubport,hubid=0,id=hs0",
		.extra_opts = ",netdev=hs0",
		.objects = "igb*",
	},

	{
		.arch = "x86_64",
		.name = "isa-applesmc",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "isa-applesmc",
	},

	{
		.arch = "x86_64",
		.name = "i82557c",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "i82557a",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "floppy",
		.args = "-nodefaults -drive id=disk0,file=null-co://,file.read-zeroes=on,if=none,format=raw",
		.extra_opts = ",id=floppy0",
		.objects = "fd* floppy* i8257",
	},

	{
		.arch = "x86_64",
		.name = "virtio-tablet-pci",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "i82550",
		.args = "-machine q35 ",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "sb16",
		.args = "-machine q35 -nodefaults -audiodev none,id=snd0 -nodefaults",
		.extra_opts = ",audiodev=snd0",
		.objects = "sb16* i8257*",
	},

	{
		.arch = "x86_64",
		.name = "isa-fdc",
		.args = "-nodefaults",
		.extra_opts = "",
		.objects = "*fdc*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-9p-pci",
		.args = "-fsdev synth,id=fsdev0",
		.extra_opts = ",fsdev=fsdev0,mount_tag=qtest",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "i82557b",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "lsi53c810",
		.args = "-machine q35 -nodefaults -blockdev driver=null-co,read-zeroes=on,node-name=null0 -device scsi-cd,drive=null0",
		.extra_opts = "",
		.objects = "lsi53c810",
	},

	{
		.arch = "x86_64",
		.name = "virtio-mouse-pci",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-multitouch-pci",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "pcnet",
		.args = "-machine q35 ",
		.extra_opts = "",
		.objects = "pcnet",
	},

	{
		.arch = "x86_64",
		.name = "virtio-serial-pci",
		.args = "-machine q35 ",
		.extra_opts = ",id=vser0",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "kvaser_pci",
		.args = "-machine q35 -nodefaults -object can-bus,id=canbus0",
		.extra_opts = ",canbus=canbus0",
		.objects = "kvaser*",
	},

	{
		.arch = "x86_64",
		.name = "pvscsi",
		.args = "-machine q35 -nodefaults -blockdev driver=null-co,read-zeroes=on,node-name=null0 -device scsi-cd,drive=null0",
		.extra_opts = "",
		.objects = "pvscsi",
	},

	{
		.arch = "x86_64",
		.name = "mioe3680_pci",
		.args = "-machine q35 -nodefaults -object can-bus,id=canbus",
		.extra_opts = ",canbus0=canbus,canbus1=canbus",
		.objects = "mioe3680*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-balloon-pci",
		.args = "-machine q35 ",
		.extra_opts = "",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-mem-pci",
		.args = "-machine q35 -nodefaults -m 2G,maxmem=4G -object memory-backend-ram,id=mem0,size=2G",
		.extra_opts = ",id=vm0,memdev=mem0,node=0,requested-size=0x1000000",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "qemu-xhci",
		.args = "-machine q35 -nodefaults -drive file=null-co://,if=none,format=raw,id=disk0 -device usb-bot -device usb-storage,drive=disk0 -chardev null,id=cd0 -chardev null,id=cd1 -device usb-braille,chardev=cd0 -device usb-ccid -device usb-ccid -device usb-kbd -device usb-mouse -device usb-serial,chardev=cd1 -device usb-tablet -device usb-wacom-tablet -device usb-tablet,bus=xhci.0",
		.extra_opts = ",id=xhci",
		.objects = "*usb* *uhci* *xhci*",
	},

	{
		.arch = "x86_64",
		.name = "isa-vga",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "isa-vga",
	},

	{
		.arch = "x86_64",
		.name = "pci-ipmi-kcs",
		.args = "-machine q35 -nodefaults -device ipmi-bmc-sim,id=bmc",
		.extra_opts = ",bmc=bmc",
		.objects = "*ipmi*",
	},

	{
		.arch = "x86_64",
		.name = "pcm3680_pci",
		.args = "-machine q35 -nodefaults -object can-bus,id=canbus",
		.extra_opts = ",canbus0=canbus,canbus1=canbus",
		.objects = "pcm3680*",
	},

	{
		.arch = "x86_64",
		.name = "bochs-display",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "bochs*",
	},

	{
		.arch = "x86_64",
		.name = "ne2k_pci",
		.args = "-machine q35 ",
		.extra_opts = "",
		.objects = "ne2k*",
	},

	{
		.arch = "x86_64",
		.name = "i82558a",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "ib700",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "ib700",
	},

	{
		.arch = "x86_64",
		.name = "pci-serial",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "pci-serial",
	},

	{
		.arch = "x86_64",
		.name = "e1000-82545em",
		.args = "",
		.extra_opts = "",
		.objects = "e1000*",
	},

	{
		.arch = "x86_64",
		.name = "ide-cd",
		.args = "-nodefaults -drive file=null-co://,if=none,format=raw,id=disk0",
		.extra_opts = ",drive=disk0",
		.objects = "*ide*",
	},

	{
		.arch = "x86_64",
		.name = "i82559b",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "i82551",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "pci-ipmi-bt",
		.args = "-machine q35 -nodefaults -device ipmi-bmc-sim,id=bmc",
		.extra_opts = ",bmc=bmc",
		.objects = "*ipmi*",
	},

	{
		.arch = "x86_64",
		.name = "cs4231a",
		.args = "-machine q35 -nodefaults -audiodev none,id=snd0 -nodefaults",
		.extra_opts = ",audiodev=snd0",
		.objects = "cs4231a* i8257*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-rng-pci",
		.args = "-machine q35 ",
		.extra_opts = "",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-scsi-pci",
		.args = "-machine q35 -drive id=drv0,if=none,file=null-co://,file.read-zeroes=on,format=raw -device scsi-hd,bus=vs0.0,drive=drv0 -drive file=blkdebug::null-co://,file.image.read-zeroes=on,if=none,id=dr1,format=raw,file.align=4k -device scsi-hd,drive=dr1,lun=0,scsi-id=1",
		.extra_opts = ",id=vs0",
		.objects = "scsi* virtio*",
	},

	{
		.arch = "x86_64",
		.name = "tulip",
		.args = "-machine q35 ",
		.extra_opts = "",
		.objects = "tulip",
	},

	{
		.arch = "x86_64",
		.name = "virtio-crypto-pci",
		.args = "-machine q35 -nodefaults -object cryptodev-backend-builtin,id=cryptodev0",
		.extra_opts = ",id=crypto0,cryptodev=cryptodev0",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "e1000e",
		.args = "-netdev socket,fd=5,id=hs0",
		.extra_opts = ",netdev=hs0",
		.objects = "e1000e",
	},

	{
		.arch = "x86_64",
		.name = "i8042",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "i8042",
	},

	{
		.arch = "x86_64",
		.name = "e1000-82544gc",
		.args = "",
		.extra_opts = "",
		.objects = "e1000*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-blk-pci",
		.args = "-machine q35 -drive if=none,id=drive0,file=/tmp/qtest.HMQC42,format=raw,auto-read-only=off",
		.extra_opts = ",id=drv0,drive=drive0,addr=4.0",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "e1000",
		.args = "",
		.extra_opts = "",
		.objects = "e1000",
	},

	{
		.arch = "x86_64",
		.name = "i82562",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "AC97",
		.args = "-machine q35 -audiodev none,id=snd0,out.frequency=44100,in.frequency=44100",
		.extra_opts = ",audiodev=snd0",
		.objects = "ac97*",
	},

	{
		.arch = "x86_64",
		.name = "rocker",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "rocker",
	},

	{
		.arch = "x86_64",
		.name = "secondary-vga",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "secondary-vga*",
	},

	{
		.arch = "x86_64",
		.name = "ufs",
		.args = "-blockdev null-co,node-name=drv0,read-zeroes=on -device ufs-lu,bus=ufs0,drive=drv0,lun=0",
		.extra_opts = ",id=ufs0",
		.objects = "ufs*",
	},

	{
		.arch = "x86_64",
		.name = "i82801",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "intel-hda",
		.args = "-machine q35 -nodefaults -audiodev driver=none,id=audio0",
		.extra_opts = ",id=hda0",
		.objects = "intel-hda",
	},

	{
		.arch = "x86_64",
		.name = "ipoctal232",
		.args = "-device tpci200,addr=04.0,id=ipack0",
		.extra_opts = ",bus=ipack0.0",
		.objects = "ipoctal*",
	},

	{
		.arch = "x86_64",
		.name = "mc146818rtc",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "mc146818rtc",
	},

	{
		.arch = "x86_64",
		.name = "virtio-keyboard-pci",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "ctucan_pci",
		.args = "-machine q35 -nodefaults -object can-bus,id=canbus",
		.extra_opts = ",canbus0=canbus,canbus1=canbus",
		.objects = "ctucan*",
	},

	{
		.arch = "x86_64",
		.name = "i82559er",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "megasas",
		.args = "-machine q35 -drive id=drv0,if=none,file=null-co://,file.read-zeroes=on,format=raw -device scsi-hd,bus=scsi0.0,drive=drv0",
		.extra_opts = ",id=scsi0",
		.objects = "megasas*",
	},

	{
		.arch = "x86_64",
		.name = "i82559c",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "i82558b",
		.args = "",
		.extra_opts = "",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "ide-hd",
		.args = "-nodefaults -drive file=null-co://,if=none,format=raw,id=disk0",
		.extra_opts = ",drive=disk0",
		.objects = "*ide*",
	},

	{
		.arch = "x86_64",
		.name = "vmxnet3",
		.args = "-machine q35 ",
		.extra_opts = "",
		.objects = "vmxnet3",
	},

	{
		.arch = "x86_64",
		.name = "ES1370",
		.args = "-machine q35 -audiodev driver=none,id=audio0",
		.extra_opts = ",audiodev=audio0",
		.objects = "es1370*",
	},

	{
		.arch = "x86_64",
		.name = "rtl8139",
		.args = "-machine q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "rtl8139",
	},

	{
		.arch = "x86_64",
		.name = "i6300esb",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "i6300esb",
	},

	{
		.arch = "x86_64",
		.name = "isa-cirrus-vga",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "isa-cirrus-vga",
	},

	{
		.arch = "x86_64",
		.name = "gus",
		.args = "-machine q35 -nodefaults -audiodev none,id=snd0 -nodefaults",
		.extra_opts = ",audiodev=snd0",
		.objects = "gus*",
	},

};

#endif /* GENERIC_PROP_FUZZ_CONFIGS_H */

