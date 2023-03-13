#include <stdio.h>

struct automobile
{
    char *marca;
    char *modello;
    int venduto;
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
}