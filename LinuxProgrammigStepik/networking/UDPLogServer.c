#include <stdio.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <string.h>
#include <unistd.h>

#define BUFS 5121

int main(int c, char **v) {
	int s = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in local;
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(atoi(v[1]));
	local.sin_family = AF_INET;

	int result = bind(s, (struct sockaddr*) &local, sizeof(local));

	char data[BUFS];
	while(1) {
		int i; for(i=0; i < BUFS-1; i++) data[i] = 0;
		read(s, data, BUFS);
		data[BUFS-1] = '\0';
		if (strncmp(data, "OFF\n", 4) == 0) return 0;
		printf("%s\n", data);
	}
	return 0;
}
