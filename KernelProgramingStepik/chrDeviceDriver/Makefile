obj-m += solution.o

all:
	make -C /lib/modules/$(shell uname -r)/build -I /home/skyfox/Projects/linux-stable/include M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
