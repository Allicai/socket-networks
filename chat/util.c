#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void init_sockaddr(struct sockaddr *in_addr, const char *ip, int port) {
    struct sockaddr_in *addr = (struct sockaddr_in *) in_addr;
    addr->sin_family = AF_INET;
    if (ip == NULL) {
        addr->sin_addr.s_addr = INADDR_ANY;
    } else {
        if(inet_pton(AF_INET, ip, &addr->sin_addr) <= 0) {
            printf("Error: invalid address or address not supported\n");
            exit(1);
        }
    }
    addr->sin_port = htons(port);
}
