#include <stdio.h>
#include <math.h>

int main()
{
    int numberOfPrimes;
    printf("Quantos números primos quer? ");
    scanf("%d", &numberOfPrimes);

    int lastPrime = 1;
    for(int i = 0; i < numberOfPrimes; ++i)
    {
        for(;;)
        {
            char found = 1;
            ++lastPrime;
            for(int i = 2; i <= sqrt(lastPrime); ++i)
            {
                if(lastPrime % i == 0)
                {
                    found = 0;
                    break;
                }
            }

            if(found)
            {
                break;
            }
        }

        printf("%d ", lastPrime);
    }
    puts("");


    return 0;
}
