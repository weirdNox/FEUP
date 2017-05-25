#include <stdio.h>
#include <limits.h>

unsigned int fib(unsigned int n)
{
    if(n == 0 || n == 1)
    {
        return n;
    }

    return fib(n-1) + fib(n-2);
}

unsigned int fib2_helper(unsigned int n, unsigned int *nchamadas)
{
    printf("fib(%d)", n);
    ++*nchamadas;
    if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }

    return fib2_helper(n-1, nchamadas) + fib2_helper(n-2, nchamadas);
}

unsigned int fib2(unsigned int n)
{
    unsigned int nchamadas = 0;
    int resultado = fib2_helper(n, &nchamadas);
    printf("\nfib() foi chamado %d vezes.\n", nchamadas);
    printf("O número fibonacci de ordem %d é %d.\n", n, resultado);
    return resultado;
}

#define FIB3_MAX 101
#define FIB3_NOT_DEFINED (unsigned int)-1
unsigned int fib3_helper(unsigned int n, unsigned int *nchamadas,
                         unsigned int resultados[])
{
    printf("fib(%d)", n);
    ++*nchamadas;
    if(resultados[n] != FIB3_NOT_DEFINED)
    {
        return resultados[n];
    }

    resultados[n] = (fib3_helper(n-1, nchamadas, resultados) +
                     fib3_helper(n-2, nchamadas, resultados));

    return resultados[n];
}

unsigned int fib3(unsigned int n)
{
    if(n >= FIB3_MAX)
    {
        return 0;
    }

    unsigned int resultados[FIB3_MAX];
    resultados[0] = 0;
    resultados[1] = 1;
    for(int i = 2; i < FIB3_MAX; ++i)
    {
        resultados[i] = FIB3_NOT_DEFINED;
    }

    unsigned int nchamadas = 0;
    int resultado = fib3_helper(n, &nchamadas, resultados);

    printf("\nfib() foi chamado %d vezes.\n", nchamadas);
    printf("O número fibonacci de ordem %d é %d.\n", n, resultado);

    return resultado;
}

int main()
{
    int n;
    printf("N? ");
    scanf("%d", &n);
    fib3(n);

    return 0;
}
