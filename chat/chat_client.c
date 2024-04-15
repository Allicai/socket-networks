#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// implemented in util.c
extern void init_sockaddr(struct sockaddr *in_addr, const char *ip, int port);

// printing function; please don't touch
void print_msg(char *msg) {
    printf("%s\n", msg);
}


/* Connect this client to the chat server and wait user's input from stdin */
void client(char *ip, int port) {
    /*
     * Here is HOWTO:
     *  - Create a socket for the client
     *  - Connect client to the server at the given port
     *  - When encountering errors, print errors using "perror" and quit
     */
    /* TODO: your code here */


    // Repeat until server goes down or user stops entering in data
    while(1) {
        /* Next:
         *  - Send data to server if stdin has data (i.e. when user typed in data and pressed enter)
         *  - Receive data from server if socket has data coming in
         *  - When encountering errors, print errors using "perror" and quit
         *  - Print the received message on screen using print_msg().
         */

        /* TODO: your code here */


    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: concat_client server_port [server_address]\n");
        exit(1);
    }

    char *ip = "127.0.0.1";
    if (argc > 2) {
        ip = argv[2];
    }
    int port = atoi(argv[1]);
    client(ip, port);
}
