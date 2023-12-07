#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define PORT 8080

int main(int argc, char const *argv[])
{
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];

    if (argc < 2)
    {
        fprintf(stderr, "use %s <port server>", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Creazione della socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione della socket
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Connessione del server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("errore nella connessione al server\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Inserisci il messsaggio da inviare al server: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer) - 1] = '\0';

        if (send(client_socket, buffer, sizeof(buffer), 0) < 0)
        {
            perror("errore nell'invio dei dati");
            exit(EXIT_FAILURE);
        }

        memset(buffer, 0, sizeof(buffer));

        if (recv(client_socket, buffer, sizeof(buffer), 0) < 0)
        {
            perror("errore nella ricezione dei messaggi");
            exit(EXIT_FAILURE);
        }

        printf("[Server]: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}