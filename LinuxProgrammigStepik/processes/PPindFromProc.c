#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	char statFilePath[256];
	snprintf(statFilePath, sizeof statFilePath, "/proc/%i/stat", getpid());
	FILE* f = fopen(statFilePath, "r");

        int x;
	int spaceCnt = 0;
	while ((x=fgetc(f)) != EOF) {
		if (x==32) {
		spaceCnt++;
		}
		if (spaceCnt==3 && x!=32) {
			printf("%c", x);	
		}		
	}
	printf("\n");
	fclose(f);
	return 0;
}
