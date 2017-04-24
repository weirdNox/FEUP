/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2016/17          */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"


/* retorna apontador para vertice correspondente a um dado identificador */
vert* encontra_vertice(grafo* g, int vertice)
{
    if(g == NULL)
      return NULL;

    for(vert* v=g->vertices; v!=NULL; v=v->proximo)
        if(v->identificador == vertice)
          return v;

    return NULL;
}

/* cria grafo vazio */
grafo* grafo_novo()
{
    grafo *g = malloc(sizeof(*g));
    if(!g)
    {
        return 0;
    }

    g->tamanho = 0;
    g->vertices = 0;

	return g;
}

/* elimina um grafo, libertando toda a memoria ocupada */
void grafo_apaga(grafo* g)
{
    if(!g)
    {
        return;
    }

    vert *v = g->vertices;
    while(v)
    {
        adj *a = v->adjacencias;
        while(a)
        {
            adj *aProx = a->proximo;
            free(a);
            a = aProx;
        }
        vert *vProx = v->proximo;
        free(v);
        v = vProx;
    }

    free(g);
}

/* adiciona um vertice ao grafo */
int grafo_vertice_adiciona(grafo* g, int vertice)
{
    if(!g || vertice <= 0)
    {
        return -1;
    }

    vert *v = encontra_vertice(g, vertice);
    if(v)
    {
        return 0;
    }

    v = malloc(sizeof(*v));
    if(!v)
    {
        return -1;
    }
    v->adjacencias = 0;
    v->identificador = vertice;
    v->proximo = g->vertices;
    g->vertices = v;
    ++g->tamanho;

    return 1;
}

/* remove um vertice do grafo */
int grafo_vertice_remove(grafo* g, int vertice)
{
    if(!g || vertice <= 0)
    {
        return -1;
    }

    vert *v = encontra_vertice(g, vertice);
    if(!v)
    {
        return 0;
    }

    vert *vTeste = g->vertices;
    vert *vAnterior = 0;
    while(vTeste)
    {
        if(vTeste == v)
        {
            adj *a = vTeste->adjacencias;
            while(a)
            {
                adj *aProx = a->proximo;
                free(a);
                a = aProx;
            }

            if(vAnterior)
            {
                vAnterior->proximo = vTeste->proximo;
            }
            else
            {
                g->vertices = vTeste->proximo;
            }
        }
        else
        {
            adj *a = vTeste->adjacencias;
            adj *aAnterior = 0;
            while(a)
            {
                if(a->destino == v)
                {
                    if(aAnterior)
                    {
                        aAnterior->proximo = a->proximo;
                    }
                    else
                    {
                        vTeste->adjacencias = a->proximo;
                    }
                    free(a);
                    break;
                }

                aAnterior = a;
                a = a->proximo;
            }
        }

        vAnterior = vTeste;
        vTeste = vTeste->proximo;
    }

    --g->tamanho;
    free(v);

    return 1;
}

/* verifica se existe um dado vertice no grafo */
int grafo_vertice_existe(grafo* g, int vertice)
{
    if(!g || vertice <= 0)
    {
        return -1;
    }
    vert *v = encontra_vertice(g, vertice);
    if(v)
    {
        return 1;
    }
    return 0;
}

/* verifica se existe uma aresta entre os vertices origem e destino */
int grafo_aresta_existe(grafo *g, int origem, int destino)
{
    if(!g || origem <= 0 || destino <= 0)
    {
        return -1;
    }

    vert *orig = encontra_vertice(g, origem);
    vert *dest = encontra_vertice(g, destino);
    if(!orig || !dest)
    {
        return -1;
    }

    adj *a = orig->adjacencias;
    while(a)
    {
        if(a->destino == dest)
        {
            return 1;
        }
        a = a->proximo;
    }

    return 0;
}

/* adiciona uma aresta ao grafo*/
int grafo_aresta_adiciona(grafo *g, int origem, int destino)
{
    if(!g || origem <= 0 || destino <= 0)
    {
        return -1;
    }

    vert *orig = encontra_vertice(g, origem);
    vert *dest = encontra_vertice(g, destino);
    if(!orig || !dest)
    {
        return -1;
    }

    adj *a = orig->adjacencias;
    while(a)
    {
        if(a->destino == dest)
        {
            return 0;
        }
        a = a->proximo;
    }

    a = malloc(sizeof(*a));
    if(!a)
    {
        return -1;
    }
    a->destino = dest;
    a->proximo = orig->adjacencias;
    orig->adjacencias = a;

    return 1;
}

/* remove uma aresta do grafo*/
int grafo_aresta_remove(grafo *g, int origem, int destino)
{
    if(!g || origem <= 0 || destino <= 0)
    {
        return -1;
    }

    vert *orig = encontra_vertice(g, origem);
    vert *dest = encontra_vertice(g, destino);
    if(!orig || !dest)
    {
        return -1;
    }

    adj *a = orig->adjacencias;
    adj *aAnterior = 0;
    while(a)
    {
        if(a->destino == dest)
        {
            if(aAnterior)
            {
                aAnterior->proximo = a->proximo;
            }
            else
            {
                orig->adjacencias = a->proximo;
            }
            free(a);
            return 1;
        }

        aAnterior = a;
        a = a->proximo;
    }

    return 0;
}


// NOTE(Gonçalo): Extra
#ifdef GRAFO_PESQUISA
#define arrayCount(arr) (sizeof(arr)/sizeof(arr[0]))

typedef struct
{
    int nPercurso;
    vert *percurso[250];
} Percurso;

Percurso grafo_ligados(grafo *g, int origem, int destino)
{
    Percurso percursoVazio = {};
    if(!g || origem <= 0 || destino <= 0)
    {
        return percursoVazio;
    }

    vert *orig = encontra_vertice(g, origem);
    vert *dest = encontra_vertice(g, destino);
    if(!orig || !dest)
    {
        return percursoVazio;
    }

    int nVisitados = 0;
    vert *visitados[1<<10];

    int filaHead = 1;
    int filaTail = 0;
    Percurso filaVert[100] = {{.nPercurso = 1, .percurso = {orig}}};

    while(filaHead != filaTail)
    {
        Percurso *teste = filaVert + filaTail;
        filaTail = (filaTail+1)%arrayCount(filaVert);

        vert *atual = teste->percurso[teste->nPercurso-1];
        visitados[nVisitados++] = atual;

        if(atual == dest)
        {
            return *teste;
        }

        ++teste->nPercurso;
        for(adj *a = atual->adjacencias; a; a = a->proximo)
        {
            vert *next = a->destino;
            int existe = 0;
            for(int i = 0; i < nVisitados; ++i)
            {
                if(next == visitados[i])
                {
                    existe = 1;
                    break;
                }
            }
            if(existe)
            {
                continue;
            }

            teste->percurso[teste->nPercurso-1] = next;
            filaVert[filaHead] = *teste;
            filaHead = (filaHead+1)%arrayCount(filaVert);
        }
    }

    return percursoVazio;
}
#endif
