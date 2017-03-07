#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1<<6
int main()
{
    char buffer[MAX_BUFFER_SIZE] = {};
    printf("Insira um número: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    int isPalindrome = 1;
    for(int i = 0, j = strlen(buffer)-2; i < j; ++i, --j)
    {
        if(buffer[i] != buffer[j])
        {
            isPalindrome = 0;
            break;
        }
    }

    if(isPalindrome)
    {
        puts("O número é capicua.");
    }
    else
    {
        puts("O número não é capicua.");
    }

    return 0;
}
