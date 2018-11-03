# Export/Import symbol
obj-m += solution.o
obj-m += checker.o

# Empty solution
obj-m += solution.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean