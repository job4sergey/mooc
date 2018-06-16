#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void sigurgHndl(int signo) {
	printf("%i\n", getpid());
	exit(0);
}

int main() {
	signal(SIGURG, sigurgHndl);
	//fclose(stdout);
	daemon(0, 0);
	while (1)
		sleep(100);
	return 0;
}
