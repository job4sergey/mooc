#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUZZ_SIZE 1024


int getParentPid(int pid) {
	char buff[BUZZ_SIZE];
	char strPath[256];
	snprintf(strPath, sizeof strPath, "/proc/%i/status", pid);	
	FILE *f = fopen(strPath, "r");
	for (int i=0; i<6; i++)
		fgets(buff, BUZZ_SIZE, f);
	fclose(f);

	char subbuff[BUZZ_SIZE-6];
	for (int i=0; i<BUZZ_SIZE-6; i++)
		subbuff[i] = buff[i+6];
	int ppid = atoi(subbuff);
	return ppid;
}


int main(int argc, char **argv) {
	int pid = atoi(argv[1]);
	printf("%i\n", pid);
	while(pid != 1) {
		pid = getParentPid(pid);
		printf("%d\n", pid);
	}
	return 0;
}
