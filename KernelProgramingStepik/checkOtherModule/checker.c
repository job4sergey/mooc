#include <stddef.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/random.h>

#define CHECKER_MACRO printk("CHECKER_MACRO");


int array_sum(short* arr, size_t n) {
	int res = 0;
	size_t i;
	for (i=0; i<n; i++) {
		res = res + arr[i];
	}
	return res;
}
EXPORT_SYMBOL(array_sum);


ssize_t generate_output(int sum, short *arr, size_t size, char *buf) {
	size_t i;
	ssize_t index = 0;
	index += sprintf(&buf[index], "%d ", sum);
	for (i=0; i<size; i++) {
	   index += sprintf(&buf[index], "%d ", arr[i]);
	}
	return index;
}
EXPORT_SYMBOL(generate_output);


static int __init my_init(void) {
	return 0;
}


static void __exit my_exit(void) {
}


module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
