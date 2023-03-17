/**
 * Si scriva su un file di testo testo.txt
 * quello che l’utente inserisce da tastiera parola per parola,
 * finché non inserisce la parola "FINE" (usando la fprintf).
 */

#include <stdio.h>
#include <string.h>

int main()
{
    FILE *file = fopen("testo.txt", "w");
    char parola[30];

    while (strcmp(parola, "FINE"))
    {
        printf("Inserisci una parola: ");
        scanf("%s", parola);
        fprintf(file, "%s\n", parola);
    }

    fclose(file);
}