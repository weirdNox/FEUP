#include <stdio.h>

int main()
{
    int num;
    printf("Insira um número: ");
    scanf("%d", &num);

    if(num % 2)
    {
        printf("%d é ímpar", num);
    }
    else
    {
        printf("%d é par", num);
    }

    return 0;
}
