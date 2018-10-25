#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>
#include <linux/slab.h>

static struct kt_date {
  struct hrtimer timer;
  ktime_t period;
};

static enum hrtimer_restart kfun(struct hrtimer *val) {
  pr_info("Function was triggered by timer.\n");
  return HRTIMER_NORESTART;
}

static long delays[1024] = {0};
static int arrcnt = 0;
module_param_array(delays, long, &arrcnt, 0660); 

// Init function will be called on the module start up.
static int __init init_solution(void) {
  pr_info("Start loading module.\n");
  data = kmalloc(sizeof(struct kt_date), GFP_KERNEL);
  data->period = ktime_set(1, 0); // 1 sec

  hrtimer_init(&data->timer, CLOCK_REALTIME, HRTIMER_MODE_REL);
  data->timer.function = kfun;
  hrtimer_start(&data->timer, data->period, HRTIMER_MODE_REL);

  return 0;
}

// Cleanup function will be called on module unload.
static void __exit cleanup_solution(void) {
  kfree(data);
  data = NULL;
}

// Specify what functions to call on module load and unload.
module_init(init_solution);
module_exit(cleanup_solution);


MODULE_AUTHOR("Dima Timofeev");
// These macros are required. Without license specification a module will not
// compile.
MODULE_LICENSE("GPL");