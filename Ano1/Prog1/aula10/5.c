#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum
{
    SIZE = 1<<10,
};

void eatWhitespace(char **at)
{
    while(**at && isspace(**at))
    {
        ++(*at);
    }
}

int wordToBuffer(char **at, char output[])
{
    char *start = *at;
    while(**at && !isspace(**at))
    {
        ++(*at);
    }
    char *end = *at;
    int size = end-start;
    strncpy(output, start, size);
    output[size] = '\0';
    return size;
}

int main()
{
    char buffer[SIZE];
    fgets(buffer, SIZE, stdin);

    int count = 0;
    int maxSize = 0;
    char maxWord[SIZE] = {0};
    double average = 0;
    char *parser = buffer;
    for(;;)
    {
        eatWhitespace(&parser);
        if(!*parser)
        {
            break;
        }
        char word[SIZE];
        int size = wordToBuffer(&parser, word);
        if(size > maxSize)
        {
            strncpy(maxWord, word, size);
            maxSize = size;
        }
        average = (average*count + size) / (count+1);
        ++count;
    }

    printf("Número de palavras: %d\n", count);
    printf("Palavra maior: %s\n", maxWord);
    printf("Comprimento médio: %.2lf\n", average);

    return 0;
}
