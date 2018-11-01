make clean || true
make
sudo insmod solution.ko delays=200,300,500
sleep 2
sudo dmesg -c
sudo rmmod solution