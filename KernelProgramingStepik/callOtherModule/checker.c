#include <linux/module.h>

void call_me(const char* message) {
	printk(KERN_INFO "Hello");
}
EXPORT_SYMBOL(call_me);

int init_module(void) {
	return 0;
}

void cleanup_module(void) {}
