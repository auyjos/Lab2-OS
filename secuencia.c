#include <stdio.h>
#include <time.h>

int main()
{
    clock_t inicio, fin;

    // Medición de tiempo antes del primer ciclo for
    inicio = clock();

    // Primer ciclo for
    for (int i = 0; i < 1000000; i++)
    {
        // No se realiza ninguna acción dentro del bucle
    }

    // Segundo ciclo for
    for (int i = 0; i < 1000000; i++)
    {
        // No se realiza ninguna acción dentro del bucle
    }

    // Tercer ciclo for
    for (int i = 0; i < 1000000; i++)
    {
        // No se realiza ninguna acción dentro del bucle
    }

    // Medición de tiempo después del último ciclo for
    fin = clock();

    // Cálculo y despliegue del tiempo transcurrido
    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo transcurrido secuencial: %f segundos\n", tiempo);

    return 0;
}
