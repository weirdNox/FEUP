#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    int histogram[6] = {0};
    int numberOfExperiments = 30;

    for(int i = 0; i < numberOfExperiments; ++i)
    {
        ++histogram[rand()%6];
    }

    printf("Histograma de %d lançamentos\n", numberOfExperiments);
    for(int i = 0; i < 6; ++i)
    {
        printf("%d - ", i+1);
        while(histogram[i]--)
        {
            printf("*");
        }
        puts("");
    }

    return 0;
}
