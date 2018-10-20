make clean || true
make 
sudo insmod solution.ko
cat /sys/kernel/my_kobject/my_sys
sudo rmmod solution
sudo dmesg -c 