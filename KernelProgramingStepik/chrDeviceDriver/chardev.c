#include <linux/module.h> // The header for modules development.
#include <linux/init.h> // Init macros for modules.
#include <linux/fs.h> // files opeartions support.
#include <linux/uaccess.h> // Access to the user space.
#include <linux/slab.h> // Kernel memory management.
#include <linux/cdev.h> // Work with char devices.


static dev_t first; // An ID for the first device in a the device tree.
static unsigned int count = 1; // A counter of devices.
static int my_major = 700, my_minor = 0; // Major and minor device numbers.
static struct cdev* my_cdev; // The struct for the char device.

// Set the device name.
#define MYDEV_NAME "MyCharDevice"
// Set the the amount of kernel emory pages for the device.
#define KBUF_SIZE 10 * PAGE_SIZE


// File operation: open device
static int mychardev_open(struct inode* inode, struct file* file) {
	static int counter = 0;
	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;
	counter++;
	return 0;
}

// File operation: close device
static int mychardev_release(struct inode* inode, struct file* file) {
	char *kbuf = file->private_data;
	if (kbuf) {
		kfree(kbuf);
	}
	kbuf = NULL;
	file->private_data = NULL;
	return 0;
}

// File operation: read from user
// __user macro says the data arrived from user and required more checks;
// loff - left offset. 
static ssize_t mychardev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos) {
	char *kbuf = file->private_data;
	//  Copy a block of data into user space.
	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;
	return nbytes;
}

// File opeartion: write to the file (can be read from user)
static ssize_t mychardev_write(struct file *file, const  char __user *buf, size_t lbuf, loff_t *ppos) {
	char *kbuf = file->private_data;
	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	ppos += nbytes;
	return nbytes;
}

// File operations struct with pointers to file opeartions functions.
static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.read = mychardev_read,
	.write = mychardev_write,
	.open = mychardev_open,
	.release = mychardev_release
};

static int __init init_chardev(void) {
	// Create FS node to access the device. MKDEV is a macro.
	first = MKDEV(my_major, my_minor);
	// Register a range of device numbers 
	register_chrdev_region(first, count, MYDEV_NAME);
	// Allocate memory for all device attributes.
	my_cdev = cdev_alloc();	
	// Initialize char device.
	cdev_init(my_cdev, &mycdev_fops);
	// Add an exact one device.
	cdev_add(my_cdev, first, count);	
	return 0;
}


static void __exit cleanup_chardev(void) {
	if (my_cdev) {
		cdev_del(my_cdev);
	}
	unregister_chrdev_region(first, count);
}

module_init(init_chardev);
module_exit(cleanup_chardev);

MODULE_LICENSE("GPL");
