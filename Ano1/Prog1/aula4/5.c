#include <stdio.h>

int main()
{
    int height = 0;
    do
    {
        printf("Altura: ");
        scanf("%d", &height);
    } while(height < 4);

    int leftSize = height - 2;
    // NOTE(nox): Top
    for(int i = 0; i < height-1; ++i)
    {
        for(int j = 0; j < leftSize - i; ++j)
        {
            printf(" ");
        }

        for(int j = 0; j < 1 + 2*i; ++j)
        {
            printf("*");
        }

        puts("");
    }

    // NOTE(nox): Base
    for(int i = 0; i < leftSize; ++i)
    {
        printf(" ");
    }

    puts("*");

    return 0;
}
