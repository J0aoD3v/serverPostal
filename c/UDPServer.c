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
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[BUFFER_SIZE];
    
    printf("SERVIDOR UDP INICIADO NA PORTA %d\n", PORTA);
    printf("Aperte Ctrl + C para encerrar o servidor.\n");
    
    // Criar socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Configurar endereço do servidor
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORTA);
    
    // Bind do socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Falha no bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    len = sizeof(cliaddr);
    
    while (1) {
        // Receber dados do cliente
        int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE - 1, 0, 
                        (struct sockaddr *)&cliaddr, &len);
        
        if (n < 0) {
            perror("Erro no recvfrom");
            continue;
        }
        
        buffer[n] = '\0';
        printf("Cliente (%s) >> %s\n", inet_ntoa(cliaddr.sin_addr), buffer);
    }
    
    close(sockfd);
    return 0;
}