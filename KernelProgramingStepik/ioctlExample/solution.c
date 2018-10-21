#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/uaccess.h>


// Device info
static dev_t my_cdev_number; // a device number (a major number and minor number) 
static int my_major_number = 240;
static int my_minor_number = 0;
static struct cdev *my_cdev;
static int device_open = 0;


static int my_cdev_open(struct inode* inode, struct file* file) {
  if (device_open) return -EBUSY;
  device_open++;
  return 0;
}

static int my_cdev_release(struct inode* inode, struct file* file) {
        device_open--;
        return 0;
}

static ssize_t my_cdev_read(struct file *file, char *buf, size_t count, loff_t *ppos) { 
  char *hello_str = "Hello, world!\n";
  int len = strlen(hello_str);
  if(count < len) return -EINVAL; 
  if( *ppos != 0 ) return 0; // EOF
  if(copy_to_user(buf, hello_str, len)) return -EINVAL; 
  *ppos = len;
  return len;
}


static const struct file_operations my_cdev_fops = { 
   .owner = THIS_MODULE,
   .open = my_cdev_open,
   .release = my_cdev_release,
   .read = my_cdev_read
};

// Init function will be called on the module start up.
static int __init init_solution(void) {
  my_cdev_number = MKDEV(my_major_number, my_minor_number);
  if (register_chrdev_region(my_cdev_number, 1, "SolutionCharDevice")) {
    pr_alert("Can't register register a range of device numbers.");
  }
  my_cdev = cdev_alloc();
  cdev_init(my_cdev, &my_cdev_fops);
  if (cdev_add(my_cdev, my_cdev_number, 1)) { // Add one device.
    pr_alert("Can't add char device.");
  }
  return 0;
}

// Cleanup function will be called on module unload.
static void __exit cleanup_solution(void) {
}

// Specify what functions to call on module load and unload.
module_init(init_solution);
module_exit(cleanup_solution);


MODULE_AUTHOR("Dima Timofeev");
// These macros are required. Without license specification a module will not
// compile.
MODULE_LICENSE("GPL");