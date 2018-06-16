#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int static cnt1 = 0;
void usr1SigHdl(int signo) {
	cnt1++;
}

int static cnt2 = 0;
void usr2SigHdl(int signo) {
	cnt2++;
}

void termSigHdl(int signo) {
	printf("%i %i\n", cnt1, cnt2);
	exit(0);
}

int main() {
	signal(SIGUSR1, usr1SigHdl);
	signal(SIGUSR2, usr2SigHdl);
	signal(SIGTERM, termSigHdl);
	while(1)
		usleep(500);
	return 0;
}
