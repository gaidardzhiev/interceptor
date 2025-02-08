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

int i(int s, const struct sockaddr *a, socklen_t addrlen) {
	int (*c)(int,const struct sockaddr*, socklen_t) = NULL;
	c = dlsym(RTLD_NEXT, "connect");
	struct sockaddr_in *myaddr = (struct sockaddr_in*)a;
	char *fam = "OTHER";
	if (a->sa_family == AF_INET)
		fam = "AF_INET";
	char address_str[BUFFER_LEN] = {0};
	if (a->sa_family == AF_INET) {
		inet_ntop(a->sa_family, &(myaddr->sin_addr.s_addr), address_str, BUFFER_LEN);
	}
	char host[BUFFER_LEN] = {0};
	char server[BUFFER_LEN] = {0};
	getnameinfo(a, addrlen,
		    host, BUFFER_LEN,
		    server, BUFFER_LEN, 0);
	printf("%s (%s) %s\n",host, fam, address_str);
	return c(s, a, addrlen);
}
