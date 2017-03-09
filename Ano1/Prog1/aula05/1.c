#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randBetween(int min, int max)
{
    int range = max - min + 1;
    int binSize = RAND_MAX / range;
    int randNumber;
    do
    {
        randNumber = rand();
    } while(randNumber >= binSize*range);

    return randNumber / binSize + min;
}

int main()
{
    srand(time(0));

    int numberOfThrows;

    printf("Quantos lançamentos? ");
    scanf("%d", &numberOfThrows);

    int n = 0;
    for(int i = 0; i < numberOfThrows; ++i)
    {
        if(randBetween(1, 6) == 6)
        {
            ++n;
        }
    }

    printf("A face seis saiu %d vezes.\n", n);

    return 0;
}
