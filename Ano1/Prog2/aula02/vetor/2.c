#include "vetor.c"
#include <time.h>

void printVec(vetor *v)
{
    printf("[ ");
    int size = vetor_tamanho(v);
    for(int i = 0; i < size; ++i)
    {
        char *string = (char*)vetor_elemento(v, i);
        printf("%s", string);
        if(i < size-1)
        {
            printf(" | ");
        }
    }
    puts(" ]");
}

char *solicitarString()
{
    int capacity = 20;
    char *string = malloc(sizeof(*string)*capacity);
    int currentSize = 0;
    for(;;)
    {
        fgets(string+currentSize, capacity-currentSize, stdin);
        currentSize = strlen(string);
        if(string[currentSize-1] == '\n')
        {
            string[--currentSize] = 0;
            break;
        }
        capacity += 20;
        string = realloc(string, sizeof(*string)*capacity);
    }

    return string;
}

int main()
{
    srand(time(0));
    vetor *v = vetor_novo();
    for(int i = 0; i < 5; ++i)
    {
        char *string = solicitarString();
        vetor_insere(v, string, i);
        free(string);
    }
    printVec(v);

    char *string = solicitarString();
    int i = vetor_pesquisa(v, string);
    if(i != -1)
    {
        vetor_remove(v, i);
    }
    free(string);
    printVec(v);
    vetor_ordena(v);
    printVec(v);

    vetor *v1 = vetor_novo();
    for(int i = 0; i < 5; ++i)
    {
        char *string = solicitarString();
        vetor_insere(v1, string, i);
        free(string);
    }
    printVec(v1);

    vetor *v2 = vetor_concatena(v1, v);
    printVec(v2);

    vetor_inverte(v2);
    printVec(v2);

    vetor *baralhado = vetor_baralha(v2);
    printVec(baralhado);

    return 0;
}
