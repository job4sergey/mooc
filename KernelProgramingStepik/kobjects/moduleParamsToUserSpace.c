#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>


static struct kobject *my_kobj;

static int sum = 0;

static int a = 0;
module_param(a, int, 0660);

static int b = 0;
module_param(b, int, 0660);

static int c[5] = {0, 0, 0, 0, 0};
module_param_array(c, int, NULL, 0660);


// Read kobject file function
static ssize_t my_sys_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
	return sprintf(buf, "%d", sum);
}

// Write kobject file function
static ssize_t my_sys_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
	return 0;
}

// The struct with file attributes
static struct kobj_attribute my_sys_attribute = __ATTR(my_sys, 0755, my_sys_show, my_sys_store);

static int __init kboj_init(void) {
  int retval;
  sum = a + b + c[0] + c[1] + c[2] + c[3] + c[4];
	my_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
	retval = sysfs_create_file(my_kobj, &my_sys_attribute.attr);
	return retval;
}

static void __exit kobj_exit(void) {
	kobject_put(my_kobj);
}

module_init(kboj_init);
module_exit(kobj_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dima Timofeev");