/*****************************************************************/
/*          Biblioteca vetorg | PROG2 | MIEEC | 2016/17           */
/*****************************************************************/

#include "vetorg.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define QTHRESHOLD  16

vetorg* vetorg_novo()
{
	vetorg* vec;

	/* aloca memoria para a estrutura vetorg */
	vec = (vetorg*)malloc(sizeof(vetorg));
	if(vec == NULL)
	return NULL;

	vec->tamanho = 0;
	vec->capacidade = 0;
	vec->elementos = NULL;

	return vec;
}

void vetorg_apaga(vetorg* vec)
{
	int i;

	if(vec == NULL)
	return;

	/* liberta memoria de cada string */
	for (i = 0; i < vec->tamanho; i++)
	{
		free(vec->elementos[i].titulo);
	}

	/* liberta memoria dos apontares para os registos */
	free(vec->elementos);

	/* liberta memoria da estrutura vetorg */
	free(vec);
}

int vetorg_tamanho(vetorg* vec)
{
	if(vec == NULL)
	return -1;

	return vec->tamanho;
}


int vetorg_insere(vetorg* vec, int votos, float classifica, int ano, const char* titulo, int pos)
{
	return -1;
}

int vetorg_ordena(vetorg* vec, comp ordem)
{
	return -1;
}

int comp_ano_asc(const vg_elemento a, const vg_elemento b){
    if(b.ano > a.ano)
        return -1;
    if(a.ano > b.ano)
        return 1;
    return 0;
}

int comp_votos_asc(const vg_elemento a, const vg_elemento b)
{
		return 0;
}

int comp_classifica_asc(const vg_elemento a, const vg_elemento b)
{
	return 0;
}

int comp_titulo_asc(const vg_elemento a, const vg_elemento b)
{
	return 0;
}

vetorg *le_ficheiro_g(char* nome)
{
		return NULL;
}
