#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <número> <letra>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Instancia: Creando o uniéndose a la memoria compartida\n");

    // Obtener el número y la letra desde los argumentos de la línea de comandos
    int n = atoi(argv[1]);
    char x = argv[2][0];

    printf("Instancia: n = %d, x = %c\n", n, x);

    // Crear o unirse a un espacio de memoria compartida
    key_t key = ftok("ipc.c", 1);
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);

    if (shmid < 0)
    {
        perror("Instancia: Error al crear o unirse a la memoria compartida");
        exit(EXIT_FAILURE);
    }

    // Obtener el file descriptor del espacio de memoria compartida
    int shmdesc = shmget(key, sizeof(int), 0);

    // Verificar si ya se ha abierto la memoria compartida por la otra instancia
    if (shmid != shmdesc)
    {
        // Recibir el file descriptor de la otra instancia
        shmdesc = shmid;
        printf("Instancia: Recibí el file descriptor de la memoria compartida de la otra instancia\n");
    }
    else
    {
        // Enviar el file descriptor a la otra instancia
        printf("Instancia: Envié el file descriptor de la memoria compartida a la otra instancia\n");
    }

    // Mapear la memoria compartida a un puntero
    int *mem_ptr = (int *)shmat(shmdesc, NULL, 0);

    // Crear un proceso hijo
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Instancia: Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Proceso hijo
        for (int i = 0; i < *mem_ptr; ++i)
        {
            if (i % n == 0)
            {
                // Escribir la letra en la memoria compartida si la iteración es divisible por n
                mem_ptr[i] = x;
                printf("Instancia: Escribiendo '%c' en la posición %d\n", x, i);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Proceso padre
        wait(NULL); // Esperar a que el proceso hijo termine

        // Desplegar el contenido de la memoria compartida
        printf("Instancia: Contenido de la memoria compartida:\n");
        for (int i = 0; i < *mem_ptr; ++i)
        {
            printf("%c ", mem_ptr[i]);
        }
        printf("\n");

        // Desvincular y liberar la memoria compartida
        shmdt(mem_ptr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
