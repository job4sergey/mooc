#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIDS 1000 

static int cnt = 1;

void findChildren(int pid, const int *pids, const int *ppids) {
	int i;
	for (i=0; i<MAX_PIDS; i++) {
		if (pid == ppids[i]) {
			cnt++;
			findChildren(pids[i], pids, ppids);
		}
	}
}

int main(int c, char **v) {
	int pids[MAX_PIDS];
	int ppids[MAX_PIDS];
	
	FILE *f = popen("cat /proc/*/status | grep '\\(^Pid\\|^PPid\\)'", "r"); 
	int i = 0;
	char pidstr[256]; char ppidstr[256];
	while (fgets(pidstr, sizeof(pidstr), f)) {
		fgets(ppidstr, sizeof(ppidstr), f);
		
		// Copy process IDs
		char pid[21];
		pid[20] = '\0';
		strncpy(pid, pidstr+5, 20);
		pids[i] = atoi(pid);
		// Copy parent process IDs
		char ppid[21];
		ppid[20] = '\0';
		strncpy(ppid, ppidstr+5, 20);
		ppids[i] = atoi(ppid);

		i++;
	}
	pclose(f);
	
	// Main logic
	findChildren(atoi(v[1]), pids, ppids);
	printf("%i\n", cnt);
	return 0;
}
