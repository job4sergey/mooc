#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	printf("%i\n", getpid());
	fclose(stdout);
	daemon(0, 0);
	sleep(1000);
	return 0;
}
