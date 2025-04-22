//#define _GNU_SOURCE

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

#define B 65536

int x(int y, const struct sockaddr *z, socklen_t d) {
	int (*f)(int, const struct sockaddr*, socklen_t) = NULL;
	f = dlsym(RTLD_NEXT, "connect");
	struct sockaddr_in *j = (struct sockaddr_in*)z;
	char *v = "OTHER";
	if (z->sa_family == AF_INET)
		v = "AF_INET";
	char t[B] = {0};
	if (z->sa_family == AF_INET) {
		inet_ntop(z->sa_family, &(j->sin_addr.s_addr), t, B);
	}
	char h[B] = {0};
	char s[B] = {0};
	getnameinfo(z, d, h, B, s, B, 0);
	printf("%s (%s) %s\n", h, v, t);
	return f(y, z, d);
}
