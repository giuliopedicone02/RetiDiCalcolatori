#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h> //Socket

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    char buffer[100];
    socklen_t len = sizeof(struct sockaddr_in);

    if (argc < 2)
    {
        printf("Devi inserire la porta \n");
        exit(0);
    }

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        printf("Errore nell'apertura del socket");
        return -1;
    }

    memset(&local_addr, 0, sizeof(local_addr)); // Setta a 0 tutta local_addr
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1])); // Host to Network

    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("Errore nella bind. Inserisci un altro numero di porta\n");
        return -1;
    }

    for (;;)
    {
        recvfrom(sockfd, buffer, 99, 0, (struc sockaddr *)&remote_addr, &len);
        printf("IP %s, Port %d, Messaggio %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), buffer)
    }

    close(sockfd);

    return 0;
}
