#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    printf("Qual é a frase? ");

    char c;
    int count[5] = {0};
    while(scanf("%c", &c) == 1)
    {
        if(c == '\n')
        {
            break;
        }

        c = tolower(c);
        switch(c)
        {
            case 'a':
            {
                ++count[0];
            } break;

            case 'e':
            {
                ++count[1];
            } break;

            case 'i':
            {
                ++count[2];
            } break;

            case 'o':
            {
                ++count[3];
            } break;

            case 'u':
            {
                ++count[4];
            } break;
        }
    }

    printf("A: %d\nE: %d\nI: %d\nO: %d\nU: %d\n", count[0], count[1], count[2], count[3], count[4]);

    return 0;
}
