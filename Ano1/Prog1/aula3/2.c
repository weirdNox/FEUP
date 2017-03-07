#include <stdio.h>

int main()
{
    int num;
    printf("Insira um número: ");
    scanf("%d", &num);

    if(num < -10 || (num >= 5 && num < 45) || (num > 120 && num <= 245))
    {
        puts("O número encontra-se nos intervalos.");
    }
    else
    {
        puts("O número não se encontra nos intervalos.");
    }

    return 0;
}
