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

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Falha na criacao do socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORTA);

    char *host = "127.0.0.1";
    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
        printf("Endereco invalido\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("Falha na conexao: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Digite mensagens (escreva 'FIM' para encerrar):\n");

    char buffer[BUFFER_SIZE];
    while (1) {
        printf("Cliente >> ");
        fflush(stdout);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = 0; // remove \n

        if (send(sock, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            printf("Falha no envio: %d\n", WSAGetLastError());
            break;
        }

        if (_stricmp(buffer, "FIM") == 0) {
            printf("Conexao encerrada\n");
            break;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
