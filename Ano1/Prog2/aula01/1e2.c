#include <stdio.h>

int main()
{
    FILE *file = fopen("lusiadas-utf8.txt", "r");
    if(!file)
    {
        fprintf(stderr, "Erro a abrir ficheiro\n");
        return -1;
    }

    int count[3] = {0};

    for(;;)
    {
        int byte1 = getc(file);
        if(byte1 == EOF)
        {
            break;
        }

        if((byte1 & 0x80) == 0)
        {
            continue;
        }
        else if((byte1 & 0xe0) == 0xc0)
        {
            int byte2 = getc(file);
            if(byte1 == 0xC3 && (byte2 == 0x83 || byte2 == 0xa3))
            {
                ++count[0];
            }
            else if(byte1 == 0xC3 && (byte2 == 0x95 || byte2 == 0xb5))
            {
                ++count[1];
            }
            else if(byte1 == 0xC3 && (byte2 == 0x87 || byte2 == 0xa7))
            {
                ++count[2];
            }
        }
        else if((byte1 & 0xf0) == 0xe0)
        {
            getc(file); getc(file);
        }
        else if((byte1 & 0xf8) == 0xf0)
        {
            getc(file); getc(file); getc(file);
        }
    }

    printf("ã: %d\n", count[0]);
    printf("õ: %d\n", count[1]);
    printf("ç: %d\n", count[2]);

    return 0;
}
