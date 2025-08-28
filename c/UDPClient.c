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
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE];
    char *host = "127.0.0.1";
    
    printf("Digite mensagens (escreva 'FIM' para encerrar):\n");
    
    // Criar socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    
    // Configurar endereço do servidor
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORTA);
    
    if (inet_pton(AF_INET, host, &servaddr.sin_addr) <= 0) {
        perror("Endereço inválido");
        close(sockfd);
        exit(EXIT_FAILURE);
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
        
        // Enviar dados para o servidor
        if (sendto(sockfd, buffer, strlen(buffer), 0, 
                  (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
            perror("Falha no envio");
            continue;
        }
        
        if (strcasecmp(buffer, "FIM") == 0) {
            printf("Conexão encerrada\n");
            break;
        }
    }
    
    close(sockfd);
    return 0;
}