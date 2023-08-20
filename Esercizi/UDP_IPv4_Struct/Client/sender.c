#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MSG_SIZE 2000
#define PORT 2000

typedef struct
{
    char nome[20];
    int age;
    int value;
} Giocatore;

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in server_addr;
    char server_message[MAX_MSG_SIZE], client_message[MAX_MSG_SIZE];
    socklen_t server_struct_length = sizeof(server_addr);

    if (argc < 2)
    {
        fprintf(stderr, "use : %s address \n", argv[0]);
        return 1;
    }

    memset(&server_addr, 0, server_struct_length);
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Errore creazione della socket\n");
        return 1;
    }

    printf("Socket creata correttamente\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    Giocatore p1;
    char s = '\0';

    printf("Vuoi un inserire un giocatore ? \n");
    printf("Se si inserisci la lettera s : ");
    scanf(" %c", &s);
    getchar();

    while (s == 's')
    {
        char buffer[100];
        buffer[0] = '\0';
        printf("\nInserire nome: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer) - 1] = '\0';
        strcpy(p1.nome, buffer);

        printf("Inserire anni: ");
        fgets(buffer, sizeof(buffer), stdin);
        p1.age = atoi(buffer);

        printf("Inserire valutazione: ");
        fgets(buffer, sizeof(buffer), stdin);
        p1.value = atoi(buffer);

        if (sendto(sockfd, &p1, sizeof(p1), 0, (struct sockaddr *)&server_addr, server_struct_length) < 0)
        {
            perror("Errore invio messaggio");
            return 1;
        }

        if (recvfrom(sockfd, server_message, sizeof(server_message), 0, (struct sockaddr *)&server_addr, &server_struct_length) < 0)
        {
            perror("Errore ricezione messaggio");
            return 1;
        }

        printf("Risposta del server: \n%s\n\n", server_message);

        printf("Vuoi un inserire un giocatore ? \n");
        printf("Se si inserisci la lettera s : ");
        scanf("%c", &s);
        getchar();
    }

    close(sockfd);
    return 0;
}