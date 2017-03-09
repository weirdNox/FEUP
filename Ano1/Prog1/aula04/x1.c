#include <stdio.h>

int main()
{
    long number;
    scanf("%ld", &number);

    int sum = 0;
    int next = 3;
    while(number)
    {
        int digit = number % 10;
        number /= 10;
        sum += digit*next;
        next = next == 3 ? 1 : 3;
    }

    int checksumDigit = (sum/10+1)*10 - sum;

    printf("%d\n", checksumDigit);

    return 0;
}
