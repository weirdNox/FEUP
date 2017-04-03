#include <stdio.h>
#include "fila.c"

int main()
{
    for(;;)
    {
        int n;
        scanf("%d", &n);
        if(!n)
        {
            break;
        }

        fila *baralho = fila_nova();
        if(!baralho)
        {
            fprintf(stderr, "Erro ao criar fila\n");
            return -1;
        }
        for(int i = 1; i <= n; ++i)
        {
            char buffer[100];
            sprintf(buffer, "%d", i);
            fila_push(baralho, buffer);
        }

        int first = 1;
        printf("Discarded cards:");
        while(fila_tamanho(baralho) >= 2)
        {
            if(!first)
            {
                printf(",");
            }
            printf(" %s", fila_front(baralho));
            fila_pop(baralho);
            fila_push(baralho, fila_front(baralho));
            fila_pop(baralho);
            first = 0;
        }

        printf("\nRemaining card: %s\n", fila_front(baralho));
        fila_apaga(baralho);
    }

    return 0;
}
