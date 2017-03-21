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

int swap(vetor *vec, int indexA, int indexB)
{
    if(!vec)
    {
        return -1;
    }

    if(indexA == indexB)
    {
        return 0;
    }

    const char *strA = vetor_elemento(vec, indexA);
    const char *strB = vetor_elemento(vec, indexB);
    if(!strA || !strB)
    {
        return -1;
    }

    char *tempA = malloc((strlen(strA)+1)*sizeof(*tempA));
    if(!tempA)
    {
        return -1;
    }

    strcpy(tempA, strA);
    if(vetor_atribui(vec, indexA, strB) == -1 || vetor_atribui(vec, indexB, tempA) == -1)
    {
        return -1;
    }

    free(tempA);

    return 0;
}

int vetor_ordena_sel(vetor* vec)
{
    if(!vec)
    {
        return -1;
    }

    for(int index = 0; index < vec->tamanho-1; ++index)
    {
        int minIndex = index;
        const char *minStr = vetor_elemento(vec, index);
        if(!minStr)
        {
            return -1;
        }

        for(int testIndex = index+1; testIndex < vec->tamanho; ++testIndex)
        {
            const char *testStr = vetor_elemento(vec, testIndex);
            if(!testStr)
            {
                return -1;
            }

            if(strcmp(testStr, minStr) < 0)
            {
                minIndex = testIndex;
                minStr = testStr;
            }
        }

        if(swap(vec, minIndex, index) == -1)
        {
            return -1;
        }
    }

	return 0;
}

int quicksortSlowPartition(vetor *vec, int low, int high)
{
    int size = high - low + 1;
    if(size < 2)
    {
        // NOTE(Gonçalo): Está feito
        return 0;
    }

#if 0
    // NOTE(Gonçalo): Semelhante ao algoritmo de Lomuto
    swap(vec, (rand() % size) + low, high); // NOTE(Gonçalo): Pivot está no índice high
    const char *pivot = vetor_elemento(vec, high);
    if(!pivot)
    {
        return -1;
    }

    int boundary = low, unknownStart = low;
    while(unknownStart < high)
    {
        const char *test = vetor_elemento(vec, unknownStart);
        if(!test)
        {
            return -1;
        }

        if(strcmp(test, pivot) <= 0)
        {
            if(swap(vec, boundary++, unknownStart++) == -1)
            {
                return -1;
            }
        }
        else
        {
            ++unknownStart;
        }
    }

    swap(vec, high, boundary);

    quicksortSlowPartition(vec, low, boundary-1);
    quicksortSlowPartition(vec, boundary+1, high);
#else
    // NOTE(Gonçalo): Semelhante ao algoritmo de Hoare
    int pivotPos = (rand() % size) + low;
    swap(vec, pivotPos, high);
    const char *pivot = vetor_elemento(vec, high);
    if(!pivot)
    {
        return -1;
    }

    int left = low, right = high-1;
    for(;;)
    {
        while(left < high && strcmp(vetor_elemento(vec, left), pivot) <= 0)
        {
            ++left;
        }
        while(right >= 0 && strcmp(vetor_elemento(vec, right), pivot) > 0)
        {
            --right;
        }

        if(left < right)
        {
            swap(vec, left, right);
        }
        else
        {
            break;
        }
    }
    swap(vec, left, high);

    quicksortSlowPartition(vec, low, left-1);
    quicksortSlowPartition(vec, left+1, high);
#endif

    return 0;
}

int vetor_ordena_qsort(vetor* vec)
{
    if(!vec)
    {
        return -1;
    }

	return quicksortSlowPartition(vec, 0, vec->tamanho-1);
}

int getPivot(vetor *vec, int low, int high)
{
    const char *lowStr = vetor_elemento(vec, low);
    const char *middleStr = vetor_elemento(vec, (low+high)/2);
    const char *highStr = vetor_elemento(vec, high);

    if(!lowStr || !middleStr || !highStr)
    {
        return -1;
    }

    int lowMiddle = strcmp(lowStr, middleStr);
    int middleHigh = strcmp(middleStr, highStr);
    int lowHigh = strcmp(lowStr, highStr);

    if((lowMiddle > 0 && lowHigh < 0) ||
       (lowMiddle < 0 && lowHigh > 0))
    {
        return low;
    }
    if((lowMiddle < 0 && middleHigh < 0) ||
       (lowMiddle > 0 && middleHigh > 0))
    {
        return (low+high)/2;
    }
    else
    {
        return high;
    }
}

int quicksortFastPartition(vetor *vec, int low, int high)
{
    int size = high - low + 1;
    if(size < 2)
    {
        // NOTE(Gonçalo): Está feito
        return 0;
    }

    int pivotPos = getPivot(vec, low, high);
    swap(vec, pivotPos, high);
    const char *pivot = vetor_elemento(vec, high);
    if(!pivot)
    {
        return -1;
    }

    int left = low, right = high-1;
    for(;;)
    {
        while(left < high && strcmp(vetor_elemento(vec, left), pivot) <= 0)
        {
            ++left;
        }
        while(right >= 0 && strcmp(vetor_elemento(vec, right), pivot) > 0)
        {
            --right;
        }

        if(left < right)
        {
            swap(vec, left, right);
        }
        else
        {
            break;
        }
    }
    swap(vec, left, high);

    quicksortSlowPartition(vec, low, left-1);
    quicksortSlowPartition(vec, left+1, high);

    return 0;
}

int vetor_ordena(vetor* vec)
{
    if(!vec)
    {
        return -1;
    }

	return quicksortFastPartition(vec, 0, vec->tamanho-1);
}

vetor* le_ficheiro(char* nome)
{
    FILE *file = fopen(nome, "r");
    if(!file)
    {
        return NULL;
    }

    vetor *result = vetor_novo();
    if(!result)
    {
        fclose(file);
        return NULL;
    }

    char buffer[1<<10];
    while(fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), file))
    {
        // NOTE(Gonçalo): Remover \n
        buffer[strlen(buffer)-1] = 0;
        if(vetor_insere(result, buffer, -1) == -1)
        {
            vetor_apaga(result);
            fclose(file);
            return NULL;
        }
    }

    return result;
}
