#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.c"
#include "grafo.c"
#include "lista.c"

lista *descobre_caminho(grafo *g, int origem, int destino, int obrigatorio)
{
    if(!g || origem < 0 || destino < 0 || obrigatorio < 0)
    {
        return 0;
    }

    lista *nova = lista_nova();
    if(!nova)
    {
        return 0;
    }

    int n1, n2;
    int *c1, *c2;
    c1 = grafo_bfs(g, origem, obrigatorio, &n1);
    c2 = grafo_bfs(g, obrigatorio, destino, &n2);

    for(int i = 0; i < n1; ++i)
    {
        char buff[10];
        sprintf(buff, "%d", c1[i]);
        lista_insere(nova, buff, -1);
    }

    for(int i = 1; i < n2; ++i)
    {
        char buff[10];
        sprintf(buff, "%d", c2[i]);
        lista_insere(nova, buff, -1);
    }

    free(c1);
    free(c2);

    return nova;
}

int simula_acontecimentos(lista *acoes, lista *tempos, int n)
{
    if(!acoes || !tempos || acoes->tamanho != tempos->tamanho)
    {
        return 0;
    }

    heap *h = heap_nova(acoes->tamanho);
    if(!h)
    {
        return 0;
    }


    for(elemento_lista *acao = acoes->raiz, *tempo = tempos->raiz;
        acao && tempo;
        acao = acao->proximo, tempo = tempo->proximo)
    {
        heap_insere(h, acao->str, atoi(tempo->str));
    }

    for(int i = 0; i < n; ++i)
    {
        char *str = heap_remove(h);
        printf("%d: %s\n", i+1, str);
        free(str);
    }

    heap_apaga(h);
    return 1;
}

/* Aqui começa o código de teste. Não modificar! */

int main() {
    /* teste problema 2.1 */
    {
        grafo *g = NULL;
        lista *l = NULL;
        int i;

        printf("* Problema 2.1 *\n");

        g = grafo_novo(8, DIGRAFO);

        grafo_adiciona(g, 1, 3);
        grafo_adiciona(g, 2, 3);
        grafo_adiciona(g, 2, 4);
        grafo_adiciona(g, 2, 5);
        grafo_adiciona(g, 3, 2);
        grafo_adiciona(g, 3, 4);
        grafo_adiciona(g, 4, 6);
        grafo_adiciona(g, 4, 7);
        grafo_adiciona(g, 5, 4);
        grafo_adiciona(g, 5, 6);
        grafo_adiciona(g, 5, 7);
        grafo_adiciona(g, 6, 7);

        l = descobre_caminho(g, 1, 7, 5);

        printf("Descobre caminho - Inicio 1, Fim 7, Passando por 5\nCaminho: ");
        for (i = 0; i < lista_tamanho(l); i++)
            printf("%s", lista_elemento(l, i));
        printf("\n\n");

        grafo_apaga(g);
        lista_apaga(l);
    }

    /* teste problema 2.2 */
    {
        FILE *f;
        char acao[21], tempo[5];
        lista *acoes, *tempos;

        printf("* Problema 2.2 *\n");

        f = fopen("acoes.txt", "r");
        acoes = lista_nova();
        tempos = lista_nova();

        while (fscanf(f, "%s %s", acao, tempo) == 2) {
            lista_insere(acoes, acao, -1);
            lista_insere(tempos, tempo, -1);
        }

        if (simula_acontecimentos(acoes, tempos, 4) == 0)
            printf("Erro ao executar a funcao\n");

        lista_apaga(acoes);
        lista_apaga(tempos);
        fclose(f);
    }

    return 0;
}
