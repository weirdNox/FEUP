#include <stdio.h>

enum
{
    arrSize = 105,
};

int procuraTodos(int *v, int N, int x, int *posicoes, int *nPosicoes)
{
    for(int i = 0; i < N; ++i)
    {
        if(v[i] == x)
        {
            posicoes[(*nPosicoes)++] = i;
        }
    }

    return (*nPosicoes) != 0;
}

int main()
{
    int arr[arrSize] = {1, 2, 3, 1, 2, 1, 2, 1};

    int posSize = 0;
    int pos[200];

    if(procuraTodos(arr, arrSize, 2, pos, &posSize))
    {
        puts("Found at least one!");
        for(int i = 0; i < posSize; ++i)
        {
            printf("Position %d\n", pos[i]);
        }
    }
    else
    {
        puts("Didn't find anything! :(");
    }

    return 0;
}
