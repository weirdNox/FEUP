#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int fact(int n)
{
    if(n == 1)
    {
        return 1;
    }

    return n*fact(n-1);
}

double calculateNext(double x, int n)
{
    double result = pow(-1, n+1)*(pow(x, 2*n-1)/fact(2*n-1));
    return result;
}

int main()
{
    double x, error;
    scanf("%lf %lf", &x, &error);

    int n = 1;
    double result = x;
    for(;;)
    {
        double next = result+calculateNext(x, ++n);
        if(fabs(next-result) < error)
        {
            break;
        }
        result = next;
    }

    printf("%lf\n", result);

    return 0;
}
