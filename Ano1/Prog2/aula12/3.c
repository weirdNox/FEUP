#include "grafo.c"

#include <stdio.h>

int *caminho(grafo *g, int inicio, int fim, int *n, int peso17)
{
    if(peso17 <= 0)
    {
        return 0;
    }
    if(peso17 > 1)
    {
        grafo_remove(g, 1, 7);
    }

    int *caminho = grafo_bfs(g, inicio, fim, n);

    if(peso17 > 1)
    {
        grafo_adiciona(g, 1, 7);
    }

    return caminho;
}

void imprimirELibertarCaminho(int *caminho, int n)
{
    for(int i = 0; i < n; ++i)
    {
        if(i)
        {
            printf(" -> ");
        }
        printf("%d", caminho[i]);
    }
    puts("");
    free(caminho);
}

int main()
{
    grafo *g = grafo_novo(8, NAODIRECIONADO);
    grafo_adiciona(g, 1, 2);
    grafo_adiciona(g, 1, 4);
    grafo_adiciona(g, 1, 7);
    grafo_adiciona(g, 2, 3);
    grafo_adiciona(g, 2, 5);
    grafo_adiciona(g, 3, 6);
    grafo_adiciona(g, 4, 7);
    grafo_adiciona(g, 5, 6);
    grafo_adiciona(g, 5, 7);
    grafo_adiciona(g, 6, 7);

    grafo_imprime(g);

    int n;
    imprimirELibertarCaminho(grafo_bfs(g, 1, 6, &n), n);

    for(int i = 2; i < 8; ++i)
    {
        printf("\nPara o %d:\n", i);
        imprimirELibertarCaminho(caminho(g, 1, i, &n, 1), n);
        imprimirELibertarCaminho(caminho(g, 1, i, &n, 2), n);
    }

    grafo_apaga(g);

    return 0;
}
