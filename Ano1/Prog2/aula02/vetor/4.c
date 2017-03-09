#include "vetor.c"

#define NSTRINGS 3

char *solicitarString()
{
    int c;
    while(c = getchar(), c != '\n' && c != EOF){}
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
    vetor *vec = vetor_novo();

    for(;;)
    {
        int size = vetor_tamanho(vec);
        for(int i = 0; i < size; ++i)
        {
            printf("[%d] %s\n", i+1, vetor_elemento(vec, i));
        }
        if(!size)
        {
            printf("(vazio)\n");
        }

        int index;
        do
        {
            printf("Posição para a nova string (1 a %d): ", size+1);
            scanf("%d", &index);
        } while(index < 0 || index > size+1);

        if(index == 0)
        {
            break;
        }

        printf("Nova string: ");
        char *string = solicitarString();
        if(index < size+1)
        {
            vetor_atribui(vec, index-1, string);
        }
        else
        {
            vetor_insere(vec, string, index-1);
        }
        free(string);
    }
    vetor_apaga(vec);

    return 0;
}
