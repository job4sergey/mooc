#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

extern int func42(void);

static int __init init_solution(void) {
  pr_info("The answer is: %i\n", func42());
  return 0;
}

static void __exit cleanup_solution(void) {
}

module_init(init_solution);
module_exit(cleanup_solution);


MODULE_AUTHOR("Dima Timofeev");
MODULE_LICENSE("GPL");