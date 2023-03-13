#include <stdio.h>

struct automobile
{
    char *marca;
    char *modello;
    int venduto;
};

struct data
{
    int giorno;
    char *mese;
    int anno;
};

int main()
{
    struct automobile a1;

    a1.marca = "FERRARI";
    a1.modello = "F40";
    a1.venduto = 200;

    printf("Marca auto = %s", a1.marca);
    printf("\nModello auto = %s", a1.modello);
    printf("\nVendute = %d", a1.venduto);

    struct data *pd, oggi;

    oggi.giorno = 13;
    oggi.mese = "Marzo";
    oggi.anno = 2023;

    pd = &oggi;

    (*pd).giorno = 31;      // pd->giorno
    (*pd).mese = "Gennaio"; // pd->mese
    (*pd).anno = 2023;      // pd->anno

    printf("\n\nGiorno = %d", pd->giorno);
    printf("\nMese = %s", pd->mese);
    printf("\nAnno = %d", pd->anno);
}