#include <stddef.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/random.h>


extern int array_sum(short*, size_t);
extern ssize_t generate_output(int, short*, size_t, char*);


short* generate_array(void) {
	static short arr[10];
	int i;
	for (i=0; i<10; i++) {
		// Generate only 1 random byte.
		get_random_bytes(&arr[i], 1);
	}
	return arr;
}

int check_array_sum(short* arr, size_t n) {
	int res = 0;
	size_t i;
	for (i=0; i<n; i++) {
		res = res + arr[i];
	}
	return res;
}

static int __init my_init(void) {
	int i;
	for (i=0; i<12; i++) {
		short* arr = generate_array();
		int sum = array_sum(arr, 10);
		int true_sum = check_array_sum(arr, 10);
		char buf[128];
		ssize_t osize = generate_output(sum, arr, 10, buf);
		if (true_sum == sum) {
			printk(KERN_INFO "%s", buf);
		} 
		else {
			printk(KERN_ERR "%s", buf);
		}
	}
	return 0;
}


static void __exit my_exit(void) {
}


module_init(my_init);
module_exit(my_exit);
