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

#define BUF 8192

int i(int s, const struct sockaddr *a, socklen_t z) {
	int (*c)(int,const struct sockaddr*, socklen_t) = NULL;
	c = dlsym(RTLD_NEXT, "connect");
	struct sockaddr_in *myaddr = (struct sockaddr_in*)a;
	char *fam = "OTHER";
	if (a->sa_family == AF_INET)
		fam = "AF_INET";
	char address_str[BUF] = {0};
	if (a->sa_family == AF_INET) {
		inet_ntop(a->sa_family, &(myaddr->sin_addr.s_addr), address_str, BUF);
	}
	char host[BUF] = {0};
	char server[BUF] = {0};
	getnameinfo(a,z,host,BUF,server,BUF,0);
	printf("%s (%s) %s\n",host,fam,address_str);
	return c(s,a,z);
}
