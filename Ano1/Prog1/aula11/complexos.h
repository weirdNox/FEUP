#if !defined(COMPLEXOS_H)
#include <math.h>

typedef struct
{
    double realPart;
    double imaginaryPart;
} Complex;

Complex readComplex()
{
    Complex complex;
    printf("Qual é a parte real do número? ");
    scanf("%lf", &complex.realPart);
    printf("Qual é a parte imaginária do número? ");
    scanf("%lf", &complex.imaginaryPart);
    return complex;
}

void writeComplex(Complex complex)
{
    if(complex.imaginaryPart > 0)
    {
        printf("%.2lf + %.2lfi\n", complex.realPart, complex.imaginaryPart);
    }
    else
    {
        printf("%.2lf - %.2lfi\n", complex.realPart, -complex.imaginaryPart);
    }
}

Complex sumComplexNums(Complex c1, Complex c2)
{
    Complex result;
    result.realPart = c1.realPart + c2.realPart;
    result.imaginaryPart = c1.imaginaryPart + c2.imaginaryPart;
    return result;
}

double modComplex(Complex c)
{
    return sqrt(c.realPart*c.realPart + c.imaginaryPart*c.imaginaryPart);
}

double argComplex(Complex c)
{
    return atan2(c.imaginaryPart, c.realPart);
}

#define COMPLEXOS_H
#endif
