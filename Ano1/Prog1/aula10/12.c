#include <stdio.h>
#include <stdint.h>

int proximoFib()
{
    static uint64_t first, second, iterationNumber = 0;

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

    ++iterationNumber;

    return second;
}

int main()
{
    for(int i = 0; i < 13; ++i)
    {
        printf("%d\n", proximoFib());
    }
    return 0;
}
