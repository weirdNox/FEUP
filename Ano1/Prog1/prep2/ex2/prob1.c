#include <stdio.h>

int ler_volumes(float *volumes)
{
    int num;
    scanf("%d", &num);

    for(int i = 0; i < num; ++i)
    {
        if(scanf("%f", volumes+i) < 1)
        {
            num = i;
            break;
        }
    }

    return num;
}

float volume_medio(float *volumes, int nvolumes, float max, float min)
{
    int n = 0;
    float avg = 0;
    for(int i = 0; i < nvolumes; ++i)
    {
        if(volumes[i] > min && volumes[i] < max)
        {
            ++n;
            avg += volumes[i];
        }
    }
    avg /= (float)n;
    return avg;
}

int main()
{
    float volumes[1000];
    int num = ler_volumes(volumes);
    printf("Foram lidos %d valores.\n", num);

    float min, max;
    printf("Indique o valor mínimo: ");
    scanf(" %f", &min);
    printf("%.1f\n", min);
    printf("Indique o valor máximo: ");
    scanf(" %f", &max);
    printf("%.1f\n", max);

    printf("O volume medio de enchimento foi de %.3f litros.\n", volume_medio(volumes, num, max, min));

    return 0;
}
