#include <stdio.h>

int main()
{
    long long num;
    printf("Insira um número: ");
    scanf("%lld", &num);

    int sum = 0;
    while(num)
    {
        int digit = num % 10;
        num /= 10;
        sum += digit;
    }

    printf("A soma dos dígitos é %d\n", sum);

    return 0;
}
