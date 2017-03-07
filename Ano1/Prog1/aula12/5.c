#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct
{
    int pos;
    int ant;
    int sem;
    int gal;
    char *titulo;
    char *artista;
    char *etiqueta;
    char *editora;
} Disco;

char *readLine(FILE *file)
{
    char *result = 0;
    int size = 0;
    int capacity = 0;

    int c;
    while(c = fgetc(file), c != '\n' && c != EOF)
    {
        if(size >= capacity-1)
        {
            capacity += 10;
            result = realloc(result, sizeof(*result)*capacity);
        }
        result[size++] = c;
    }

    if(result)
    {
        result[size] = 0;
    }

    return result;
}

void eatWhitespace(char **iterator)
{
    while(**iterator && isspace(**iterator))
    {
        ++*iterator;
    }
}

char *readToken(char **iterator)
{
    eatWhitespace(iterator);

    char *first = *iterator;
    while(**iterator && **iterator != '|' && **iterator != '\n')
    {
        ++*iterator;
    }
    char *last = *iterator - 1;

    if(**iterator)
    {
        ++*iterator;
    }

    while(last > first && isspace(*last))
    {
        --last;
    }
    last += 1;

    char *result = malloc(sizeof(*result)*(last-first+1));
    for(char *it = first; it < last; ++it)
    {
        result[it-first] = *it;
    }
    result[last-first] = 0;

    return result;
}

int main()
{
    FILE *file = fopen("discos.txt", "r");
    Disco *discos = 0;
    int numDiscos = 0;

    char *line;
    while(line = readLine(file), line)
    {
        discos = realloc(discos, sizeof(*discos)*++numDiscos);
        Disco *disco = discos + numDiscos-1;
        char *iterator = line;
        char *token = readToken(&iterator);
        sscanf(token, "%d", &disco->pos);
        free(token);
        token = readToken(&iterator);
        sscanf(token, "%d", &disco->ant);
        free(token);
        token = readToken(&iterator);
        sscanf(token, "%d", &disco->sem);
        free(token);
        token = readToken(&iterator);
        sscanf(token, "%d", &disco->gal);
        free(token);
        disco->titulo = readToken(&iterator);
        disco->artista = readToken(&iterator);
        disco->etiqueta = readToken(&iterator);
        disco->editora = readToken(&iterator);
    }

    for(int i = 0; i < numDiscos; ++i)
    {
        Disco *disco = discos+i;
        if(disco->sem > 4)
        {
            printf("%s, %s, %s, %s\n", disco->titulo,
                   disco->artista, disco->etiqueta, disco->editora);
        }
    }

    return 0;
}
