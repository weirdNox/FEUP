#include <stdio.h>
#include <math.h>

void solve(float a, float b, float c)
{
    float discriminant = b*b - 4*a*c;
    if(discriminant > 0)
    {
        float discSqrt = sqrt(discriminant);
        printf("As raizes são: %f %f\n", (-b + discSqrt)/(2*a), (-b - discSqrt)/(2*a));
    }
    else if(discriminant == 0)
    {
        printf("Tem raiz dupla: %f\n", (-b)/(2*a));
    }
    else
    {
        float realPart = -b/(2*a);
        float complexPart = sqrt(-discriminant)/(2*a);
        printf("Tem raizes complexas: %f+%fi %f-%fi\n", realPart, complexPart, realPart, complexPart);
    }
}

int main()
{
    float a, b, c;
    printf("Introduza o valor de a: ");
    scanf("%f", &a);

    printf("Introduza o valor de b: ");
    scanf("%f", &b);

    printf("Introduza o valor de c: ");
    scanf("%f", &c);

    solve(a, b, c);

    return 0;
}
