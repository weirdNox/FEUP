#include <stdio.h>

int main()
{
    float temp;
    printf("Qual a temperatura? ");
    scanf("%f", &temp);

    printf("\n%.3f C - %.3f K\n", temp, temp+273.15f);
    printf("%.3f C - %.3f F\n", temp, temp*9.0f/5.0f+32.0f);

    return 0;
}
