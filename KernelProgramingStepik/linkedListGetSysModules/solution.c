#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/list.h>
#include <linux/list_sort.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/string.h>

static struct kobject *solution_kobj;

int my_strcmp(void *arg, struct list_head *left, struct list_head *right) {
  struct module *left_module = container_of(left, struct module, list);
  struct module *right_module = container_of(right, struct module, list);
  return strcmp(left_module->name, right_module->name);
}

/*
 * The "my_sys" file where a static variable is read from and written to.
 */
static ssize_t solution_attr_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
  struct list_head *real_head = THIS_MODULE->list.prev;
  list_sort(NULL, real_head, my_strcmp);

  struct list_head *my_list = NULL;
  struct module *my_module = NULL;
  list_for_each(my_list, real_head) {
    my_module = container_of(my_list, struct module, list);
    strncat(buf, my_module->name, strlen(my_module->name));
    strncat(buf, "\n", 1);
  }

	return strlen(buf);
}

/* Sysfs attributes cannot be world-writable. */
static struct kobj_attribute solution_attr =
	__ATTR(my_sys, 0755, solution_attr_show, NULL);

// Init function will be called on the module start up.
static int __init init_solution(void) {
  int retval = 0;
  solution_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
  retval = sysfs_create_file(solution_kobj, &solution_attr.attr);
  return 0;
}

// Cleanup function will be called on module unload.
static void __exit cleanup_solution(void) {
  kobject_put(solution_kobj);
}

// Specify what functions to call on module load and unload.
module_init(init_solution);
module_exit(cleanup_solution);


MODULE_AUTHOR("Dima Timofeev");
// These macros are required. Without license specification a module will not
// compile.
MODULE_LICENSE("GPL");