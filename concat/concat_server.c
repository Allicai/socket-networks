#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


// helper functions implemented in util.c

/* This function initializes the given "struct sockaddr".
 * For servers, set "ip" to "NULL"; for clients, set "ip" to the server's IP
 */
void init_sockaddr(struct sockaddr *in_addr, const char *ip, int port);

/* This function fills in "len" number of random chars to "str_buf" and a tailing '\0'.
 * The function assumes that "str_buf" points to a memory of size at lease "len+1".
 */
void rand_str(char *str_buf, int len);


void server(int port) {
    /*
     * Server should establish a listening socket and accept
     * connections from clients.
     * Here is HOWTO:
     *  - Create a socket for the server on localhost
     *  - Create "struct sockaddr" and use "init_sockaddr()" to initialize it
     *  - Bind the socket to the server port
     *  - Put server's socket in LISTEN mode
     *  - Call accept to wait for a connection
     *  - When encountering errors, print errors using "perror" and quit
     * */

    /* TODO: your code here */
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t clilen;
    char buffer[11]; // Buffer for received data from the client
    char random_str[11]; // Buffer for random string
    char concatenated_str[21]; // Buffer for concatenated string

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Initialize sockaddr structure
    init_sockaddr((struct sockaddr*)&server_addr, NULL, port);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }
    // listen for connection
    listen(sockfd, 5);


    while(1) {
        /*
         * Here, server receives a string, concatenates a 10-char string, and
         * returns the new string.
         * Here is HOTWO:
         *  - Receive data over the socket returned by the accept() method
         *    -- Exit the loop when client closes connection
         *  - Generate a new string of length 10 using rand_str()
         *    -- pay attention to the tailing '\0'
         *  - Append the string to the data received
         *    -- "strcat" is useful
         *  - Send the new string back to the client
         *  - When encountering errors, print errors using "perror" and quit
         */

        /* TODO: your code here */
        clilen = sizeof(client_addr);

        // accept client connection
        new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &clilen);
        if (new_sockfd < 0) {
            perror("Error accepting connection");
            exit(1);
        }

        while (1) {
            // getting data from client
            int bytes_received = recv(new_sockfd, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received < 0) {
                perror("Error receiving data from client");
                exit(1);
            } else if (bytes_received == 0) {
                // client closes 
                break;
            }

            // Null-terminate received data
            buffer[bytes_received] = '\0';

            // Generate random string
            rand_str(random_str, sizeof(random_str) - 1);

            // Concatenate received data and random string
            snprintf(concatenated_str, sizeof(concatenated_str), "%s%s", buffer, random_str);

            // Send concatenated string back to client
            if (send(new_sockfd, concatenated_str, strlen(concatenated_str), 0) < 0) {
                perror("Error sending data to client");
                exit(1);
            }
        }

        // Close client socket
        close(new_sockfd);
    }
    // TODO: close all sockets that were created
    close(sockfd);

}


int main(int argc, char *argv[]) {
    if (argc < 2 || argc >3) {
        printf("Usage: concat_server server_port [random_seed]\n");
        exit(1);
    }

    if (argc == 3) {
        srandom(atoi(argv[2]));
    } else {
        srandom(3650);
    }

    int port = atoi(argv[1]);
    server(port);
}

