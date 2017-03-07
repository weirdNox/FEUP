#include <stdio.h>

enum
{
    arraySize = 128,
};

int compacta(char *orig, int N, char *dst)
{
    int size = 0;
    dst[size++] = *orig;
    for(int i = 1; i < N; ++i)
    {
        if(dst[size-1] != orig[i])
        {
            dst[size++] = orig[i];
        }

        if(orig[i] == '.')
        {
            break;
        }
    }

    return size;
}

int main()
{
    char string[arraySize] = "Hello worldd.";
    char dest[arraySize] = {0};

    int size = compacta(string, arraySize, dest);
    printf("%d\n", size);
    for(int i = 0; i < size; ++i)
    {
        printf("%c\n", dest[i]);
    }

    return 0;
}
