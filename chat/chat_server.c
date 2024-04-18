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

    char *token;
    char *result = strdup(str);
    if (result == NULL) {
        perror("Error duplicating string");
        exit(1);
    }

    // iterate over each bad word
    for (int i = 0; i < 3; i++) {
        // finding a bad word in a string
        while ((token = strstr(result, bad_words[i])) != NULL) {
            // replace the bad word with good word
            strncpy(token, good_words[i], strlen(good_words[i]));
        }
    }

    return result;
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
    int listener_socket, client_socket[2];
    struct sockaddr_in server_addr, client_addr;
    socklen_t clilen;

    // create sockaddr
    listener_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // creating sockaddr struct
    init_sockaddr((struct sockaddr*)&server_addr, NULL, port);

    // bind sock to addr
    if (bind(listener_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    // listen for connections
    listen(listener_socket, 2);

    // accepting two connections from the two clients
    for (int i = 0; i < 2; i++) {
        clilen = sizeof(client_addr);
        client_socket[i] = accept(listener_socket, (struct sockaddr *)&client_addr, &clilen);
        if (client_socket[i] < 0) {
            perror("Error accepting connection");
            exit(1);
        }
    }

    char buffer[256];

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
        
        // read data from client 0 and send it to client 1
        ssize_t bytes_received_0 = recv(client_socket[0], buffer, sizeof(buffer), 0);
        if (bytes_received_0 > 0) {
            buffer[bytes_received_0] = '\0';
            char *replaced_message = replace_bad_words(buffer);
            ssize_t bytes_sent_1 = send(client_socket[1], replaced_message, strlen(replaced_message), 0);
            free(replaced_message);
            if (bytes_sent_1 < 0) {
                perror("Error sending data to client 1");
                exit(1);
            }
        } else if (bytes_received_0 == 0) {
            // client 0 closed the connection
            break;
        } else {
            perror("Error receiving data from client 0");
            exit(1);
        }

        // read the data from client 1 and send it to client 0
        ssize_t bytes_received_1 = recv(client_socket[1], buffer, sizeof(buffer), 0);
        if (bytes_received_1 > 0) {
            buffer[bytes_received_1] = '\0';
            char *replaced_message = replace_bad_words(buffer);
            ssize_t bytes_sent_0 = send(client_socket[0], replaced_message, strlen(replaced_message), 0);
            free(replaced_message);
            if (bytes_sent_0 < 0) {
                perror("Error sending data to client 0");
                exit(1);
            }
        } else if (bytes_received_1 == 0) {
            // client 1 closes connection
            break;
        } else {
            perror("Error receiving data from client 1");
            exit(1);
        }
    }

    // TODO: close created sockets
    close(listener_socket);
    close(client_socket[0]);
    close(client_socket[1]);
}


int main(int argc, char *argv[]) {
    if (argc < 2 || argc >3) {
        printf("Usage: chat_server server_port\n");
        exit(1);
    }

    int port = atoi(argv[1]);
    server(port);
}
