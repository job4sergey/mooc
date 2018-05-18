#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

int (*target_function)(int);

bool init_library(const char* libname, const char* funcname) {
	void* hdl = dlopen(libname, RTLD_LAZY);
	if (hdl == NULL) {
		return false;
	}

	target_function = (int(*)(int))dlsym(hdl, funcname);
	if (target_function == NULL) {
		return false;
	}

	return true;
}

int main(int argc, char* argv[]) {
	char* libpath = argv[1];
	char libpathModified[strlen(libpath)+2];
	strcat(libpathModified, "./");
	strcat(libpathModified, libpath);
	char* funcname = argv[2];
	char* funcarg = argv[3];

	if (init_library(libpathModified, funcname)) {
		printf("%i\n", target_function(atoi(funcarg)));
	}
	return 0;
}
