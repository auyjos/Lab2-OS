#include <stdio.h>
#include <unistd.h>

int main()
{
    int i;

    for (i = 0; i < 4; i++)
    {
        fork();
        printf("Proceso creado en iteración %d\n", i + 1);
    }

    return 0;
}
