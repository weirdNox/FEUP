#include <stdio.h>

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

int main()
{
    char c;
    int shift;
    printf("Carater e shift: ");
    scanf("%c %d", &c, &shift);

    printf("%c\n", converte(c, shift));

    return 0;
}
