#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>


static struct kobject *my_kobj;
static int reads_cnt;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
	reads_cnt++;
	return sprintf(buf, "%d\n", cnt);
}


static int __init init_kobj_reads_counter(void) {
       return 0;
}

static void __exit cleanup_kobj_reads_counter(void) {
}


module_init(init_kobj_reads_counter);
module_exit(cleanup_kobj_reads_counter);

MODULE_LICENSE("GPL");
