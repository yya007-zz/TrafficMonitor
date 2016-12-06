ifneq ($(KERNELRELEASE),)
   obj-m := main.o
else

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#KERNELDIR ?= /home/vagrant/Desktop/src/linux-3.11.1/

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
