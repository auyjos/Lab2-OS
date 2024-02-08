#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // Crear un proceso hijo
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Proceso hijo
        execl("./ipc", "./ipc", "2", "A", (char *)NULL);
        perror("Error al ejecutar el programa ipc en el proceso hijo");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Proceso padre
        printf("Proceso padre: Iniciando la primera instancia de ipc\n");
        // Esperar a que el proceso hijo termine
        wait(NULL);

        // Crear otro proceso hijo
        pid_t pid2 = fork();

        if (pid2 < 0)
        {
            perror("Error al crear el segundo proceso hijo");
            exit(EXIT_FAILURE);
        }
        else if (pid2 == 0)
        {
            // Proceso hijo 2
            execl("./ipc", "./ipc", "3", "B", (char *)NULL);
            perror("Error al ejecutar el programa ipc en el segundo proceso hijo");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Proceso padre
            printf("Proceso padre: Iniciando la segunda instancia de ipc\n");
            // Esperar a que el segundo proceso hijo termine
            wait(NULL);
        }
    }

    return 0;
}
