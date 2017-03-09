#include <stdio.h>

int main()
{
    int total = 0;
    int noFreq = 0;
    int approved = 0;

    float freq, mini;
    while(scanf("%f %f", &freq, &mini) != EOF)
    {
        ++total;
        if(freq < 40)
        {
            ++noFreq;
            continue;
        }

        float final = 0.4f*freq + 0.6f*mini;
        final /= 5.0f;

        if(final >= 9.5f)
        {
            ++approved;
        }
    }

    printf("Estudantes sem frequencia: %d\n", noFreq);
    printf("Aprovacoes: %.1f %%\n", approved/(float)total*100);

    return 0;
}
