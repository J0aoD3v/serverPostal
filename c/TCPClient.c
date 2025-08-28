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
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char *host = "127.0.0.1";
    
    printf("Digite mensagens (escreva 'FIM' para encerrar):\n");
    
    // Criar socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Falha na criação do socket");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORTA);
    
    // Converter endereço IP
    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
        perror("Endereço inválido");
        close(sock);
        return -1;
    }
    
    // Conectar ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Falha na conexão");
        close(sock);
        return -1;
    }
    
    while (1) {
        printf("Cliente >> ");
        fflush(stdout);
        
        // Ler entrada do usuário
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        // Remover quebra de linha
        buffer[strcspn(buffer, "\n")] = 0;
        
        // Enviar mensagem
        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            perror("Falha no envio");
            break;
        }
        
        if (strcasecmp(buffer, "FIM") == 0) {
            printf("Conexão encerrada\n");
            break;
        }
    }
    
    close(sock);
    return 0;
}