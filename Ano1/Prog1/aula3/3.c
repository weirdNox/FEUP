#include <stdio.h>

int main()
{
    float height;
    printf("Qual a altura da pessoa? ");
    scanf("%f", &height);

    if(height < 1.3f)
    {
        puts("Essa pessoa é baixíssima.");
    }
    else if(height < 1.6f)
    {
        puts("Essa pessoa é baixa.");
    }
    else if(height < 1.75f)
    {
        puts("Essa pessoa é mediana.");
    }
    else if(height < 1.9f)
    {
        puts("Essa pessoa é alta.");
    }
    else
    {
        puts("Essa pessoa é altíssima.");
    }

    return 0;
}
