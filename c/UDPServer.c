#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORTA 8089
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("Falha no WSAStartup\n");
        return 1;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Falha na criacao do socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORTA);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("Falha no bind: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("SERVIDOR UDP INICIADO NA PORTA %d\n", PORTA);
    printf("Aperte Ctrl + C para encerrar o servidor.\n");

    char buffer[BUFFER_SIZE];
    int len = sizeof(cliaddr);

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&cliaddr, &len);
        if (n == SOCKET_ERROR) {
            printf("Erro no recvfrom: %d\n", WSAGetLastError());
            continue;
        }

        buffer[n] = '\0';
        printf("Cliente (%s) >> %s\n", inet_ntoa(cliaddr.sin_addr), buffer);
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
