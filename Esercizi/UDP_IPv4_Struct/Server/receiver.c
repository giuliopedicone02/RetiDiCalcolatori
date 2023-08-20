#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_RESP "Server's answer: "
#define MAX_MSG_SIZE 1000
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
    struct sockaddr_in server_addr, client_addr;
    char server_message[MAX_MSG_SIZE], client_message[MAX_MSG_SIZE];
    socklen_t client_struct_length = sizeof(client_addr);
    size_t strl = strlen(SERVER_RESP);

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Error while creating socket");
        return 1;
    }

    printf("Socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Non è possibile fare la bind sulla porta");
        return -1;
    }

    printf("Bind effettuata\n");

    printf("In attesa di messaggi...\n\n");

    Giocatore p1;

    for (;;)
    {
        if (recvfrom(sockfd, &p1, sizeof(p1), 0, (struct sockaddr *)&client_addr, &client_struct_length) < 0)
        {
            perror("Non è possibile effettuare la recvfrom");
            return -1;
        }

        printf("Ricevuto messaggio da IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        printf("---Messaggio dal client--- \n");

        printf("Nome : %s\n", p1.nome);
        printf("Eta : %d\n", p1.age);
        printf("Valutazione : %d\n", p1.value);

        sprintf(server_message, "Ho ricevuto le informazioni sul giocatore : %s\n", p1.nome);

        if (sendto(sockfd, server_message, strlen(server_message), 0, (struct sockaddr *)&client_addr, client_struct_length) < 0)
        {
            perror("Non si può inviare una risposta");
            return 1;
        }
    }

    close(sockfd);

    return 0;
}