#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_LEN 8192

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	int (*original_connect)(int,const struct sockaddr*, socklen_t) = NULL;
	original_connect = dlsym(RTLD_NEXT, "connect");
	
	struct sockaddr_in *myaddr = (struct sockaddr_in*)addr;
	
	char *fam = "OTHER";
	if (addr->sa_family == AF_INET)
		fam = "AF_INET";

	char address_str[BUFFER_LEN] = {0};
	if (addr->sa_family == AF_INET) {
		inet_ntop(addr->sa_family, &(myaddr->sin_addr.s_addr), address_str, BUFFER_LEN);
	}

	char host[BUFFER_LEN] = {0};
	char server[BUFFER_LEN] = {0};
	getnameinfo(addr, addrlen,
		    host, BUFFER_LEN,
		    server, BUFFER_LEN, 0);
	printf("%s (%s) %s\n",host, fam, address_str);

	return original_connect(sockfd, addr, addrlen);
}
