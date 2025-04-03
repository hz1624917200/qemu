#ifndef GENERIC_PROP_FUZZ_CONFIGS_H
#define GENERIC_PROP_FUZZ_CONFIGS_H

#define COMMON_USB_CMD_STORAGE     "-usb "     "-drive file=null-co://,if=none,format=raw,id=disk0 -device usb-storage,port=1,drive=disk0"

#include "../generic_fuzz_configs.h"

const generic_fuzz_config prop_fuzz_predefined_configs[] = {
	{
		.arch = "x86_64",
		.name = "virtio-net-pci",
		.args = "-M q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "i82559a",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-machine q35 -nodefaults -device scsi-cd,drive=null0 -blockdev driver=null-co,read-zeroes=on,node-name=null0",
		.extra_opts = "",
		.objects = "mptsas1068",
	},

	{
		.arch = "x86_64",
		.name = "nvme",
		.args = "-machine q35 -nodefaults -drive file=null-co://,id=disk0,if=none,format=raw",
		.extra_opts = "-ns,drive=disk0,nsid=1",
		.objects = "nvme*",
	},

	{
		.arch = "x86_64",
		.name = "sdhci-pci",
		.args = "-nodefaults -device sd-card,drive=mydrive -drive if=none,index=0,file=null-co://,format=raw,id=mydrive -nographic",
		.extra_opts = ",sd-spec-version=3",
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
		.args = "-device scsi-hd,drive=disk0 -drive id=disk0,if=none,file=null-co://,format=raw -nodefaults",
		.extra_opts = ",id=scsi",
		.objects = "*esp* *scsi* *am53c974*",
	},

	{
		.arch = "x86_64",
		.name = "tpci200",
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "tpci200*",
	},

	{
		.arch = "x86_64",
		.name = "igb",
		.args = "-M q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "i82557a",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "floppy",
		.args = "-machine pc -nodefaults -drive id=disk0,file=null-co://,file.read-zeroes=on,if=none,format=raw",
		.extra_opts = ",drive=disk0,drive-type=288",
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
		.args = "-machine q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-machine pc -nodefaults",
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
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "lsi53c810",
		.args = "-machine q35 -nodefaults -device scsi-cd,drive=null0 -blockdev driver=null-co,read-zeroes=on,node-name=null0",
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
		.args = "-machine q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "pcnet",
	},

	{
		.arch = "x86_64",
		.name = "virtio-serial-pci",
		.args = "-machine q35 -nodefaults -chardev socket,path=/tmp/foo,server=on,wait=off,id=foo -chardev socket,path=/tmp/bar,server=on,wait=off,id=bar -device virtconsole,chardev=foo -device virtserialport,chardev=bar",
		.extra_opts = "",
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
		.args = "-machine q35 -nodefaults -device scsi-cd,drive=null0 -blockdev driver=null-co,read-zeroes=on,node-name=null0",
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
		.args = "-machine q35 -nodefaults",
		.extra_opts = ",free-page-reporting=true",
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
		.args = "-machine q35 -nodefaults -drive file=null-co://,if=none,format=raw,id=disk0 -device usb-tablet,bus=xhci.0 -device usb-bot -device usb-storage,drive=disk0 -chardev null,id=cd0 -chardev null,id=cd1 -device usb-braille,chardev=cd0 -device usb-ccid -device usb-ccid -device usb-kbd -device usb-mouse -device usb-serial,chardev=cd1 -device usb-tablet -device usb-wacom-tablet",
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
		.args = "-machine q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "ne2k*",
	},

	{
		.arch = "x86_64",
		.name = "i82558a",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "e1000*",
	},

	{
		.arch = "x86_64",
		.name = "ide-cd",
		.args = "-machine pc -nodefaults -drive file=null-co://,if=none,format=raw,id=disk0",
		.extra_opts = ",drive=disk0",
		.objects = "*ide*",
	},

	{
		.arch = "x86_64",
		.name = "i82559b",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "i82551",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-machine q35 -nodefaults",
		.extra_opts = "",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-scsi-pci",
		.args = "-machine q35 -device scsi-hd,drive=disk0 -drive file=null-co://,id=disk0,if=none,format=raw",
		.extra_opts = ",num_queues=8",
		.objects = "scsi* virtio*",
	},

	{
		.arch = "x86_64",
		.name = "tulip",
		.args = "-machine q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-M q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "e1000*",
	},

	{
		.arch = "x86_64",
		.name = "virtio-blk-pci",
		.args = "-machine q35 -drive file=null-co://,id=drive0,if=none,format=raw",
		.extra_opts = ",drive=drive0",
		.objects = "virtio*",
	},

	{
		.arch = "x86_64",
		.name = "e1000",
		.args = "-M q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "e1000",
	},

	{
		.arch = "x86_64",
		.name = "i82562",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "AC97",
		.args = "-machine q35 -nodefaults -audiodev none,id=snd0 -nodefaults",
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
		.args = "-M q35 -nodefaults -drive file=null-co://,if=none,id=disk0",
		.extra_opts = "-lu,drive=disk0,bus=ufs_bus",
		.objects = "ufs*",
	},

	{
		.arch = "x86_64",
		.name = "i82801",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
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
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "megasas",
		.args = "-machine q35 -nodefaults -device scsi-cd,drive=null0 -blockdev driver=null-co,read-zeroes=on,node-name=null0",
		.extra_opts = "",
		.objects = "megasas*",
	},

	{
		.arch = "x86_64",
		.name = "i82559c",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "i82558b",
		.args = "-netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "i8255*",
	},

	{
		.arch = "x86_64",
		.name = "ide-hd",
		.args = "-machine pc -nodefaults -drive file=null-co://,if=none,format=raw,id=disk0",
		.extra_opts = ",drive=disk0",
		.objects = "*ide*",
	},

	{
		.arch = "x86_64",
		.name = "vmxnet3",
		.args = "-machine q35 -nodefaults -netdev user,id=net0",
		.extra_opts = ",netdev=net0",
		.objects = "vmxnet3",
	},

	{
		.arch = "x86_64",
		.name = "ES1370",
		.args = "-machine q35 -nodefaults -audiodev none,id=snd0 -nodefaults",
		.extra_opts = ",audiodev=snd0",
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

