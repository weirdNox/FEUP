#include <stdio.h>
#include <time.h>

#include "vetor.c"
#include "lista.c"

#define arrayCount(a) (sizeof(a) / sizeof(*a))

void printList(lista *l, FILE *stream)
{
    int num = lista_tamanho(l);
    for(int i = 0; i < num; ++i)
    {
        fprintf(stream, "Pos %d -> %s\n", i, lista_elemento(l, i)->str);
    }
}

int main()
{
    clock_t start, end;

    FILE *file = fopen("nomes.txt", "r");
    if(!file)
    {
        fprintf(stderr, "Erro a abrir ficheiro\n");
        return 1;
    }
    char buffer[1<<10];

    // NOTE(nox): Teste listas!
    start = clock();

    vetor *v = vetor_novo();
    while(fgets(buffer, arrayCount(buffer), file))
    {
        buffer[strlen(buffer)-1] = 0;
        vetor_insere(v, buffer, 0);
    }

    int size = vetor_tamanho(v);
    for(int i = 0; i < 10000; ++i)
    {
        const char *text = vetor_elemento(v, rand() % size);
        if(text) // NOTE(nox): Para o compilador não reclamar com variável não usada...
        {
        }
    }
    for(int i = 0; i < size; ++i)
    {
        vetor_remove(v, 0);
    }
    rewind(file);
    while(fgets(buffer, arrayCount(buffer), file))
    {
        buffer[strlen(buffer)-1] = 0;
        vetor_insere(v, buffer, -1);
    }

    end = clock();
    printf("Tempo com vetores: %.3fs\n", (double)(end-start)/CLOCKS_PER_SEC);
    vetor_apaga(v);

    rewind(file);

    // NOTE(nox): Teste listas!
    start = clock();

    lista *l = lista_nova();
    while(fgets(buffer, arrayCount(buffer), file))
    {
        buffer[strlen(buffer)-1] = 0;
        lista_insere(l, buffer, lista_elemento(l, 0));
    }

    size = lista_tamanho(l);
    for(int i = 0; i < 10000; ++i)
    {
        l_elemento *el = lista_elemento(l, rand() % size);
        if(el->str) // NOTE(nox): Para o compilador não reclamar com variável não usada...
        {
        }
    }
    for(int i = 0; i < size; ++i)
    {
        lista_remove(l, lista_elemento(l, 0));
    }
    rewind(file);
    while(fgets(buffer, arrayCount(buffer), file))
    {
        buffer[strlen(buffer)-1] = 0;
        lista_insere(l, buffer, 0);
    }

    end = clock();
    printf("Tempo com listas: %.3fs\n", (double)(end-start)/CLOCKS_PER_SEC);
    lista_apaga(l);

    return 0;
}
