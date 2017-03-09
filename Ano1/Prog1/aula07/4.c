#include <stdio.h>
#include <math.h>

void cartesianas_polares(float x, float y, float *r, float *theta)
{
    *r = sqrtf(x*x+y*y);
    *theta = atan2(y, x);
}

void polares_cartesianas(float r, float theta, float *x, float *y)
{
    *x = r*cos(theta);
    *y = r*sin(theta);
}

int main()
{
    float x, y, r, theta;

    x = 60;
    y = 20;
    cartesianas_polares(x, y, &r, &theta);
    printf("(%f, %f): %f e %frad\n", x, y, r, theta);
    polares_cartesianas(r, theta, &x, &y);
    printf("%f e %frad: (%f, %f)\n", r, theta, x, y);

    return 0;
}
