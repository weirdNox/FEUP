#include <stdio.h>

int multiplicacao(int primeiroNumero, int segundoNumero)
{
    if(segundoNumero == 1)
    {
        return primeiroNumero;
    }
    else if(segundoNumero == -1)
    {
        return -primeiroNumero;
    }
    else if(segundoNumero > 0)
    {
        return primeiroNumero + multiplicacao(primeiroNumero, segundoNumero-1);
    }
    else if(segundoNumero < 0)
    {
        return -primeiroNumero + multiplicacao(primeiroNumero, segundoNumero+1);
    }
    else
    {
        return 0;
    }
}

int main()
{
    int a, b;
    printf("Insira 2 números para serem multiplicados: ");
    scanf("%d %d", &a, &b);

    printf("Resultado: %d\n", multiplicacao(a, b));

    return 0;
}
