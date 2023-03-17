/**
 * Un file di testo rubrica.txt contiene una rubrica del telefono, in cui per ogni persona è memorizzato
 * • nome (stringa di 20 caratteri senza spazi, incluso terminatore)
 * • indirizzo (stringa di 30 caratteri senza spazi, incluso ‘\0’)
 * • numero(stringa di 15 caratteri incluso ‘\0’)
 *
 * Si scriva un programma C che legge da tastiera un nome, cerca la persona corrispondente nel file rubrica.txt
 * e visualizza sullo schermo i dati della persona (se trovata)
 */

#include <stdio.h>
#include <string.h>

struct Persona
{
    char nome[21];
    char indirizzo[31];
    char numero[16];
};

int main()
{
    FILE *file = fopen("rubrica.txt", "r");
    char cerca[21];

    if (file == NULL)
    {
        printf("File non trovato!");
        return 0;
    }

    struct Persona persone[100];
    int i = 0, dim = 0;

    while (!feof(file))
    {
        fscanf(file, "%s", &persone[i].nome);
        fscanf(file, "%s", &persone[i].indirizzo);
        fscanf(file, "%s", &persone[i].numero);
        i++;
    }

    dim = i;

    printf("Inserisci il nome di una persona da cercare: ");
    scanf("%s", cerca);

    for (int i = 0; i < dim; i++)
    {
        if (strcmp(cerca, persone[i].nome) == 0)
        {
            printf("\n\033[1;32mHo trovato %s ecco le sue informazioni: \033[0m", cerca);
            printf("\n\nNome: %s, Indirizzo: %s, Numero: %s", persone[i].nome, persone[i].indirizzo, persone[i].numero);
            return 0;
        }
    }

    printf("\n\033[1;31mMi dispiace, non ho trovato %s in rubrica\033[0m", cerca);
}