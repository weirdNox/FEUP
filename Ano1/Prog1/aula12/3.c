#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readString()
{
    char *result = 0;
    int size = 0;

    int c;
    while(c = getchar(), c != '\n' && c != EOF)
    {
        result = realloc(result, sizeof(*result)*(size+2));
        result[size++] = c;
    }

    if(result)
    {
        result[size] = 0;
    }

    return result;
}

int main()
{
    char **stringList = 0;
    int stringListSize = 0;
    for(;;)
    {
        char *newString;
        if(newString = readString(), !newString)
        {
            break;
        }

        stringList = realloc(stringList, sizeof(*stringList)*(stringListSize+1));
        stringList[stringListSize++] = newString;
    }

    for(int i = 1; i < stringListSize; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(strcmp(stringList[j], stringList[i]) == 0)
            {
                free(stringList[j]);
                stringList[j] = stringList[--stringListSize];
            }
        }
    }

    stringList = realloc(stringList, stringListSize);
    puts("Depois de eliminar:");
    for(int i = 0; i < stringListSize; ++i)
    {
        printf("%s\n", stringList[i]);
    }

    return 0;
}
