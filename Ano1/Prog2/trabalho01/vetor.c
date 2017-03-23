/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2016/17           */
/*****************************************************************/

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* para buffer de leitura */
#define BUFFER_SIZE  256
#define QTHRESHOLD   16

vetor* vetor_novo()
{
	vetor* vec;

	/* aloca memoria para a estrutura vetor */
	vec = (vetor*)malloc(sizeof(vetor));
	if(vec == NULL)
	return NULL;

	vec->tamanho = 0;
	vec->capacidade = 0;
	vec->elementos = NULL;

	return vec;
}

void vetor_apaga(vetor* vec)
{
	int i;

	if(vec == NULL)
	return;

	/* liberta memoria de cada string */
	for (i = 0; i < vec->tamanho; i++)
	{
		free(vec->elementos[i].str);
	}

	/* liberta memoria dos apontares para as strings */
	free(vec->elementos);

	/* liberta memoria da estrutura vetor */
	free(vec);
}

int vetor_atribui(vetor* vec, int pos, const char* valor)
{
	unsigned int len_valor;

	if (vec == NULL || pos < 0 || pos >= vec->tamanho)
	return -1;

	len_valor = strlen(valor);

	/* reserva mais espaco se necessario */
	if(len_valor > strlen(vec->elementos[pos].str))
	{
		vec->elementos[pos].str = (char*)realloc(vec->elementos[pos].str, (len_valor+1)*sizeof(char));
		if(vec->elementos[pos].str == NULL)
		return -1;
	}

	/* copia valor */
	strcpy(vec->elementos[pos].str, valor);

	return pos;
}

int vetor_tamanho(vetor* vec)
{
	if(vec == NULL)
	return -1;

	return vec->tamanho;
}

const char* vetor_elemento(vetor* vec, int indice)
{
	if (vec == NULL || indice < 0 || indice >= vec->tamanho)
	return NULL;

	return vec->elementos[indice].str;
}

int vetor_insere(vetor* vec, const char* valor, int pos)
{
	int i;

	if(vec == NULL || pos < -1 || pos > vec->tamanho)
		return -1;

	/* aumenta elementos do vetor se capacidade nao for suficiente */
	if(vec->tamanho == vec->capacidade)
	{
		if(vec->capacidade == 0)
		vec->capacidade = 1;
		else
		vec->capacidade *= 2;

		vec->elementos = (v_elemento*)realloc(vec->elementos, vec->capacidade * sizeof(v_elemento));
		if(vec->elementos == NULL)
		return -1;
	}

	/* se pos=-1 insere no fim do vetor */
	if(pos == -1)
		pos = vec->tamanho;

	/* copia todos os elementos a partir da posicao pos ate' ao fim do vetor para pos+1 */
	for(i=vec->tamanho-1; i>=pos; i--)
	{
		vec->elementos[i+1] = vec->elementos[i];
	}

	/* aloca espaco para a nova string na posicao pos */
	vec->elementos[pos].str = (char*)calloc(strlen(valor)+1, sizeof(char));
	if(vec->elementos[pos].str == NULL)
	return -1;

	/* copia valor */
	strcpy(vec->elementos[pos].str, valor);

	vec->tamanho++;

	return pos;
}

int vetor_remove(vetor* vec, int pos)
{
	int i;

	if(vec == NULL || pos < 0 || pos >= vec->tamanho)
	return -1;

	/* liberta string na posicao a remover */
	free(vec->elementos[pos].str);

	/* copia todos os elementos a partir da posicao pos+1 ate' ao fim do vetor para pos */
	for(i=pos+1; i<vec->tamanho; i++)
	{
		vec->elementos[i-1] = vec->elementos[i];
	}

	vec->tamanho--;

	return 0;
}

int vetor_pesquisa(vetor* vec, const char* valor)
{
	int i;

	if(vec == NULL)
	return -1;

	/* pesquisa sequencial */
	for (i = 0; i < vec->tamanho; i++)
	{
		if (strcmp(vec->elementos[i].str, valor) == 0)
		return i;
	}

	return -1;
}

int vetor_ordena_ins(vetor* vec)
{
	int i, j;
	char *tmp;

	if(vec == NULL)
	return -1;

	/* ordenacao por insercao */
	for (i = 1; i < vec->tamanho; i++)
	{
		tmp = vec->elementos[i].str;
		for (j = i; j > 0 && strcmp(tmp, vec->elementos[j-1].str) < 0; j--)
		{
			vec->elementos[j] = vec->elementos[j-1];
		}
		vec->elementos[j].str = tmp;
	}

	return 0;
}

/* funções a implementar */

// NOTE(Gonçalo): Esta função _NÃO_ verifica se o idxA e o idxB estão dentro dos limites
void vetor__unsafeSwap(vetor *vec, int idxA, int idxB)
{
    v_elemento tempA = vec->elementos[idxA];
    vec->elementos[idxA] = vec->elementos[idxB];
    vec->elementos[idxB] = tempA;
}

int vetor_ordena_sel(vetor* vec)
{
    if(!vec)
    {
        return -1;
    }

    int size = vec->tamanho;
    for(int i = 0; i < size; ++i)
    {
        int iMin = i;
        for(int j = i+1; j < size; ++j)
        {
            if(strcmp(vec->elementos[j].str, vec->elementos[iMin].str) < 0)
            {
                iMin = j;
            }
        }
        if(iMin != i)
        {
            vetor__unsafeSwap(vec, iMin, i);
        }
    }

    return 0;
}

void vetor__qsortPartition(vetor *vec, int low, int high)
{
    int size = high - low + 1;
    if(size < 2)
    {
        return;
    }

    int pivotIdx = (rand() % size) + low;
    vetor__unsafeSwap(vec, pivotIdx, high);
    char *pivot = vec->elementos[high].str;

    int left = low-1, right = high;
    for(;;)
    {
        do
        {
            ++left;
        } while(left < high && strcmp(vec->elementos[left].str, pivot) < 0);

        do
        {
            --right;
        } while(right > low && strcmp(vec->elementos[right].str, pivot) > 0);

        if(left < right)
        {
            vetor__unsafeSwap(vec, left, right);
        }
        else
        {
            break;
        }
    }
    vetor__unsafeSwap(vec, left, high); // NOTE(Gonçalo): Restaurar pivot em left

    vetor__qsortPartition(vec, low, left-1);
    vetor__qsortPartition(vec, left+1, high);

    return;
}

int vetor_ordena_qsort(vetor* vec)
{
    if(!vec)
    {
        return -1;
    }
	vetor__qsortPartition(vec, 0, vec->tamanho-1);
    return 0;
}

int vetor__qsortMedian(vetor *vec, int low, int high)
{
    int middle = (low+high)/2;

    int lowMid = strcmp(vec->elementos[low].str, vec->elementos[middle].str);
    int midHigh = strcmp(vec->elementos[middle].str, vec->elementos[high].str);
    int lowHigh = strcmp(vec->elementos[low].str, vec->elementos[high].str);

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
void vetor__qsortBetterPartition(vetor *vec, int low, int high)
{
    int size = high - low + 1;
    if(size < 150)
    {
        // NOTE(Gonçalo): Sort por inserção
        for(int i = low+1; i <= high; ++i)
        {
            char *temp = vec->elementos[i].str;
            int j;
            for(j = i; j > low && strcmp(temp, vec->elementos[j-1].str) < 0; --j)
            {
                vec->elementos[j] = vec->elementos[j-1];
            }
            vec->elementos[j].str = temp;
        }
        return;
    }

    // NOTE(Gonçalo): Dutch National Flag Problem
    // Three-way partition
    int pivotIdx = vetor__qsortMedian(vec, low, high);
    char *pivot = vec->elementos[pivotIdx].str;

    int left = low, iter = low, right = high;
    while(iter <= right)
    {
        int comp = strcmp(vec->elementos[iter].str, pivot);
        if(comp < 0)
        {
            // NOTE(Gonçalo): Menor que pivot
            vetor__unsafeSwap(vec, left, iter);
            ++left; ++iter;
        }
        else if(comp > 0)
        {
            // NOTE(Gonçalo): Maior que pivot
            vetor__unsafeSwap(vec, iter, right);
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
        vetor__qsortBetterPartition(vec, low, left-1);
    }
    if(right < high)
    {
        vetor__qsortBetterPartition(vec, right+1, high);
    }

    return;
}

int vetor_ordena(vetor* vec)
{
    if(!vec)
    {
        return -1;
    }

    vetor__qsortBetterPartition(vec, 0, vec->tamanho-1);

	return 0;
}

vetor* le_ficheiro(char* nome)
{
    FILE *file = fopen(nome, "r");
    if(!file)
    {
        return 0;
    }

    vetor *result = vetor_novo();
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

        if(vetor_insere(result, buffer, -1) == -1)
        {
            vetor_apaga(result);
            fclose(file);
            return 0;
        }
    }

	return result;
}
