#include <stdio.h>

int main(int argc, char *argv[])
{
    float popA = 0, rateA, popB = 0, rateB;
    do
    {
        printf("Pais A (pop/taxa): ");
        scanf("%f %f", &popA, &rateA);
    } while(popA <= 0);
    do
    {
        printf("Pais B (pop/taxa): ");
        scanf("%f %f", &popB, &rateB);
    } while(popA <= popB);

    int years = 0;
    while(popB <= popA)
    {

        years += 1;
        popA *= (1.0 + rateA/100);
        popB *= (1.0 + rateB/100);
    }

    printf("Ultrapassará em %d anos.\n", years);

    return 0;
}
