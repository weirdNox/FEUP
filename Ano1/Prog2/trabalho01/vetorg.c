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
    if(!vec || !titulo || pos < -1 || pos > vec->tamanho)
    {
        return -1;
    }

    if(vec->tamanho == vec->capacidade)
    {
        if(!vec->capacidade)
        {
            vec->capacidade = 1;
        }
        else
        {
            vec->capacidade *= 2;
        }

        vg_elemento *temp = realloc(vec->elementos, sizeof(*temp)*vec->capacidade);
        if(!temp)
        {
            return -1;
        }
        vec->elementos = temp;
    }

    if(pos == -1)
    {
        pos = vec->tamanho;
    }

    for(int i = vec->tamanho - 1; i >= pos; --i)
    {
        vec->elementos[i+1] = vec->elementos[i];
    }

    vg_elemento *atual = vec->elementos + pos;
    atual->votos = votos;
    atual->classifica = classifica;
    atual->ano = ano;

    atual->titulo = malloc(sizeof(char)*(strlen(titulo)+1));
    if(!atual->titulo)
    {
        return -1;
    }
    strcpy(atual->titulo, titulo);
    atual->titulo[strlen(titulo)] = 0;

    ++vec->tamanho;

	return pos;
}

// NOTE(Gonçalo): Esta função _NÃO_ verifica se o idxA e o idxB estão dentro dos limites
void vetorg__unsafeSwap(vetorg *vec, int idxA, int idxB)
{
    vg_elemento tempA = vec->elementos[idxA];
    vec->elementos[idxA] = vec->elementos[idxB];
    vec->elementos[idxB] = tempA;
}

int vetorg__qsortMedian(vetorg *vec, comp order, int low, int high)
{
    int middle = (low+high)/2;

    int lowMid = order(vec->elementos[low], vec->elementos[middle]);
    int midHigh = order(vec->elementos[middle], vec->elementos[high]);
    int lowHigh = order(vec->elementos[low], vec->elementos[high]);

    if((lowMid > 0 && lowHigh < 0) ||
       (lowMid < 0 && lowHigh > 0))
    {
        return low;
    }
    if((lowMid < 0 && midHigh < 0) ||
       (lowMid > 0 && midHigh > 0))
    {
        return middle;
    }

    return high;
}

/* NOTE(Gonçalo):
    Otimizações em vigor:
     - Quando tamanho menor que um threshold, usar Insertion Sort
     - Escolher pivot como mediana dos extremos e o valor médio
     - Usar um algoritmo de partição em 3 partes (Dutch National Flag problem). Temos
       os elementos menor que o pivot, iguais e maiores
*/
void vetorg__qsortBetterPartition(vetorg *vec, comp order, int low, int high)
{
    int size = high - low + 1;
    if(size < 150)
    {
        // NOTE(Gonçalo): Sort por inserção
        for(int i = low+1; i <= high; ++i)
        {
            vg_elemento temp = vec->elementos[i];
            int j;
            for(j = i; j > low && order(temp, vec->elementos[j-1]) < 0; --j)
            {
                vec->elementos[j] = vec->elementos[j-1];
            }
            vec->elementos[j] = temp;
        }
        return;
    }

    // NOTE(Gonçalo): Dutch National Flag Problem
    // Three-way partition
    int pivotIdx = vetorg__qsortMedian(vec, order, low, high);
    vg_elemento pivot = vec->elementos[pivotIdx];

    int left = low, iter = low, right = high;
    while(iter <= right)
    {
        int comp = order(vec->elementos[iter], pivot);
        if(comp < 0)
        {
            // NOTE(Gonçalo): Menor que pivot
            vetorg__unsafeSwap(vec, left, iter);
            ++left; ++iter;
        }
        else if(comp > 0)
        {
            // NOTE(Gonçalo): Maior que pivot
            vetorg__unsafeSwap(vec, iter, right);
            --right;
        }
        else
        {
            // NOTE(Gonçalo): Igual
            ++iter;
        }
    }

    if(left > low)
    {
        vetorg__qsortBetterPartition(vec, order, low, left-1);
    }
    if(right < high)
    {
        vetorg__qsortBetterPartition(vec, order, right+1, high);
    }

    return;
}

int vetorg_ordena(vetorg* vec, comp ordem)
{
    if(!vec || !ordem)
    {
        return -1;
    }
    vetorg__qsortBetterPartition(vec, ordem, 0, vec->tamanho-1);

	return 0;
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
    if(a.votos < b.votos)
    {
        return -1;
    }
    if(a.votos > b.votos)
    {
        return 1;
    }
    return 0;
}

int comp_classifica_asc(const vg_elemento a, const vg_elemento b)
{
    if(a.classifica < b.classifica)
    {
        return -1;
    }
    if(a.classifica > b.classifica)
    {
        return 1;
    }
    return 0;
}

int comp_titulo_asc(const vg_elemento a, const vg_elemento b)
{
    return strcmp(a.titulo, b.titulo);
}

vetorg *le_ficheiro_g(char* nome)
{
    FILE *file = fopen(nome, "r");
    if(!file)
    {
        return 0;
    }

    vetorg *result = vetorg_novo();
    if(!result)
    {
        fclose(file);
        return 0;
    }

    char buffer[1<<13];
    while(fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), file))
    {
        for(int i = strlen(buffer)-1;
            i >= 0 && (buffer[i] == '\n' || buffer[i] == '\r');
            --i)
        {
            buffer[i] = 0;
        }

        char *token = strtok(buffer, " ");
        int votos = atoi(token);
        token = strtok(0, " ");
        float classifica = atof(token);
        token = strtok(0, " ");
        int ano = atoi(token);

        char *titulo = token + strlen(token) + 1;

        if(vetorg_insere(result, votos, classifica, ano, titulo, -1) == -1)
        {
            vetorg_apaga(result);
            fclose(file);
            return 0;
        }
    }

	return result;
}
