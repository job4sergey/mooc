#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

bool ProcHasName(char* procdir, char* pname) {
	// Create a path to the file with a run command
	char statPath[256];
	snprintf(statPath, sizeof statPath, "/proc/%s/cmdline", procdir);
	
	// Open the file with the run command
	FILE* f = fopen(statPath, "r");
	char cmd[1024]; int i=0; char x;
	while ((x=fgetc(f)) != EOF) {
		cmd[i] = x;
		i++;	
	}
	fclose(f);
	
	if (strstr(cmd, pname) != NULL) {
		return true;
	}
	return false;
}

int main() {
	char* targetPName = "nano";
	DIR* proc = opendir("/proc");
	struct dirent *de;  // Pointer for directory entry
	int cnt = 0;
	while ((de = readdir(proc)) != NULL) {
		if (strstr(de->d_name, ".") != NULL)
			continue;
		if (strstr(de->d_name, ".") != NULL)
			continue;
		if (atoi(de->d_name) < 1)
			continue;
		if (de->d_type == DT_DIR && ProcHasName(de->d_name, targetPName)) {
			cnt++;
		}
	}
        closedir(proc);
	printf("%i\n", cnt);	
	return 0;
}
