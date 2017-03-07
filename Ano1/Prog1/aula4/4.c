#include <stdio.h>

int main()
{
    int num;
    printf("Insira o número para fatorizar: ");
    scanf("%d", &num);

    for(int i = 2; i <= num;)
    {
        if(num % i == 0)
        {
            printf("%d ", i);
            num /= i;
            if(num == 1)
            {
                break;
            }
        }
        else
        {
            ++i;
        }
    }
    puts("");

    return 0;
}
