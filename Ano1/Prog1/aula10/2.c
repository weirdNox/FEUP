#include <stdio.h>
#include <string.h>

int capicua(char *str)
{
    char *head = str;
    char *tail = str + strlen(str) - 1;
    int isPalindrome = 1;
    while(head < tail)
    {
        if(*head != *tail)
        {
            isPalindrome = 0;
            break;
        }
        ++head;
        --tail;
    }

    return isPalindrome;
}

int main()
{
    for(;;)
    {
        char buffer[256] = {0};
        printf("Palavra? ");
        if(scanf("%255s", buffer) != 1)
        {
            break;
        }
        if(capicua(buffer))
        {
            printf("%s é capicua\n", buffer);
        }
        else
        {
            printf("%s não é capicua\n", buffer);
        }
    }

    return 0;
}
