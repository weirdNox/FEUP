#include <stdio.h>

float f(float a, float x)
{
    return a*x*x;
}

int main()
{
    float a, begin, end, increment;
    printf("Qual o valor de a? ");
    scanf("%f", &a);

    printf("Qual o intervalo? ");
    scanf("%f %f", &begin, &end);

    printf("Qual o incremento? ");
    scanf("%f", &increment);

    for(float x = begin; x <= end; x += increment)
    {
        printf("f(%f) = %f\n", x, f(a, x));
    }

    return 0;
}
