#define GRAFO_PESQUISA
#include "grafo.c"
#include <stdio.h>

int count;
void printGraph(FILE *f, grafo *g)
{
    for(vert *v = g->vertices; v; v = v->proximo)
    {
        fprintf(f, "    _%d_%d [label=\"%d\"];\n", count, v->identificador,
                v->identificador);
        for(adj *a = v->adjacencias; a; a = a->proximo)
        {
            fprintf(f, "    _%d_%d -> _%d_%d;\n", count, v->identificador, count,
                    a->destino->identificador);
        }
    }
    ++count;
}

void caminho(grafo *g, int a, int b)
{
    Percurso percurso = grafo_ligados(g, a, b);
    if(percurso.nPercurso)
    {
        for(int i = 0; i < percurso.nPercurso; ++i)
        {
            if(i)
            {
                printf(" -> ");
            }
            printf("%d", percurso.percurso[i]->identificador);
        }
        puts("");
    }
    else
    {
        printf("Não há caminho entre %d e %d\n", a, b);
    }
}

int main()
{
    FILE *f = fopen("output.txt", "w");
    if(!f)
    {
        return -1;
    }

    grafo *g = grafo_novo();
    if(!g)
    {
        fprintf(stderr, "Erro ao criar grafo\n");
        return -1;
    }
    fprintf(f, "digraph {\n");

    grafo_vertice_adiciona(g, 1);
    grafo_vertice_adiciona(g, 2);
    grafo_vertice_adiciona(g, 3);
    grafo_vertice_adiciona(g, 4);
    grafo_vertice_adiciona(g, 7);

    grafo_aresta_adiciona(g, 1, 2);
    grafo_aresta_adiciona(g, 1, 3);
    grafo_aresta_adiciona(g, 2, 7);
    grafo_aresta_adiciona(g, 3, 1);
    grafo_aresta_adiciona(g, 3, 3);
    grafo_aresta_adiciona(g, 3, 4);
    grafo_aresta_adiciona(g, 3, 7);
    grafo_aresta_adiciona(g, 4, 1);
    grafo_aresta_adiciona(g, 7, 1);

    caminho(g, 1, 7);
    caminho(g, 4, 7);
    caminho(g, 3, 3);
    printGraph(f, g);

    grafo_aresta_remove(g, 3, 1);
    printGraph(f, g);

    grafo_vertice_remove(g, 3);
    caminho(g, 7, 4);
    printGraph(f, g);

    grafo_vertice_remove(g, 7);
    printGraph(f, g);

    grafo_vertice_adiciona(g, 9);
    grafo_aresta_adiciona(g, 9, 2);
    printGraph(f, g);

    fprintf(f, "}\n");
    grafo_apaga(g);
    fclose(f);

    return 0;
}
