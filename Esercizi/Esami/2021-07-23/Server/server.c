/**
 * @file server.c
 * @author Tend (casablancaernesto@gmail.com)
 * @brief Semplice server tcp ipv4
 * @version 0.1
 * @date 2023-05-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_RESP "Server's answer: "
#define MAX_MSG_SIZE 1000
#define PORT 2000
#define N_ACCEPT 5

struct Message
{
    int operazione;
    char username[20];
    int numeroFile;
    char files[30][256];
    int porta;
};

int isRegistrato(struct Message m)
{
    FILE *file = fopen("utenti.txt", "r");
    char user[20];
    int porta;

    if (file == NULL)
    {
        printf("File non trovato!\n");
        return 0;
    }

    rewind(file);

    while (!feof(file))
    {
        fscanf(file, "%s", &user);
        fscanf(file, "%d", &porta);

        if (strcmp(m.username, user) == 0)
        {
            return 1; // Utente trovato
        }
    }

    return 0; // Utente non trovato
}

void insertUtente(struct Message m)
{
    FILE *file = fopen("utenti.txt", "a+");

    if (file == NULL)
    {
        printf("File non trovato!\n");
        return;
    }

    rewind(file);

    fprintf(file, "%s %d\n", m.username, m.porta);

    fclose(file);

    return;
}

void insertFileDisponibili(struct Message m)
{
    FILE *file = fopen("files.txt", "a+");

    if (file == NULL)
    {
        printf("File non trovato!\n");
        return;
    }

    rewind(file);

    fprintf(file, "%s %d", m.username, m.numeroFile);

    for (int i = 0; i < m.numeroFile; i++)
    {
        fprintf(file, " %s", m.files[i]);
    }

    fprintf(file, "\n");

    fclose(file);

    return;
}

int loginRegistrazione(struct Message m)
{
    if (isRegistrato(m) == 1)
    {
        printf("Utente registrato\n");
        return 0;
    }
    else
    {
        insertUtente(m);
        insertFileDisponibili(m);
        return 1;
    }
}

void stampaInfoRegistrazione(struct Message m)
{
    printf("Username: %s\n", m.username);
    printf("Porta di ascolto: %d\n", m.porta);
    printf("Lista dei files: \n");

    for (int i = 0; i < m.numeroFile; i++)
    {
        printf("%s\n", m.files[i]);
    }
}

char *stampaListaUtenti()
{
    FILE *file = fopen("utenti.txt", "r");
    char *buffer, user[40];
    buffer = malloc(sizeof(char) * 1000);
    int porta;

    if (file == NULL)
    {
        printf("File non trovato!\n");
        return 0;
    }

    while (fgets(user, sizeof(user), file) != NULL)
    {
        strcat(buffer, user);
    }

    fclose(file);
    return buffer;
}

char *stampaListaFileUtenti(char *username)
{
    FILE *file = fopen("files.txt", "r");
    char *buffer, user[40], filename[40];
    buffer = malloc(sizeof(char) * 1000);
    int numeroFiles = 0;

    if (file == NULL)
    {
        printf("File non trovato!\n");
        return 0;
    }

    while (!feof(file))
    {
        fscanf(file, "%s", &user);

        if (strcmp(username, user) == 0) // Utente trovato
        {
            fscanf(file, "%d", &numeroFiles);

            for (int i = 0; i < numeroFiles; i++)
            {
                fscanf(file, "%s", &filename);
                strcat(buffer, filename);
                strcat(buffer, "\n");
            }

            return buffer;
        }
        else // Utente non trovato, cerco ancora...
        {
            fscanf(file, "%d", &numeroFiles);

            for (int i = 0; i < numeroFiles; i++)
            {
                fscanf(file, "%s", &filename);
            }
        }
    }

    fclose(file);
    return "NOT FOUND"; // Utente non trovato
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char server_message[MAX_MSG_SIZE], client_message[MAX_MSG_SIZE];
    socklen_t client_struct_length = sizeof(client_addr);
    size_t strl = strlen(SERVER_RESP);

    // Azzera tutte le strutture dati. '\0' e 0 sono equivalenti
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Creazione del socket.
    // Dato che upd è il protocollo di default per SOCK_STREAM, il terzo parametro può essere 0
    // sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error while creating socket");
        return 1;
    }
    printf("Socket created successfully\n");

    // Si impostano le informazioni del server
    // In questo esempio la porta è hard-coded
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // Il server accetta connessioni da qualsiasi indirizzo

    // Si associa il socket all'indirizzo e alla porta
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Couldn't bind to the port");
        return -1;
    }
    printf("Done with binding\n");

    // Si è disposti ad accettare le richieste di connessione in arrivo
    if (listen(sockfd, N_ACCEPT) < 0)
    {
        perror("Could't listen to connections");
        return 1;
    }

    int sockfd_conn = accept(sockfd, (struct sockaddr *)&client_addr, &client_struct_length);
    if (sockfd_conn < 0)
    {
        perror("Couldn'd accept new connection");
        return 1;
    }

    printf("Listening for incoming messages...\n\n");

    for (;;)
    {
        struct Message m;
        char server_message[MAX_MSG_SIZE] = {0};

        if (recv(sockfd_conn, &m, sizeof(m), 0) < 0)
        {
            perror("Couldn't receive");
            return -1;
        }

        printf("Received message from IP: %s and port: %i\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        switch (m.operazione)
        {
        case 1:

            printf("Richiesta di Login/Registrazione da: %s\n", m.username);

            // stampaInfoRegistrazione(m); Decommentare per visualizzare info passate al server

            int result = loginRegistrazione(m);

            if (result == 0)
            {
                strcpy(server_message, "\033[1;32mUTENTE GIA REGISTRATO\n\033[0m");
            }
            else if (result == 1)
            {
                strcpy(server_message, "\033[1;32mREGISTRAZIONE EFFETTUATA CON SUCCESSO\n\033[0m");
            }

            if (send(sockfd_conn, server_message, strlen(server_message), 0) < 0)
            {
                perror("Can't send");
                return 1;
            }

            break;

        case 2:

            printf("Richiesta Lista utenti\n");
            strcpy(server_message, stampaListaUtenti());

            if (send(sockfd_conn, server_message, strlen(server_message), 0) < 0)
            {
                perror("Can't send");
                return 1;
            }

            break;

        case 3:

            printf("Richiesta lista file dell'utente %s\n", m.username);

            strcpy(server_message, stampaListaFileUtenti(m.username));

            if (strcmp(server_message, "NOT FOUND") == 0) // Utente non trovato
            {
                strcpy(server_message, "\033[1;31mUTENTE NON TROVATO\n\033[0m");
            }

            if (send(sockfd_conn, server_message, strlen(server_message), 0) < 0)
            {
                perror("Can't send");
                return 1;
            }

            break;

        case 4:

            printf("Download\n");
            break;

        case 5:

            printf("Disconnessione avvenuta con successo\n");
            close(sockfd_conn);
            close(sockfd);

            return 0;

        default:

            printf("Default\n");
            continue;
        }
    }

    // Si prepara il messaggio da inviare al client
    strcat(server_message, SERVER_RESP);
    strncat(server_message + strl, client_message, sizeof(client_message) - strl);

    // Si invia il messaggio al client
    if (send(sockfd_conn, server_message, strlen(server_message), 0) < 0)
    {
        perror("Can't send");
        return 1;
    }

    // Si chiude il socket
    close(sockfd_conn);
    close(sockfd);

    return 0;
}