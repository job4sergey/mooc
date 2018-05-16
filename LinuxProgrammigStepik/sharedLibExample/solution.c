#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count) {
	size_t len = strlen(string);
	(*count)++;
	return len*multiplier;
}

