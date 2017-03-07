#include <stdio.h>
#include <stdint.h>

int main()
{
    int type;
    printf("Pretende usar numero maximo de valores(1) ou valor maximo(2)? ");
    scanf("%d", &type);

    uint64_t until;
    if(type == 1)
    {
        printf("Introduza um numero de valores da sequência: ");
        scanf("%lu", &until);
    }
    else
    {
        printf("Introduza o valor máximo: ");
        scanf("%lu", &until);
    }

    uint64_t first, second;
    for(int iterationNumber = 0;
        (type == 1 && iterationNumber < until) || type != 1;
        ++iterationNumber)
    {
        if(iterationNumber == 0)
        {
            second = 0;
        }
        else if(iterationNumber == 1)
        {
            first = 0;
            second = 1;
        }
        else
        {
            uint64_t temp = first;
            first = second;
            second += temp;
        }

        if(type != 1 && second > until)
        {
            break;
        }

        if(iterationNumber)
        {
            printf(", ");
        }
        printf("%lu", second);
    }
    puts(".");

    return 0;
}
