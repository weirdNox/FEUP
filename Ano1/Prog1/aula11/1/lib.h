#if !defined(LIB_H)

enum
{
    POLY_ARRAY_SIZE = 11,
};

int readPoly(int *polynomial);
void writePoly(int *polynomial, int degree);
void addPoly(int *p1, int *p2, int *pRes, int biggerDegree);
float calc(int *polynomial, int degree, float x);

#define LIB_H
#endif
