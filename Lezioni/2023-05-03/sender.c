#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in dest_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[100];

    if (argc < 3)
    {
        printf("Errore: Inserisci IP e Porta");
        return 0;
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\nErrore nell'apertura del socket");
        return -1;
    }

    memset(&dest_addr, 0, len);
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(dest_addr.sin_addr));
    dest_addr.sin_port = htons(atoi(argv[2])); // htons() = host to network

    printf("\nInserisci una parola: ");
    scanf("%d", &buffer);

    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&dest_addr, len);

    close(sockfd);
    return 0;

    // Si esegue con ./sender indirizzoIPServer NumeroDiPorta
    // Esempio ./sender 192.168.56.103 5050
}