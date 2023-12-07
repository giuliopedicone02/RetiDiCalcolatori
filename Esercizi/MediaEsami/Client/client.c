#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

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

void initStruct(Messaggio m)
{
    m.scelta = -1;
    memset(m.nomeEsame, '\0', sizeof(m.nomeEsame));
    m.valutazione = 0;
}

int main(int argc, char **argv)
{
    int sockfd, n;
    struct sockaddr_in remote_addr;
    char sendline[1000];
    char recvline[1000];
    socklen_t len = sizeof(struct sockaddr_in);

    if (argc != 3)
    {
        printf("usage:  UDPclient <remote_IP remote_port>\n");
        return 1;
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\nError in socket opening ... exit!");
        return -1;
    }

    memset(&remote_addr, 0, len);
    remote_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));
    remote_addr.sin_port = htons(atoi(argv[2]));

    Messaggio m;
    initStruct(m);

    while (1)
    {
        printf("Effettua una scelta:\n");
        printf("1) Inserisci una nuova valutazione\n");
        printf("2) Ottieni la media dei voti\n\n");

        printf("Inserisci scelta: ");
        scanf("%d", &m.scelta);
        getchar();

        sendto(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, len);
        recvfrom(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, &len);

        printf("%s\n", m.messaggioDalServer);

        if (m.scelta - 1 == INSERIMENTO)
        {
            printf("Inserisci il nome dell'esame da registrare: ");
            fgets(m.nomeEsame, sizeof(m.nomeEsame), stdin);
            m.nomeEsame[strlen(m.nomeEsame) - 1] = '\0';

            printf("Inserisci valutazione: ");
            scanf("%d", &m.valutazione);

            sendto(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, len);
            recvfrom(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, &len);

            printf("%s\n", m.messaggioDalServer);
        }

        if (m.scelta - 1 == MEDIA)
        {
            recvfrom(sockfd, &m, sizeof(Messaggio), 0, (struct sockaddr *)&remote_addr, &len);
            printf("%s\n", m.messaggioDalServer);
        }
    }
}
