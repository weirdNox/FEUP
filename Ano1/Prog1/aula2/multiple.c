#include <stdio.h>

int main()
{
    int int1, int2;
    printf("Numero inteiro 1? ");
    scanf("%d", &int1);
    printf("Numero inteiro 2? ");
    scanf("%d", &int2);

    if(int1 % int2)
    {
        printf("%d nao e multiplo de %d\n", int1, int2);
    }
    else
    {
        printf("%d e multiplo de %d\n", int1, int2);
    }

    return 0;
}
