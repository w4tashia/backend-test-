#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9090);
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.19");

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int conn = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (conn < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    printf("Connected to server!\n");

    const char *msg = "Hello, server!";
    ssize_t bytes_sent = send(sock, msg, strlen(msg), 0);
    if (bytes_sent < 0) {
        perror("send");
    }

    close(sock);

    return 0;
};