#include <stdio.h>

int main()
{
    float ideal, min, max;
    scanf("%f %f %f", &ideal, &min, &max);

    float read;
    int count = 0;
    float average = 0;
    int above = 0, below = 0;
    while(scanf("%f", &read) != EOF)
    {
        if(read < min)
        {
            ++below;
            continue;
        }
        if(read > max)
        {
            ++above;
            continue;
        }
        average += read;
        ++count;
    }

    average /= count;
    float deviation = (average-ideal)/ideal;
    printf("Volume medio (desvio): %.2f (desvio de %.2f%%)\n\
Garrafas eliminadas (volume por excesso): %d\n\
Garrafas eliminadas (volume por defeito): %d\n", average, deviation*100.0f, above, below);

    return 0;
}
