#include <stdio.h>

void converteBinário(int num)
{
    printf("%d\t", num);

    for(int i = 8; i >= 0; --i)
    {
        if(num & (1<<i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    puts("");
}

int main()
{
    int number;
    char conversion;
    while(scanf("%d %c", &number, &conversion) != EOF)
    {
        switch(conversion)
        {
            case 'b':
            {
                converteBinário(number);
            } break;

            case 'o':
            {
                printf("%d\t%o\n", number, number);
            } break;

            case 'h':
            {
                printf("%d\t%X\n", number, number);
            } break;

            default:
            {
            } break;
        }
    }

    return 0;
}
/*  */
