#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_PIDS 32767

int getProcessWithParent() {
	int pids[MAX_PIDS];
	for (int i=0; i<MAX_PIDS; i++)
		pids[i] = -1;

	DIR* proc = opendir("/proc");
	struct dirent* de;

	int cnt = 0;

	while ((de = readdir(proc)) != NULL) {
		if (strstr(de->d_name, ".") != NULL)
			continue;
		if (strstr(de->d_name, ".") != NULL)
			continue;
		if (de->d_type == DT_DIR && atoi(de->d_name) > 0) {
			pids[cnt] = atoi(de->d_name);
			cnt++;
		}
	}
	
	closedir(proc);
	return cnt;
}

int main() {
	int c = getProcessWithParent();
	printf("Processes: %i\n", c);
	return 0;
}
