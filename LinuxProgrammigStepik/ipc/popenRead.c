#include <stdio.h>

int main(int argc, char* argv[]) {
	// Concat arguments
	char buf[100];
	sprintf(buf, "%s %s", argv[1], argv[2]);

	// Read the pipe
	FILE *p = popen(buf, "r");
	int zeroCnt = 0;
	char c;
	while ((c=fgetc(p)) != EOF) {
		if (c == '0')
			zeroCnt++;
	}
	pclose(p);
	printf("%i\n", zeroCnt);
	return 0;
}
