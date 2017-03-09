#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int countDigit(uint64_t number, int wantedDigit)
{
    int count = 0;
    while(number)
    {
        int digit = number % 10;
        number /= 10;
        if(digit == wantedDigit)
        {
            ++count;
        }
    }

    return count;
}

int main()
{
    uint64_t number;
    uint32_t wantedDigit;
    scanf("%lu %d", &number, &wantedDigit);

    printf("o digito %d aparece %d vezes no numero %lu\n", wantedDigit, countDigit(number, wantedDigit),
                                                                                   number);

    return 0;
}
