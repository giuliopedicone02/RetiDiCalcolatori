#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    while (!feof(f))
    {
        char data[5];

        fscanf(f, "%s", people[i].cognome);
        fscanf(f, "%s", people[i].nome);
        fscanf(f, "%s", people[i].sesso);

        fscanf(f, "%s", data);
        people[i].nascita = atoi(data);

        printf("\nCognome: %s, Nome: %s, Sesso: %s, Nascita: %d", people[i].cognome, people[i].nome, people[i].sesso, people[i].nascita);
        i++;
    }
}