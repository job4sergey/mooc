#include <linux/module.h>

extern void call_me(const char*);

int init_module(void) {
	char* str = "Hello from my module!";
	call_me(str);
	return 0;
}

void cleanup_module(void) {}
