#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    clock_t inicio, fin;

    // Medición de tiempo antes del fork
    inicio = clock();

    // Fork para crear el proceso hijo
    pid_t pid = fork();

    if (pid == 0)
    { // Código del proceso hijo
        // Fork para crear el proceso nieto
        pid_t pid_nieto = fork();

        if (pid_nieto == 0)
        { // Código del proceso nieto (bisnieto)
            // Ciclo for del bisnieto
            for (int i = 0; i < 1000000; i++)
            {
                // No se realiza ninguna acción dentro del bucle
            }
        }
        else
        { // Código del proceso hijo
            // Ciclo for del hijo
            for (int i = 0; i < 1000000; i++)
            {
                // No se realiza ninguna acción dentro del bucle
            }

            // Espera a que termine el bisnieto
            wait(NULL);
        }
    }
    else
    { // Código del proceso padre
        // Ciclo for del padre
        for (int i = 0; i < 1000000; i++)
        {
            // No se realiza ninguna acción dentro del bucle
        }

        // Espera a que termine el hijo
        wait(NULL);

        // Medición de tiempo después de la ejecución concurrente
        fin = clock();

        // Cálculo y despliegue del tiempo transcurrido
        double tiempo_concurrente = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
        printf("Tiempo transcurrido concurrente: %f segundos\n", tiempo_concurrente);
    }

    return 0;
}
