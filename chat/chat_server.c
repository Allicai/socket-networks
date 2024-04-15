#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// implemented in util.c
extern void init_sockaddr(struct sockaddr *in_addr, const char *ip, int port);


char *bad_words[3] =  {"virus", "worm", "malware"};
char *good_words[3] = {"groot", "hulk", "ironman"};

/* Replace bad words in "str" to the corresponding good words.
 * - Bad/good words are defined in "bad_words"/"good_words" (arrays defined above)
 * - Partial word does not count: for example, you can ignore "malwareXYZ".
 * - You should return a string with replaced words.
 * - hints:
 *   -- strtok() is useful
 *   -- Notice that the corresponding bad and good words are of the same length.
 */
char *replace_bad_words(char *str) {
    /* TODO: your code here */

    return NULL;
}


/* the chat server will accept two clients and forward messages between them. */
void server(int port) {
    /* For server:
     *  - Create a socket to listen on port for new connections.
     *  - Bind the server's socket to port.
     *  - Put listener_socket in LISTEN mode
     *  - Accept two connections from two clients
     *  - When encountering errors, print errors using "perror" and quit
     */
    /* TODO: your code here */

    while(1) {
        /* Next:
         *  - Use "select" to see which socket is available to read from
         *    -- we don't care about writefds and exceptfds; we don't timeout
         *    -- remember to clear "fd_set"
         *  - Check to see if connection is closed
         *  - Replace bad words using "replace_bad_words()"
         *  - Forward to the other socket
         *  - Quit when either client closes the socket
         *  - When encountering errors, print errors using "perror" and quit
         */

        /* TODO: your code here */

    }

    // TODO: close created sockets
}


int main(int argc, char *argv[]) {
    if (argc < 2 || argc >3) {
        printf("Usage: chat_server server_port\n");
        exit(1);
    }

    int port = atoi(argv[1]);
    server(port);
}
