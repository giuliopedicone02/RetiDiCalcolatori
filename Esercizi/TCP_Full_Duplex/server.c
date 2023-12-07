#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

#define MAX_BUFFER_SIZE 1024
#define PORT 8080

int main(int argc, char const *argv[])
{

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[MAX_BUFFER_SIZE];

    if (argc < 2)
    {
        fprintf(stderr, "use %s <port server>", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Creazione della socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // binding
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("errore nella bind");
        exit(EXIT_FAILURE);
    }

    // listen
    if (listen(server_socket, 5) < 0)
    {
        perror("errore nella listen");
        exit(EXIT_FAILURE);
    }

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len)) < 0)
    {
        perror("errore nell'accettazione della socket");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        memset(buffer, 0, MAX_BUFFER_SIZE);

        // Attesa della ricezione di un messaggio da parte del client
        if (recv(client_socket, buffer, sizeof(buffer), 0) < 0)
        {
            perror("errore nella ricezione");
            exit(EXIT_FAILURE);
        }

        printf("[Client]: %s\n", buffer);

        printf("Inserisci il messsaggio da inviare al client: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer) - 1] = '\0';

        if (send(client_socket, buffer, sizeof(buffer), 0) < 0)
        {
            perror("errore nell'invio del messaggio");
        }
    }

    close(client_socket);
    close(server_socket);

    return 0;
}