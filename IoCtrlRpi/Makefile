ifneq ($(KERNELRELEASE),)

obj-m := IoCtrl.o

else


KDIR := /lib/modules/4.9.44-v7+/build

all:
	make -C $(KDIR) M=$(shell pwd) modules
clean:
	rm -f *.ko *.o *.mod.o *mod.c *.symvers *.order

endif
