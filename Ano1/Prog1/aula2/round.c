#include <stdio.h>

int main()
{
    float number;
    printf("Insira um numero: ");
    scanf("%f", &number);

    int rounded = (int)(number+0.5f);
    if(rounded % 2)
    {
        printf("%d %d", rounded-1, rounded+1);
    }
    else
    {
        printf("%d %d", rounded-2, rounded+2);
    }

    return 0;
}
