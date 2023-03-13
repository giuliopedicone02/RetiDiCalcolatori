#include <stdio.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Impossibile aprire il file");
        return 1;
    }
    char buffer[100];
    while (fgets(buffer, 100, file) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}
