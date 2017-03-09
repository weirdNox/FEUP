#include <stdio.h>

int main()
{
    int n, ci, j;
    printf("Qual o capital inicial? ");
    scanf("%d", &ci);
    printf("Qual a taxa de juro dada pelo banco? ");
    scanf("%d", &j);
    printf("Durante quantos anos? ");
    scanf("%d", &n);

    float inside = 1 + (float)j/100.0f;
    float ca = ci;
    for(int i = 0; i < n; ++i)
    {
        ca *= inside;
    }

    printf("O capital acumulado ao fim de %d anos é de %.3f euros.\n", n, ca);

    return 0;
}
