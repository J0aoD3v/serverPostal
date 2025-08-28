#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTA 8089
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    printf("SERVIDOR INICIADO NA PORTA %d\n", PORTA);
    printf("Aperte Ctrl + C para encerrar o servidor.\n");
    
    // Criar socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }
    
    // Configurar endereço
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORTA);
    
    // Bind do socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Falha no bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    // Escutar conexões
    if (listen(server_fd, 3) < 0) {
        perror("Falha no listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        // Aceitar conexão
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Falha no accept");
            continue;
        }
        
        printf("CONEXÃO ESTABELECIDA COM %s\n", inet_ntoa(address.sin_addr));
        
        // Receber mensagens
        int bytes_received;
        while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            buffer[bytes_received] = '\0';
            // Remove quebra de linha se existir
            if (buffer[bytes_received - 1] == '\n') {
                buffer[bytes_received - 1] = '\0';
            }
            printf("Cliente >> %s\n", buffer);
            memset(buffer, 0, BUFFER_SIZE);
        }
        
        printf("Cliente desconectado: %s\n", inet_ntoa(address.sin_addr));
        close(client_fd);
    }
    
    close(server_fd);
    return 0;
}