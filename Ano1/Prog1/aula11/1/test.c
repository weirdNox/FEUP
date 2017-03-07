#include <stdio.h>
#include "lib.h"

int main(int argc, char *argv[])
{
    int p1[POLY_ARRAY_SIZE];
    int d1 = readPoly(p1);
    writePoly(p1, d1);

    int p2[POLY_ARRAY_SIZE];
    int d2 = readPoly(p2);
    writePoly(p2, d2);

    int p3[POLY_ARRAY_SIZE] = {0};
    addPoly(p1, p2, p3, d1 > d2 ? d1 : d2);
    writePoly(p3, 10);

    printf("Resultado do polinómio 2 com x=2.5: %f\n", calc(p2, d2, 2.5));

    return 0;
}
