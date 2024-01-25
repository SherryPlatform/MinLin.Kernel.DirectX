# SPDX-License-Identifier: GPL-2.0
# Makefile for the hyper-v compute device driver (dxgkrnl).

ifeq ($(KERNELRELEASE), )
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules
clean:
	rm -rf .tmp_versions Module.symvers *.mod.c *.o *.ko .*.cmd Module.markers modules.order
load:
	/sbin/insmod dxgkrnl.ko
unload:
	/sbin/rmmod dxgkrnl
install:
	cp dxgkrnl.ko /lib/modules/$(shell uname -r)/kernel/drivers/hv/dxgkrnl.ko
else
	obj-m += dxgkrnl.o
	dxgkrnl-y := dxgmodule.o hmgr.o misc.o dxgadapter.o ioctl.o dxgvmbus.o dxgprocess.o dxgsyncfile.o
endif