#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

int readPoly(int *polynomial)
{
    memset(polynomial, 0, POLY_ARRAY_SIZE*sizeof(polynomial[0]));
    int degree;
    do
    {
        printf("Qual é o maior grau? ");
        scanf("%d", &degree);
    } while(degree < 0 || degree > 10);

    for(int i = degree;
        i >= 0;
        --i)
    {
        if(i)
        {
            printf("Insira o coeficiente do grau %d: ", i);
        }
        else
        {
            printf("Insira o termo independente: ");
        }
        scanf("%d", polynomial+i);
    }

    return degree;
}

void writePoly(int *polynomial, int degree)
{
    printf("Polinómio: ");

    int prev = 0;
    for(int i = degree;
        i >= 0;
        --i)
    {
        if(polynomial[i])
        {
            int representation = polynomial[i];

            if(prev)
            {
                if(polynomial[i] > 0)
                {
                    printf(" + ");
                }
                else
                {
                    printf(" - ");
                }
                representation = abs(representation);
            }
            prev = 1;

            if(i)
            {
                printf("%dx^%d", representation, i);
            }
            else
            {
                printf("%d", representation);
            }
        }
    }
    if(!prev)
    {
        printf("0");
    }
    puts("");
}

void addPoly(int *p1, int *p2, int *pRes, int biggerDegree)
{
    memset(pRes, 0, POLY_ARRAY_SIZE*sizeof(pRes[0]));
    for(int i = biggerDegree;
        i >= 0;
        --i)
    {
        pRes[i] = p1[i] + p2[i];
    }
}

float calc(int *polynomial, int degree, float x)
{
    float sum = 0;
    for(int i = degree;
        i >= 0;
        --i)
    {
        float partialResult = polynomial[i];
        for(int j = 0; j < i; ++j)
        {
            partialResult *= x;
        }
        sum += partialResult;
    }
    return sum;
}
