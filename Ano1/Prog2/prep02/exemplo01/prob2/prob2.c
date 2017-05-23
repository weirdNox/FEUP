#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.c"
#include "grafo.c"
#include "tabdispersao.c"


/*** problema 2.1 ***/
vetor* td_pesquisa_inversa(tabela_dispersao *td, const char *valor)
{
    if(!td || !valor)
    {
        return 0;
    }

    vetor *result = vetor_novo();
    if(!result)
    {
        return 0;
    }
    for(int i = 0; i < td->tamanho; ++i)
    {
        td_elemento *el = td->elementos[i];
        while(el)
        {
            if(strcmp(el->obj->valor, valor) == 0)
            {
                if(vetor_insere(result, el->obj->chave, -1) == -1)
                {
                    vetor_apaga(result);
                    return 0;
                }
            }
            el = el->proximo;
        }
    }

	return result;
}

/*** problema 2.2 ***/
grafo * grafo_uniao(grafo *g1, grafo *g2)
{
	/* complexidade do algoritmo: O(n^2)
     * Temos um loop a percorrer todos os vertices (v) e outro, dentro, todas as suas
     * arestas (a) (v*a)
     */

    if(!g1 || !g2 || g1->tamanho != g2->tamanho)
    {
        return 0;
    }

    grafo *result = grafo_novo(g1->tamanho, DIGRAFO);
    if(!result)
    {
        return 0;
    }

    for(int i = 0; i < g1->tamanho; ++i)
    {
        lista_no *no = g1->adjacencias[i].inicio;
        while(no)
        {
            grafo_adiciona(result, i, no->vertice);
            no = no->proximo;
        }

        no = g2->adjacencias[i].inicio;
        while(no)
        {
            grafo_adiciona(result, i, no->vertice);
            no = no->proximo;
        }
    }

	return result;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_LINE	100
#define MAX_WORD	50
#define PESQ "Netherlands"

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	/* teste problema 2.1 */
	{
		int i;
		char aeroporto[MAX_WORD], pais[MAX_WORD];
		puts("* Problema 2.1 *");
		tabela_dispersao * td = tabela_nova(300, hash_krm);
		FILE *fp=fopen("aeroportos.txt", "r");
		while(fscanf(fp, "%s\t%s", aeroporto, pais) == 2)
			tabela_insere(td,aeroporto,pais);
		vetor *v=td_pesquisa_inversa(td, PESQ);
		printf("%s airports:\n",PESQ);
		for (i=0; i<vetor_tamanho(v);i++) {
			printf("%d: %s\n",i+1,vetor_elemento(v,i));
		}
        vetor_apaga(v);
		tabela_apaga(td);
        fclose(fp);
	}

	/* teste problema 2.2 */
	{
		puts("\n\n* Problema 2.2 *");
		grafo * g1 = grafo_novo(8, DIGRAFO);
		grafo * g2 = grafo_novo(8, DIGRAFO);
		grafo_adiciona(g1,0,4);
		grafo_adiciona(g1,1,0);
		grafo_adiciona(g1,1,5);
		grafo_adiciona(g1,2,1);
		grafo_adiciona(g1,3,2);
		grafo_adiciona(g1,4,3);
		grafo_adiciona(g1,5,4);
		grafo_adiciona(g1,6,3);
		grafo_adiciona(g1,7,2);
		grafo_adiciona(g1,7,6);
		grafo_adiciona(g2,0,4);
		grafo_adiciona(g2,1,0);
		grafo_adiciona(g2,1,4);
		grafo_adiciona(g2,1,5);
		grafo_adiciona(g2,2,3);
		grafo_adiciona(g2,5,4);
		grafo_adiciona(g2,6,2);
		grafo_adiciona(g2,7,3);
		grafo * g3=grafo_uniao(g1,g2);
		if (g3) grafo_imprime(g3);
		grafo_apaga(g1);
		grafo_apaga(g2);
		grafo_apaga(g3);
	}

	return 0;
}
