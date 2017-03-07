#include <stdio.h>
#include <string.h>

enum
{
    SIZE = 1<<10,
};

int conta(char *frase, char *palavra)
{
    int count = 0;
    for(;;)
    {
        char *ptr = strstr(frase, palavra);
        if(!ptr)
        {
            break;
        }
        ++count;
        frase = ptr+1;
    }

    return count;
}

int main()
{
    char buffer[SIZE], word[SIZE];
    printf("Frase? ");
    fgets(buffer, SIZE, stdin);
    printf("Palavra? ");
    fgets(word, SIZE, stdin);
    word[strlen(word)-1] = '\0';

    printf("%d\n", conta(buffer, word));

    return 0;
}
