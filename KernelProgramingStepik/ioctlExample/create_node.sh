DEVICE_NAME="solution_node"
MAJOR=240
MINOR=0

echo "Creating char device with major = $MAJOR and minor = $MINOR"
sudo mknod /dev/$DEVICE_NAME c $MAJOR $MINOR

echo "Adding full access to the device for everyone..."
sudo chmod a+rw /dev/$DEVICE_NAME