#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int x = 0, i;
    int pid;

    for (i = 0; i < 10; i++)
    {
        x = x + i;
        printf("x = %d\n", x);
    }

    // top: Permette di vedere i process inattivi in linux

    pid = fork();

    if (pid == 0) // Processo figlio
    {
        for (i = 0; i < 10; i++)
        {
            x -= i;
            printf("PID %d, x = %d\n", pid, x);
        }
    }
    else // Processo padre
    {
        for (i = 0; i < 5; i++)
        {
            x += i;
            printf("PID %d, x = %d\n", pid, x);
        }
    }

    return 0;
}