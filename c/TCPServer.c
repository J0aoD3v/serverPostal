#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORTA 8089
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Falha no WSAStartup\n");
        return 1;
    }

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Falha na criacao do socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORTA);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Falha no bind: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Falha no listen: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("SERVIDOR INICIADO NA PORTA %d\n", PORTA);
    printf("Aperte Ctrl + C para encerrar o servidor.\n");

    while (1) {
        SOCKET client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (client_fd == INVALID_SOCKET) {
            printf("Falha no accept: %d\n", WSAGetLastError());
            continue;
        }

        printf("CONEXAO ESTABELECIDA COM %s\n", inet_ntoa(address.sin_addr));

        char buffer[BUFFER_SIZE];
        int bytes_received;
        while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            buffer[bytes_received] = '\0';
            if (buffer[bytes_received - 1] == '\n')
                buffer[bytes_received - 1] = '\0';
            printf("Cliente >> %s\n", buffer);
            memset(buffer, 0, BUFFER_SIZE);
        }

        printf("Cliente desconectado: %s\n", inet_ntoa(address.sin_addr));
        closesocket(client_fd);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}
