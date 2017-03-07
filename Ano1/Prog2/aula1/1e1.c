#include <stdio.h>
#include <ctype.h>

int main()
{
    FILE *file = fopen("lusiadas.txt", "r");
    if(!file)
    {
        fprintf(stderr, "Erro a abrir ficheiro!\n");
        return 0;
    }

    int total = 0;
    int count['z' - 'a' + 1] = {0};

    for(;;)
    {
        int c = getc(file);
        if(c == EOF)
        {
            break;
        }

        char *converter = "aaaa---c-ee--i-----ooo----u-----aaaa---c-ee--i-----ooo----u-----";
        if(c >= 0xC0)
        {
            c = converter[c - 0xC0];
        }
        c |= 0x20;

        if(c >= 'a' && c <= 'z')
        {
            ++count[c - 'a'];
            ++total;
        }
    }

    printf("Número de letras no ficheiro: %d\n", total);
    for(int i = 0; i < ('z' - 'a' + 1); ++i)
    {
        float fraction = (float) (count[i] * 100.0f) / total;
        printf("Letra %c: %.2f%%\n", 'a'+i, fraction);
    }

    fclose(file);

    return 0;
}
