/**
 * @file client.c
 * @author Tend (casablancaernesto@gmail.com)
 * @brief Semplice client tcp ipv4
 * @version 0.1
 * @date 2023-05-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MSG_SIZE 2000
#define PORT 2000

struct Message
{
    int operazione;
    char username[20];
    int numeroFile;
    char files[30][256];
    int porta;
};

int sendLoginRegistrazione(int sockfd)
{
    struct Message m;

    m.operazione = 1; // Login - Registazione

    printf("Inserisci un username: ");
    scanf("%s", &m.username);

    printf("Inserisci numero di files da condividere (max 30): ");
    scanf("%d", &m.numeroFile);

    for (int i = 0; i < m.numeroFile; i++)
    {
        printf("Inserisci file %d: ", i + 1);
        scanf("%s", &m.files[i]);
    }

    printf("Inserisci porta di ascolto: ");
    scanf("%d", &m.porta);

    if (send(sockfd, &m, sizeof(m), 0) < 0)
    {
        perror("Unable to send message");
        return 1;
    }
}

int stampaListaUtenti(int sockfd)
{
    struct Message m;

    m.operazione = 2; // Stampa Lista Utenti

    if (send(sockfd, &m, sizeof(m), 0) < 0)
    {
        perror("Unable to send message");
        return 1;
    }

    return 0;
}

int stampaFilePerUtente(int sockfd)
{
    struct Message m;

    m.operazione = 3; // Stampa Lista Utenti

    printf("Inserisci username dei file da cercare: ");
    scanf("%s", &m.username);

    if (send(sockfd, &m, sizeof(m), 0) < 0)
    {
        perror("Unable to send message");
        return 1;
    }

    return 0;
}

int logout(int sockfd)
{
    struct Message m;

    m.operazione = 5; // Uscita

    if (send(sockfd, &m, sizeof(m), 0) < 0)
    {
        perror("Unable to send message");
        return 1;
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;
    char server_message[MAX_MSG_SIZE], client_message[MAX_MSG_SIZE];
    socklen_t server_struct_length = sizeof(server_addr);

    FILE *file = fopen("lista.txt", "r");

    if (argc < 2)
    {
        fprintf(stderr, "use: %s address\n", argv[0]);
        return 1;
    }

    // Azzera tutte le strutture dati. '\0' e 0 sono equivalenti
    memset(&server_addr, 0, server_struct_length);
    memset(server_message, 0, sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Creazione del socket.
    // Dato che tcp è il protocollo di default per SOCK_STREAM, il terzo parametro può essere 0
    // sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_TCP);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error while creating socket");
        return 1;
    }
    printf("Socket created successfully\n");

    // Si impostano le informazioni del server a cui connettersi
    // In questo esempio porta e indirizzo sono hard-coded
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Si apre una connessione al server
    if (connect(sockfd, (struct sockaddr *)&server_addr, server_struct_length) < 0)
    {
        perror("Unable to connect");
        return 1;
    }

    for (;;)
    {
        printf("\n\n*** Effettua una scelta: ***\n");
        printf("1. Registrazione/Login\n");
        printf("2. Visualizza gli utenti registrati\n");
        printf("3. Visualizza lista dei file di un client\n");
        printf("4. Scaricare un file\n");
        printf("5. Esci\n");
        printf("> ");

        int scelta = 0;
        scanf("%d", &scelta);
        printf("Hai selezionato %d\n", scelta);

        switch (scelta)
        {
        case 1:

            printf("Registazione/Login\n");
            sendLoginRegistrazione(sockfd);
            break;

        case 2:

            printf("Lista utenti\n");
            stampaListaUtenti(sockfd);
            break;

        case 3:

            printf("Lista file per utente\n");
            stampaFilePerUtente(sockfd);
            break;

        case 4:

            printf("Download\n");
            break;

        case 5:

            printf("Esci\n");
            logout(sockfd);
            close(sockfd);
            return 0;

        default:

            printf("Default\n");
            continue;
        }

        int n = 0;

        n = recv(sockfd, server_message, sizeof(server_message), 0);

        // Si riceve la risposta del server
        if (n < 0)
        {
            perror("Error while receiving server's msg");
            return 1;
        }

        server_message[n] = 0;

        printf("\n\n *** Risposta del server: ***\n\n%s", server_message);

        sleep(3);
    }

    // Si chiude il socket
    close(sockfd);

    return 0;
}