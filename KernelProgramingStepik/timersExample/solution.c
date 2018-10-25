#include <checker.h>
#include <linux/hrtimer.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/time64.h>


#define NSEC_PER_MSEC	1000000L

static struct hrtimer hr_timer;
static ktime_t ktime;

static unsigned long delays[1024] = {0};
static int arrcnt;
module_param_array(delays, long, &arrcnt, 0660);

static int delay_cnt = 0;

static enum hrtimer_restart kfun(struct hrtimer *val) {
  delay_cnt++;
  check_timer();
  if (delay_cnt >= arrcnt) {
    return HRTIMER_NORESTART;
  }
  ktime = ktime_set(0, delays[delay_cnt] * NSEC_PER_MSEC);
  hrtimer_forward_now(&hr_timer, ktime_set(0, delays[delay_cnt] * NSEC_PER_MSEC));
  return HRTIMER_RESTART;
}

// Init function will be called on the module start up.
static int __init init_solution(void) {
  ktime = ktime_set(0, delays[0] * NSEC_PER_MSEC);

  hrtimer_init(&hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  hr_timer.function = &kfun;
  check_timer();
  hrtimer_start(&hr_timer, ktime, HRTIMER_MODE_REL);
  return 0;
}

// Cleanup function will be called on module unload.
static void __exit cleanup_solution(void) {
  	hrtimer_cancel(&hr_timer);
}

// Specify what functions to call on module load and unload.
module_init(init_solution);
module_exit(cleanup_solution);


MODULE_AUTHOR("Dima Timofeev");
// These macros are required. Without license specification a module will not
// compile.
MODULE_LICENSE("GPL");