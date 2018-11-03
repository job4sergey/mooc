#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

int func42(void) {
  return 42;
}

EXPORT_SYMBOL(func42);

static int __init init_solution(void) {
  return 0;
}

static void __exit cleanup_solution(void) {
}

module_init(init_solution);
module_exit(cleanup_solution);


MODULE_AUTHOR("Dima Timofeev");
MODULE_LICENSE("GPL");