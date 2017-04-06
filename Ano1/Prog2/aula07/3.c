#include <stdio.h>
#include "avl.c"

#define arrayCount(arr) sizeof(arr)/sizeof(arr[0])

int main()
{
    FILE *ficheiro = fopen("cidades.txt", "r");
    if(!ficheiro)
    {
        fprintf(stderr, "Erro ao abrir ficheiro\n");
        return -1;
    }

    arvore_avl *paises = avl_nova();
    char linha[1<<13];
    while(fgets(linha, arrayCount(linha), ficheiro))
    {
        strtok(linha, ",");
        char *insere = strtok(0, "\r\n");

        avl_insere(paises, insere);
    }

    char *paisesAImprimir[] = {"Portugal", "Spain", "Russia"};
    for(int i = 0; i < arrayCount(paisesAImprimir); ++i)
    {
        no_avl *no = avl_pesquisa(paises, paisesAImprimir[i]);
        if(no)
        {
            printf("%s - %d\n", no->str, no->contagem);
        }
    }

    return 0;
}
