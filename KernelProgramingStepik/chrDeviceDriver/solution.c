#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/uaccess.h>

#define KBUF_SIZE 10 * PAGE_SIZE
#define MYDEV_NAME "solution_node"

// Module-level varaibles
static dev_t first;
static int my_major = 240, my_minor = 0;
static struct cdev *my_cdev;
static unsigned int devcnt = 1;
static int opencnt = 0; // How many times the device was opened for read or write.
static int datacnt = 0; // An amount of data written into the device.
static char message[100] = {0};


static int mychrdev_open(struct inode* inode, struct file* file) {
	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;
	opencnt++;
  return 0;
  }

static int mychrdev_release(struct inode* inode, struct file* file) {
  char *kbuf = file->private_data;
	if (kbuf) {
		kfree(kbuf);
	}
	kbuf = NULL;
	file->private_data = NULL;
	return 0;
  }

/** @brief This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user. In this case is uses the copy_to_user() function to
 *  send the buffer string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 */
static ssize_t mychrdev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
	snprintf(message, sizeof(message), "%d %d\n", opencnt, datacnt);
	return simple_read_from_buffer(buffer, len, offset, message, sizeof(message));
}

static ssize_t mychrdev_write(struct file *file, const  char __user *buf, size_t lbuf, loff_t *ppos) {
  char *kbuf = file->private_data;
	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	ppos += nbytes;
  datacnt += nbytes;
	printk(KERN_INFO "Data count: %d\n", datacnt);
	return nbytes;
}

static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.open = mychrdev_open,
	.release = mychrdev_release,
  .read = mychrdev_read,
	.write = mychrdev_write
};

static int __init init_chardev(void) {
	int err;
	first = MKDEV(my_major, my_minor);
	register_chrdev_region(first, devcnt, MYDEV_NAME);
	my_cdev = cdev_alloc();	
	cdev_init(my_cdev, &mycdev_fops);
	err = cdev_add(my_cdev, first, devcnt);
	if (err < 0) {
		printk(KERN_ERR "Device add error!\n");
		return err;
	}
	printk(KERN_INFO "Module 'solution_node' loaded succesfully.\n");
	return 0;
}

static void __exit cleanup_chardev(void) {
	if (my_cdev) {
		cdev_del(my_cdev);
	}
	unregister_chrdev_region(first, devcnt);
	printk(KERN_INFO "Module 'solution_node' cleaned up succesfully.\n");
}

module_init(init_chardev);
module_exit(cleanup_chardev);

MODULE_LICENSE("GPL");
