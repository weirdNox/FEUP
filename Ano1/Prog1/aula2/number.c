#include <stdio.h>

int main()
{
    float number;
    printf("Insira um numero: ");
    scanf("%f", &number);

    printf("Numero com 3 casas decimais - %.3f\nParte inteira - %d\nParte decimal - %f\n",
           number, (int)number, number-(int)number);

    return 0;
}
