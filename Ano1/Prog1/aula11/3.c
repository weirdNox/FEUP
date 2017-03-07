#include <stdio.h>
#include "complexos.h"

int main(int argc, char *argv[])
{
    Complex c1 = readComplex();
    writeComplex(c1);

    Complex c2 = readComplex();
    writeComplex(c2);

    Complex c3 = sumComplexNums(c1, c2);
    writeComplex(c3);

    printf("Módulo do primeiro: %lf\n", modComplex(c1));
    printf("Argumento do primeiro: %lf\n", argComplex(c1));

    return 0;
}
