#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Proceso hijo
        for (int i = 1; i <= 4000000; i++)
        {
            printf("Conteo en el proceso hijo: %d\n", i);
        }
    }
    else if (pid > 0)
    {
        // Proceso padre
        while (1)
        {
            // Ciclo while infinito
        }
    }

    return 0;
}
