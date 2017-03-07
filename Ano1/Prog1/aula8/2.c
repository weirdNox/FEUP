#include <stdio.h>
#include <stdlib.h>

int contaRepeticao(int v[], int tamanhoVetor, int numero)
{
    int currentStreak = 0, maxStreak = 0;
    for(int i = 0; i < tamanhoVetor; ++i)
    {
        if(v[i] == numero)
        {
            ++currentStreak;
            maxStreak = (currentStreak>maxStreak) ? currentStreak : maxStreak;
        }
        else
        {
            currentStreak = 0;
        }
    }

    return maxStreak;
}

int main()
{
    size_t arrayCount = 0;
    size_t arrayCapacity = 0;
    int *array = 0;

    for(;;)
    {
        if(arrayCount == arrayCapacity)
        {
            arrayCapacity += 20;
            array = realloc(array, sizeof(*array) * arrayCapacity);
        }

        printf("Introduza um número: ");
        scanf("%d", array + arrayCount++);
        if(array[arrayCount-1] < 0)
        {
            break;
        }
    }

    int searchFor;
    printf("Número a pesquisar: "); scanf("%d", &searchFor);
    int rep = contaRepeticao(array, arrayCount-1, searchFor);
    printf("Maior sequência de números %d tem tamanho %d\n", searchFor, rep);

    return 0;
}
