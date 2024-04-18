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
    int sockfd;
    struct sockaddr_in server_addr;

    // creating socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // creating sockaddr struct
    init_sockaddr((struct sockaddr*)&server_addr, ip, port);

    // connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    char buffer[256]; // user input


    // Repeat until server goes down or user stops entering in data
    while(1) {
        /* Next:
         *  - Send data to server if stdin has data (i.e. when user typed in data and pressed enter)
         *  - Receive data from server if socket has data coming in
         *  - When encountering errors, print errors using "perror" and quit
         *  - Print the received message on screen using print_msg().
         */

        /* TODO: your code here */
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int maxfd = (sockfd > STDIN_FILENO) ? sockfd : STDIN_FILENO;
        select(maxfd + 1, &readfds, NULL, NULL, NULL);

        // If socket has data, receive and print message
        if (FD_ISSET(sockfd, &readfds)) {
            int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) {
                perror("Error receiving data from server");
                exit(1);
            }
            buffer[bytes_received] = '\0';
            print_msg(buffer);
        }

        // If stdin has data, send message to server
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            fgets(buffer, sizeof(buffer), stdin);
            if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
                perror("Error sending data to server");
                exit(1);
            }
        }

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
