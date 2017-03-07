#include <stdio.h>
#include <ctype.h>
#include <string.h>

enum
{
    SIZE = 1<<10,
};

char converte(char c, int shift)
{
    char offset = c - 'a';
    offset += shift;
    if(offset < 0)
    {
        offset += 26;
    }
    else if(offset >= 26)
    {
        offset -= 26;
    }
    return offset + 'a';
}

void desloca(char *texto, char *cifra, int shift)
{
    int length = strlen(texto)-1;
    for(int i = 0; i < length; ++i)
    {
        if(isalpha(texto[i]))
        {
            cifra[i] = converte(texto[i], shift);
        }
        else
        {
            cifra[i] = texto[i];
        }
    }
    cifra[length] = '\0';
}

int main()
{
    char buffer[SIZE], output[SIZE];
    fgets(buffer, SIZE, stdin);
    int shift;
    scanf("%d", &shift);

    desloca(buffer, output, shift);

    printf("%s\n", output);

    return 0;
}
