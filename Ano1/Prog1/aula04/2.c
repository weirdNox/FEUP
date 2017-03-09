#include <stdio.h>
#include <float.h>

int main()
{
    float num;
    printf("Insira uma lista de números (para indicar o fim, basta C-D)\n");
    float min = FLT_MAX;
    float max = -FLT_MAX;
    float average = 0;
    int numberOfReads = 0;
    while(scanf("%f", &num) == 1)
    {
        if(num < min)
        {
            min = num;
        }

        if(num > max)
        {
            max = num;
        }

        average = average*numberOfReads + num;
        average /= ++numberOfReads;
    }

    printf("A média é %f, o máximo é %f e o mínimo é %f.\n", average, max, min);

    return 0;
}
