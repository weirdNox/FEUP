#include <stdio.h>

void quociresto(int dividendo, int divisor, int *quociente, int *resto)
{
    *quociente = 0;
    *resto = dividendo;
    while(*resto >= divisor)
    {
        *resto -= divisor;
        ++(*quociente);
    }
}

int soma(int n)
{
    int sum = 0;
    while(n)
    {
        int resto;
        quociresto(n, 10, &n, &resto);
        sum += resto;
    }

    return sum;
}

int par(int n)
{
    int quociente, resto;
    quociresto(n, 2, &quociente, &resto);

    return (resto == 0);
}

int main()
{
    int parTest = 76;
    int paraSomar = 12345678;

    if(par(parTest))
    {
        puts("É PAR!");
    }

    int sum = soma(paraSomar);
    printf("Soma: %d\n", sum);

    return 0;
}
