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

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORTA);

    char *host = "127.0.0.1";
    if (inet_pton(AF_INET, host, &servaddr.sin_addr) <= 0) {
        printf("Endereco invalido\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    char buffer[BUFFER_SIZE];

    printf("Digite mensagens (escreva 'FIM' para encerrar):\n");
    while (1) {
        printf("Cliente >> ");
        fflush(stdout);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = 0;

        if (sendto(sockfd, buffer, strlen(buffer), 0, 
                   (const struct sockaddr *)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
            printf("Falha no envio: %d\n", WSAGetLastError());
            continue;
        }

        if (_stricmp(buffer, "FIM") == 0) {
            printf("Conexao encerrada\n");
            break;
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
