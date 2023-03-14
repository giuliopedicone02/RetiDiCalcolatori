#include <stdio.h>

struct persone
{
    char cognome[31];
    char nome[31];
    char sesso[2];
    int nascita;
};

int main()
{
    FILE *f = fopen("people.txt", "r");

    struct persone people[100];
    int i = 0;

    printf("\033[1;37m"); // Bianco in grassetto
    printf("\n---------------------------------------------------------\n");
    printf("Cognome\t\tNome\t\tSesso\t\tNascita");
    printf("\n---------------------------------------------------------");
    printf("\033[0m"); // Reset colori

    while (!feof(f))
    {
        char data[5];

        fscanf(f, "%s", &people[i].cognome);
        fscanf(f, "%s", &people[i].nome);
        fscanf(f, "%s", &people[i].sesso);
        fscanf(f, "%d", &people[i].nascita);

        printf("\n%s\t\t%s\t\t%s\t\t%d", people[i].cognome, people[i].nome, people[i].sesso, people[i].nascita);
        i++;
    }
}