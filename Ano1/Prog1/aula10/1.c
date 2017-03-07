#include <stdio.h>
#include <string.h>

enum
{
    SIZE = 1<<10,
};

void inverte(char *strOriginal, char *strInvertida)
{
    int length = strlen(strOriginal) - 1; // NOTE(nox): Not counting newline
    for(int index = 0;
        index < length;
        ++index)
    {
        strInvertida[length-1-index] = strOriginal[index];
    }
}

int main()
{
    char buffer1[SIZE];
    char buffer2[SIZE];

    printf("Escreva uma frase: ");
    fgets(buffer1, SIZE, stdin);
    inverte(buffer1, buffer2);

    printf("A frase invertida é %s\n", buffer2);

    return 0;
}
