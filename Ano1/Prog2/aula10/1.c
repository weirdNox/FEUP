#include <stdio.h>
#include <time.h>
#include "tabdispersao.c"
#include "lista.c"

#define NUMERO_LEITURAS 1000

int main()
{
    srand(time(0));
    FILE *f = fopen("englishwords.txt", "r");
    if(!f)
    {
        return -1;
    }
    clock_t tempoInicio;

    // {
    lista *l = lista_nova();
    tempoInicio = clock();

    for(;;)
    {
        char palavra[1<<10], tipo[1<<10];
        if(fscanf(f, "%*s %s %s %*s ", palavra, tipo) < 2)
        {
            break;
        }
        lista_insere(l, palavra, 0);
    }

    printf("Inserção lista - %lfs\n", (double)(clock()-tempoInicio)/CLOCKS_PER_SEC);
    // }

    rewind(f);

    // {
    tabela_dispersao *h = tabela_nova(1e6, hash_djbm);
    tempoInicio = clock();

    for(;;)
    {
        char palavra[1<<10], tipo[1<<10];
        if(fscanf(f, "%*s %s %s %*s ", palavra, tipo) < 2)
        {
            break;
        }
        tabela_adiciona(h, palavra, tipo);
    }

    printf("Inserção tabela - %lfs\n", (double)(clock()-tempoInicio)/CLOCKS_PER_SEC);
    // }

    clock_t total = 0;
    for(int i = 0; i < NUMERO_LEITURAS; ++i)
    {
        int j = rand() % l->tamanho;
        l_elemento *el = l->inicio;
        while(j--)
        {
            el = el->proximo;
        }

        tempoInicio = clock();
        char *valor = (char*)tabela_valor(h, el->str);
        total += clock() - tempoInicio;

        if(valor)
        {
            //printf("%s - %s\n", el->str, valor);
        }
    }
    printf("Leitura de %d valores aleatórios da tabela - %lfs\n",
           NUMERO_LEITURAS, (double)total / CLOCKS_PER_SEC);

    lista_apaga(l);
    tabela_apaga(h);
    fclose(f);

    return 0;
}
