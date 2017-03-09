#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ordena(int *valorA, int *valorB, int *valorC)
{
    if(*valorA <= *valorB && *valorA <= *valorC)
    {
        if(*valorB > *valorC)
        {
            swap(valorB, valorC);
        }
    }
    else if(*valorB <= *valorA && *valorB <= *valorC)
    {
        swap(valorA, valorB);
        if(*valorB > *valorC)
        {
            swap(valorB, valorC);
        }
    }
    else
    {
        swap(valorA, valorC);
        if(*valorB > *valorC)
        {
            swap(valorB, valorC);
        }
    }
}

int main()
{
    int num1, num2, num3;
    scanf("%d %d %d", &num1, &num2, &num3);

    ordena(&num1, &num2, &num3);

    printf("%d %d %d", num1, num2, num3);

    return 0;
}
