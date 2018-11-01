#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <checker.h>

static void *p = NULL;
static void *ap = NULL;
static struct device *sp = NULL;


// Init function will be called on the module start up.
static int __init init_solution(void) {
  // 1.
  ssize_t size = get_void_size();
  p = kmalloc(size, GFP_KERNEL);
  submit_void_ptr(p);

  // 2. 
  size = get_int_array_size();
  ap = kmalloc_array(size, sizeof(int), GFP_KERNEL);
  submit_int_array_ptr(ap);
  
  // 3.
  sp = kmalloc(sizeof(struct device), GFP_ATOMIC);
  submit_struct_ptr(sp);
  return 0;
}

// Cleanup function will be called on module unload.
static void __exit cleanup_solution(void) {
  // 1
  checker_kfree(p);
  // 2
  checker_kfree(ap);
  ap = NULL;
  // 3
  checker_kfree(sp);
}

// Specify what functions to call on module load and unload.
module_init(init_solution);
module_exit(cleanup_solution);


MODULE_AUTHOR("Dima Timofeev");
// These macros are required. Without license specification a module will not
// compile.
MODULE_LICENSE("GPL");