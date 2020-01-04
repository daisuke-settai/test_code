objm = kprobe.o

obj-m += $(objm)

all:
	make -Wall -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -Wall -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

