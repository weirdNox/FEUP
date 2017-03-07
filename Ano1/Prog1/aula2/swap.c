#include <stdio.h>

int main()
{
    int n1, n2;
    printf("Insira numero para variavel 1: ");
    scanf("%d", &n1);
    printf("Insira numero para variavel 2: ");
    scanf("%d", &n2);

    n1 ^= n2;
    n2 ^= n1;
    n1 ^= n2;

    printf("Valor da variavel 1 depois da troca: %d\nValor da variavel 2 depois da troca: %d\n",
           n1, n2);

    return 0;
}
