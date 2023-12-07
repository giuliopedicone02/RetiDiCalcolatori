#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

typedef enum
{
    INSERIMENTO,
    MEDIA
} Operazione;

typedef struct
{
    Operazione scelta;
    char nomeEsame[21];
    char messaggioDalServer[51];
    int valutazione;
} Messaggio;

int main(int argc, char **argv)
{
    int sockfd, n;
    extern int errno;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char mesg[1000];

    if (argc < 2)
    {
        printf("Use: server listening_PORT");
        return 0;
    }

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\nError in socket opening ... exit!");
        return -1;
    }

    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));
    if (bind(sockfd, (struct sockaddr *)&local_addr, len) < 0)
    {
        printf("\nBinding error! Error code n.%d \n", errno);
        return -1;
    }

    Messaggio m;
    int sommaVoti = 0, numeroEsami = 0;

    while (1)
    {
        recvfrom(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, &len);

        if (m.scelta - 1 == INSERIMENTO)
        {
            printf("[Client: %s] Vuole aggiungere un nuovo esame\n", inet_ntoa(remote_addr.sin_addr));

            strcpy(m.messaggioDalServer, "Hai scelto di aggiugnere un nuovo esame\n");

            sendto(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, len);

            // Resto in attesa di ricevere un nuovo esame

            recvfrom(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, &len);

            sommaVoti += m.valutazione;
            numeroEsami++;

            strcpy(m.messaggioDalServer, "Esame aggiunto con successo!\n");

            sendto(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, len);
        }
        else if (m.scelta - 1 == MEDIA)
        {
            printf("[Client: %s] Vuole sapere la media dei voti\n", inet_ntoa(remote_addr.sin_addr));

            strcpy(m.messaggioDalServer, "Hai scelto di conoscere la media dei tuoi voti\n");

            sendto(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, len);

            float avg = (float)(sommaVoti / numeroEsami);

            sprintf(m.messaggioDalServer, "La media dei tuoi voti è la seguente: %.2f\n", avg);

            sendto(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, len);
        }
    }
}
