#include <stdio.h>
#include <stdint.h>

void nextFibonacciUntil_(uint64_t n1, uint64_t n2, int times, int until, int type)
{
    if(type == 1 && times >= until)
    {
        puts(".");
        return;
    }

    if(times == 0)
    {
        n1 = -1;
        n2 = 0;
    }
    else if(times == 1)
    {
        n1 = 0;
        n2 = 1;
    }
    else
    {
        uint64_t temp = n1;
        n1 = n2;
        n2 += temp;
    }

    if(type != 1 && n2 > until)
    {
        puts(".");
        return;
    }

    if(times)
    {
        printf(", ");
    }
    printf("%lu", n2);
    nextFibonacciUntil_(n1, n2, times+1, until, type);
}

void startFibonacci(int type, uint64_t until)
{
    nextFibonacciUntil_(0, 0, 0, until, type);
}

int main()
{
    int type;
    printf("Pretende usar numero maximo de valores(1) ou valor maximo(2)? ");
    scanf("%d", &type);

    uint64_t until;
    if(type == 1)
    {
        printf("Introduza um numero de valores da sequência: ");
        scanf("%lu", &until);
    }
    else
    {
        printf("Introduza o valor máximo: ");
        scanf("%lu", &until);
    }
    startFibonacci(type, until);

    return 0;
}
