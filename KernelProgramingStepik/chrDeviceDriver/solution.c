#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/uaccess.h>

#define KBUF_SIZE 10 * PAGE_SIZE
#define MYDEV_NAME "solution_node"

static char *node_name = "default_node_name";
module_param(node_name, charp, 0660);

// Module-level varaibles
static char message[100] = {0};
static int given_major;  
static int my_minor = 0;
static struct device *my_cdev;
static struct class *my_class;


static int mychrdev_open(struct inode* inode, struct file* file) {
	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;
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

static ssize_t mychrdev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
	snprintf(message, sizeof(message), "%d\n", given_major);
	return simple_read_from_buffer(buffer, len, offset, message, sizeof(message));
}

static ssize_t mychrdev_write(struct file *file, const  char __user *buf, size_t lbuf, loff_t *ppos) {
  char *kbuf = file->private_data;
	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	ppos += nbytes;
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

  // Try to dynamically allocate a major number for the device -- more difficult but worth it
  given_major = register_chrdev(0, node_name, &mycdev_fops);
  if (given_major < 0){
    printk(KERN_ALERT "MyCharDev: failed to register a major number\n");
    return given_major;
  }
  printk(KERN_INFO "MyCharDev: registered correctly with major number %d\n", given_major);

  // Register the device class
  my_class = class_create(THIS_MODULE, "my_class");
  if (IS_ERR(my_class)) {                // Check for error and clean up if there is
      unregister_chrdev(given_major, node_name);
      printk(KERN_ALERT "Failed to register device class\n");
      return PTR_ERR(my_class);          // Correct way to return an error on a pointer
  }
  printk(KERN_INFO "MyCharDev: device class registered correctly\n");

  // Register the device driver
  my_cdev = device_create(my_class, NULL, MKDEV(given_major, my_minor), NULL, node_name);
  if (IS_ERR(my_cdev)) {               // Clean up if there is an error
      class_destroy(my_class);           // Repeated code but the alternative is goto statements
      unregister_chrdev(given_major, node_name);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(my_cdev);
  }
  printk(KERN_INFO "MyCharDev: device class created correctly\n"); // Made it! device was initialized
  return 0;
}

static void __exit cleanup_chardev(void) {
  device_destroy(my_class, MKDEV(given_major, 0));     // remove the device
  class_unregister(my_class);                          // unregister the device class
  class_destroy(my_class);                             // remove the device class
  unregister_chrdev(given_major, node_name);             // unregister the major number
	printk(KERN_INFO "MyCharDev: Module 'solution_node' cleaned up succesfully.\n");
}

module_init(init_chardev);
module_exit(cleanup_chardev);

MODULE_LICENSE("GPL");
