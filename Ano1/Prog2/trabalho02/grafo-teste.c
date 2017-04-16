/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2016/17          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define INICIA_TESTE() \
	int erros = 0;

#define ERRO(msg) \
	{ \
	printf("\n\t"#msg); \
		erros++; \
	}

#define FINALIZA_TESTE() \
	if (!erros) \
		printf("OK\n"); \
	else \
		printf("\n"); \
	return erros;

/* cria um grafo, insere vertices e arestas
   args: numero de vertices, v1, v2, ... , numero de arestas, o1, d1, o2, d2, ... */

grafo* _g(int n, ...)
{
	va_list argp; grafo *g;
	int i, x, y, m;
	vert *v; adj *a;

	g = calloc(1, sizeof(grafo));
	va_start(argp, n);
	for(i=0; i<n; i++)
	{
		x = va_arg(argp, int);
		v = calloc(1,sizeof(vert));
		v->identificador = x;
		v->proximo = g->vertices;
		g->vertices = v;
		g->tamanho++;
	}
	m = va_arg(argp, int);
	for(i=0; i<m; i++)
	{
	    x = va_arg(argp, int);
	    y = va_arg(argp, int);
	    v=encontra_vertice(g,x);
	    a=calloc(1, sizeof(adj));
	    a->destino = encontra_vertice(g,y);
	    a->proximo = v->adjacencias;
	    v->adjacencias = a;
	}
	return g;
}

int teste_grafo_novo()
{
	INICIA_TESTE()

	grafo *g;

	printf("grafo_novo(): ");

	g = grafo_novo();
	if(!g)
	{
		ERRO("novo grafo invalido")
		FINALIZA_TESTE();
	}

	if(g->vertices)
    {
        ERRO("lista de vertices nao inicializada")
        FINALIZA_TESTE();
    }

	grafo_apaga(g);

	FINALIZA_TESTE()
}

int teste_grafo_vertice_existe()
{
    INICIA_TESTE();

    grafo *g=_g(4,8,7,6,5,-1);

    printf("grafo_vertice_existe(): ");

    if(grafo_vertice_existe(g,6) != 1)
        ERRO("pesquisa de vertice existente deveria retornar 1");

    if(grafo_vertice_existe(g,8) != 1)
        ERRO("pesquisa de vertice existente deveria retornar 1");

    if(grafo_vertice_existe(g,4) != 0)
        ERRO("pesquisa de vertice nao existente deveria retornar 0");

    if(grafo_vertice_existe(NULL,6) != -1)
        ERRO("pesquisa em grafo NULL deveria retornar -1");

   	grafo_apaga(g);

	FINALIZA_TESTE()
}

int teste_grafo_vertice_adiciona()
{
    INICIA_TESTE();

    grafo *g=_g(4,1,2,3,4,-1);

    printf("grafo_vertice_adiciona(): ");

    if(grafo_vertice_adiciona(g,6) != 1)
      ERRO("adicao de vertice nao existente deveria retornar 1");

		if(g->tamanho != 5)
			ERRO("adicao de vertice nao existente deveria aumentar o tamanho");

		if(encontra_vertice(g, 6) == NULL)
			ERRO("adicao de vertice nao existente não concretizada");

    if(grafo_vertice_adiciona(g,8) != 1)
      ERRO("adicao de vertice existente deveria retornar 0");

		if(grafo_vertice_adiciona(g,-2) != -1)
			ERRO("adicao de vertice com indice invalido deveria retornar -1")

    if(grafo_vertice_adiciona(NULL,6) != -1)
      ERRO("adicao de vertice em grafo NULL deveria retornar -1");


   	grafo_apaga(g);

	FINALIZA_TESTE()
}

int teste_grafo_vertice_remove()
{
    INICIA_TESTE();

    grafo *g=_g(4,6,8,10,12, -1);

    printf("grafo_vertice_remove(): ");

    if(grafo_vertice_remove(g,6) != 1)
      ERRO("remocao de vertice existente deveria retornar 1");

		if(g->tamanho != 3)
			ERRO("adicao de vertice existente deveria diminuir o tamanho");

		if(encontra_vertice(g, 6) != NULL)
			ERRO("remocao de vertice existente não concretizada");

    if(grafo_vertice_remove(g,3) != 0)
      ERRO("remocao de vertice nao existente deveria retornar 0");

    if(grafo_vertice_remove(NULL,5) != -1)
      ERRO("remocao de vertice de grafo NULL deveria retornar -1");

   	grafo_apaga(g);

	FINALIZA_TESTE()
}


int teste_grafo_aresta_existe()
{
	INICIA_TESTE()

	grafo *g=_g(5, 1,2,3,4,6, 10, 1,2, 2,3, 3,4, 4,6, 1,3, 2,4, 3,6, 6,1, 6,2, 6,4);

	printf("grafo_aresta_existe(): ");

	if(grafo_aresta_existe(g,2,3) != 1)
		ERRO("pesquisa de aresta existente deveria retornar 1")

	if(grafo_aresta_existe(g,6,4) != 1)
		ERRO("pesquisa de aresta existente deveria retornar 1")

	if(grafo_aresta_existe(g,2,6) != 0)
		ERRO("pesquisa de aresta nao existente deveria retornar 0")

	if(grafo_aresta_existe(g,1,5) != -1)
		ERRO("pesquisa de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_existe(g,5,3) != -1)
		ERRO("pesquisa de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_existe(g,0,5) != -1)
		ERRO("pesquisa de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_existe(g,-2,7) != -1)
		ERRO("retorno deveria ser -1 ao pesquisar com indice invalido")

	if(grafo_aresta_existe(NULL,2,7) != -1)
		ERRO("retorno deveria ser -1 ao pesquisar em grafo NULL")


	grafo_apaga(g);

	FINALIZA_TESTE()
}

int teste_grafo_aresta_adiciona()
{
	INICIA_TESTE()

	grafo *g=_g(5, 1,2,3,4,6, 10, 1,2, 2,3, 3,4, 4,6, 1,3, 2,4, 3,6, 6,1, 6,2, 6,4);

	printf("grafo_aresta_adiciona(): ");

	if(grafo_aresta_adiciona(g,1,4) != 1)
		ERRO("adicao de aresta nao existente deveria retornar 1")

	if(grafo_aresta_adiciona(g,6,4) != 0)
		ERRO("adicao de aresta existente deveria retornar 0")

	if(grafo_aresta_adiciona(g,1,4) != 0)
		ERRO("adicao de aresta existente deveria retornar 0")

	if(grafo_aresta_adiciona(g,1,5) != -1)
		ERRO("adicao de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_adiciona(g,5,3) != -1)
		ERRO("adicao de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_adiciona(g,0,5) != -1)
		ERRO("adicao de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_adiciona(NULL,2,7) != -1)
		ERRO("adicao de aresta em grafo NULL deveria retornar -1")

	grafo_apaga(g);

	FINALIZA_TESTE()
}

int teste_grafo_aresta_remove()
{
	INICIA_TESTE()

	grafo *g=_g(5, 1,2,3,4,6, 10, 1,2, 2,3, 3,4, 4,6, 1,3, 2,4, 3,6, 6,1, 6,2, 6,4);

	printf("grafo_aresta_remove(): ");

	if(grafo_aresta_remove(g,1,3) != 1)
		ERRO("remocao de aresta existente deveria retornar 1")

	if(grafo_aresta_remove(g,6,3) != 0)
		ERRO("remocao de aresta nao existente deveria retornar 0")

	if(grafo_aresta_remove(g,1,3) != 0)
		ERRO("remocao de aresta nao existente deveria retornar 0")

	if(grafo_aresta_remove(g,1,5) != -1)
		ERRO("remocao de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_remove(g,5,3) != -1)
		ERRO("remocao de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_remove(g,0,5) != -1)
		ERRO("remocao de aresta com origem ou destino nao existente deveria retornar -1")

	if(grafo_aresta_remove(NULL,2,7) != -1)
		ERRO("remocao de aresta em grafo NULL deveria retornar -1")

	grafo_apaga(g);

	FINALIZA_TESTE()
}

int main()
{
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	int erros = 0;
	erros += teste_grafo_novo();
	erros += teste_grafo_vertice_existe();
	erros += teste_grafo_vertice_adiciona();
	erros += teste_grafo_vertice_remove();
	erros += teste_grafo_aresta_existe();
	erros += teste_grafo_aresta_adiciona();
	erros += teste_grafo_aresta_remove();

	if (!erros)
		printf("FIM DE TODOS OS TESTES.\n");
	else
		printf("FOI ENCONTRADO UM TOTAL DE %d ERROS.\n", erros);
	return 0;
}
