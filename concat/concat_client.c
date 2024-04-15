#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// helper functions implemented in util.c

/* This function initializes the given "struct sockaddr".
 * For servers, set "ip" to "NULL"; for clients, set "ip" to the server's IP
 */
void init_sockaddr(struct sockaddr *in_addr, const char *ip, int port);

/* This function fills in "len" number of random chars to "str_buf" and a tailing '\0'.
 * The function assumes that "str_buf" points to a memory of size at lease "len+1".
 */
void rand_str(char *str_buf, int len);

// printing function; please don't touch
void print_msg(char *msg) {
    printf("=<%s>=\n", msg);
}

#define NUM_TRANSMISSIONS 10

void client(char *ip, int port) {
    /* Client should establish a connection to the server,
     * send a 10-char string, and receive data from the server.
     * Here is HOWTO:
     *  - Create the socket for the client
     *  - Create "struct sockaddr" and use "init_sockaddr()" to initialize it
     *  - Connect this socket to the server
     *  - When encountering errors, print errors using "perror" and quit
     */

    /* TODO: your code here */


    for (int i=0; i<NUM_TRANSMISSIONS; i++) {
        /* Here, client should send random generated strings to the server.
         * Here is HOWTO:
         *  - Generate a random string of length 10 using rand_str() function
         *    -- pay attention to the tailing '\0'
         *  - Send random string to the server
         *  - Receive concatenated data back from server
         *  - Print out concatenated data using "print_msg()"
         *  - When encountering errors, print errors using "perror" and quit
         */
        /* TODO: your code here */

    }

    // TODO: close socket
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        printf("Usage: concat_client server_port [server_address] [random_seed]\n");
        exit(1);
    }

    char *ip = "127.0.0.1";
    if (argc > 2) {
        ip = argv[2];
    }

    if (argc == 4) {
        srandom(atoi(argv[3]));
    } else {
        srandom(3650);
    }

    int port = atoi(argv[1]);

    client(ip, port);
}
