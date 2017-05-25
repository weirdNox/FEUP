#include <stdio.h>

unsigned int pascal(unsigned int l, unsigned int c)
{
    if(c > l)
    {
        return 0;
    }
    if(!c)
    {
        return 1;
    }

    return pascal(l-1, c-1) + pascal(l-1, c);
}

unsigned int printTriangle()
{
    unsigned int results[33*32];
    for(int l = 0; l < 32; ++l)
    {
        for(int c = 0; c < l+2; ++c)
        {
            if(c > l)
            {
                results[32*l + c] = 0;
                continue;
            }
            else if(c == 0)
            {
                results[32*l + c] = 1;
            }
            else
            {
                results[32*l + c] = results[32*(l-1) + c-1] + results[32*(l-1) + c];
            }
            printf("%-9u ", results[32*l+c]);
        }
        puts("");
    }
    return 0;
}

int main()
{
    unsigned int l, c;
    printf("Linha? ");
    scanf("%d", &l);
    printf("Coluna? ");
    scanf("%d", &c);
    printf("O elemento do triângulo de Pascal em (%d, %d) é %d\n", l, c,
           pascal(l, c));

    printTriangle();

    return 0;
}
