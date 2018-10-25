make clean || true
make
sudo insmod solution.ko delays=100,200,300
sleep 2
sudo dmesg -c
sudo rmmod solution