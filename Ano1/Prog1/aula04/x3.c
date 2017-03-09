#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    int numberInside = 0;
    int totalPoints = 0;

    scanf("%d", &totalPoints);

    for(int i = 0; i < totalPoints; ++i)
    {
        double x = rand() / (double)RAND_MAX;
        double y = rand() / (double)RAND_MAX;

        if(x*x + y*y < 1.0)
        {
            ++numberInside;
        }
    }

    printf("Pi = %f\n", 4*(double)numberInside/(double)totalPoints);

    return 0;
}
