obj-m += simple.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
remove:
	sudo rmmod simple
insert:
	sudo insmod simple.ko
clear:
	sudo dmesg -c
message:
	dmesg

