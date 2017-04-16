/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2016/17          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <stdio.h>


/* elemento da lista de vertices */
typedef struct _vert
{
    int identificador;              /* identificador do vertice */
    struct _adj *adjacencias; /* apontador para lista de adjacencias */
    struct _vert *proximo;    /* apontador para o proximo vertice */
} vert;

/* elemento da lista de adjacencias */
typedef struct _adj
{
    struct _vert *destino;    /* apontador para o vertice destino */
    struct _adj *proximo;     /* apontador para a proxima adjacencia */
} adj;

/* grafo e' apontador para lista de vertices */
typedef struct
{
    int tamanho;
    vert *vertices; /* apontador para lista de vertices */
} grafo;

/* cria grafo vazio */
grafo* grafo_novo ();

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g);

/* adiciona um vertice ao grafo */
int grafo_vertice_adiciona(grafo* g, int vertice);

/* remove um vertice do grafo */
int grafo_vertice_remove(grafo* g, int vertice);

/* verifica se existe um dado vertice no grafo */
int grafo_vertice_existe(grafo* g, int vertice);

/* verifica se existe uma aresta entre os vertices origem e destino */
int grafo_aresta_existe(grafo *g, int origem, int destino);

/* adiciona uma aresta ao grafo*/
int grafo_aresta_adiciona(grafo *g, int origem, int destino);

/* remove uma aresta do grafo*/
int grafo_aresta_remove(grafo *g, int origem, int destino);

/* retorna o apontador para um dado vertice do grafo */
vert* encontra_vertice(grafo* g, int vertice);

#endif
