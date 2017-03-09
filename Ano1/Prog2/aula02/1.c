#include <stdio.h>
#include <stdlib.h>

void printVector(char *name, int *v, int n)
{
    printf("%s: [ ", name);
    for(int i = 0; i < n; ++i)
    {
        printf("%d ", v[i]);
    }
    puts("]");
}

int main()
{
    int vCount = 0;
    int *v = 0;
    printf("Número de elementos? ");
    scanf("%d", &vCount);
    v = malloc(sizeof(*v)*vCount);
    for(int i = 0; i < vCount; ++i)
    {
        printf("Introduza o %dº elemento: ", i+1);
        scanf("%d", v+i);
    }

    int evenCount = 0, oddCount = 0;
    int *even = malloc(sizeof(*even)*vCount);
    int *odd = malloc(sizeof(*odd)*vCount);
    for(int i = 0; i < vCount; ++i)
    {
        if(v[i] % 2)
        {
            odd[oddCount++] = v[i];
        }
        else
        {
            even[evenCount++] = v[i];
        }
    }
    even = realloc(even, sizeof(*even)*evenCount);
    odd = realloc(odd, sizeof(*odd)*oddCount);

    printVector("Vetor original", v, vCount);
    printVector("Números pares", even, evenCount);
    printVector("Números ímpares", odd, oddCount);

    return 0;
}
