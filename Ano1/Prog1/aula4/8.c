#include <stdio.h>

int main()
{
    int number;
    printf("Insira o número: ");
    scanf("%d", &number);

    int temp = number;
    int inverseNumber = 0;
    for(;temp;)
    {
        inverseNumber *= 10;
        inverseNumber += temp % 10;
        temp /= 10;
    }

    printf("O inverso de %d é %d.\n", number, inverseNumber);

    return 0;
}
