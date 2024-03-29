#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int sockfd, n;
    struct sockaddr_in remote_addr, local_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char msg[1000];

    if (argc != 4)
    {
        printf("Errore! Devi inserire 4 parametri!");
        return 0;
    }

    if (!fork()) // Processo figlio
    {
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            printf("Errore nell'apertura del socket");
            return -1;
        }

        memset(&local_addr, 0, len);
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(atoi(argv[1]));

        if (bind(sockfd, (struct sockaddr *)&local_addr, len) < 0)
        {
            printf("Errore nella bind\n");
            return -1;
        }

        for (;;)
        {
            n = recvfrom(sockfd, msg, 999, 0, (struct sockaddr *)&remote_addr, &len);
            msg[n] = 0;

            printf("Messaggio: %s, IP: %s, Porta: %d\n", msg, inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));
        }

        close(sockfd);
        return 0;
    }
    else // Processo padre
    {
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            printf("Errore nell'apertura del socket");
            return -1;
        }

        int broadcastEnable = 1;
        int ret = setsockopt(sockd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

        memset(&remote_addr, 0, len);
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(atoi(argv[1]));
        inet_pton(AF_INET, "255.255.255.255", &(remote_addr.sin_addr));

        while (fgets(msg, 1000, stdin) != NULL)
        {
            sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr *)&remote_addr, len);
        }

        close(sockfd);
        return 0;
    }

    return 0;
}