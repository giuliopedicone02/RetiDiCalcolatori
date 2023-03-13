#include <stdio.h>

int main()
{
    int n = 5;
    int *p = &n;

    printf("Indirizzo (p): %p \nVariabile (*p): %d", p, *p);

    n += 5;

    printf("\n%d", *p);

    *p = 20;

    printf("\n%d\n", *p);

    /**
     * Aritmetica dei puntatori
     */

    int a[10] = {0};

    for (int i = 0; i < 10; i++)
    {
        a[i] = i + 1;
    }

    printf("\nArray = [ ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", *(a + i));
    }
    printf("]");
}