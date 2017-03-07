#include <stdio.h>

float avg(float v[])
{
    float average = 0;
    for(int i = 0; i < 10; ++i)
    {
        average += v[i];
    }
    average /= 10.f;

    return average;
}

float max(float v[])
{
    float max = v[0];
    for(int i = 1; i < 10; ++i)
    {
        max = v[i] > max ? v[i] : max;
    }

    return max;
}

float min(float v[])
{
    float min = v[0];
    for(int i = 1; i < 10; ++i)
    {
        min = v[i] < min ? v[i] : min;
    }

    return min;
}

void imprimir_vetor(float v[], int n)
{
    printf("{");
    for(int i = 0; i < n; ++i)
    {
        printf("%f", v[i]);
        if(i < n-1)
        {
            printf(", ");
        }
    }
    puts("}");
}

int main()
{
    float v[10];
    for(int i = 0; i < 10; ++i)
    {
        scanf("%f", v+i);
    }

    printf("%f\n", avg(v));
    printf("%f\n", max(v));
    printf("%f\n", min(v));
    imprimir_vetor(v, 10);

    return 0;
}
