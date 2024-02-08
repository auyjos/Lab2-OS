#include <stdio.h>
#include <unistd.h>

int main()
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if (fork() == 0)
        {
            printf("Proceso creado en iteración %d\n", i + 1);
            break; // Se detiene el bucle en el proceso hijo
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int j = 0; j < 4; j++)
    {
        wait(NULL);
    }

    return 0;
}
