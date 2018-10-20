#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/rtc.h>

static struct kobject *solution_kobj;
static int cnt = 0;

irqreturn_t irq8_handler(int irq, void *dev) {
  cnt++;
  return IRQ_HANDLED;
}

/*
 * The "my_sys" file where a static variable is read from and written to.
 */
static ssize_t solution_attr_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	return sprintf(buf, "%i\n", cnt);
}

/* Sysfs attributes cannot be world-writable. */
static struct kobj_attribute solution_attr =
	__ATTR(my_sys, 0755, solution_attr_show, NULL);

// Init function will be called on the module start up.
static int __init init_solution(void) {
  int retval = 0;

  // Register kobject with attributes.
  solution_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
  retval = sysfs_create_file(solution_kobj, &solution_attr.attr);

  // Register an interrupt handler.
  retval = request_irq(8, irq8_handler, IRQF_SHARED, "rtc", 1);
  if (retval < 0) {
    pr_alert("Request IRQ failed: %i\n", retval);
  }

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