#include <stdio.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <string.h>
#include <unistd.h>

int comp (const void * elem1, const void * elem2) {
	char f = *((char*)elem1);
	char s = *((char*)elem2);
	if (f < s) return 1;
	if (f > s) return -1;
	return 0;
}
int main(int c, char **v) {
	// Server's socket
	int ss = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in local;
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(atoi(v[1]));
	local.sin_family = AF_INET;

	bind(ss, (struct sockaddr*) &local, sizeof(local));
	listen(ss, 5);
	int cs = accept(ss, NULL, NULL); 

	// Read from client's socket
	char buf[BUFSIZ];
	while (1) {
		int i; for(i=0; i < BUFSIZ; i++) buf[i] = 0;
		read(cs, buf, BUFSIZ);
		if (strncmp(buf, "OFF\n", 4) == 0) return 0;
		qsort(buf, strlen(buf), 1, comp);
		write(cs, buf, strlen(buf));

	}
	close(cs);

	return 0;
}
