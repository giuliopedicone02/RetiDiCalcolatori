#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h> //Socket

int main(int argc, char **argv)
{
    int sockfd, n;
    struct sockaddr_in local_addr, dest_addr;
    char buffer[100];
    socklen_t len = sizeof(struct sockaddr_in);

    if (argc < 2)
    {
        printf("Errore! Devi inserire la porta! \n");
        return 0;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        printf("Errore nell'apertura del socket");
        return -1;
    }

    memset(&local_addr, 0, len); // Setta a 0 tutta local_addr
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1])); // Host to Network

    if (bind(sockfd, (struct sockaddr *)&local_addr, len) < 0)
    {
        printf("Errore nella bind. Inserisci un altro numero di porta\n");
        return -1;
    }

    n = recvfrom(sockfd, buffer, 99, 0, (struct sockaddr *)&dest_addr, &len);
    buffer[n] = 0;

    printf("IP %s, Port %d, Messaggio %s\n", inet_ntoa(dest_addr.sin_addr), ntohs(dest_addr.sin_port), buffer);

    close(sockfd);

    return 0;

    // Si esegue con ./receiver NumeroDiPorta
    // Esempio ./receiver 192.168.56.103 5050
}
