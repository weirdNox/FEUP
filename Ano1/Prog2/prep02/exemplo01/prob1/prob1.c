#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.c"
#include "heap.c"
#include "fila.c"
#include "vetor.c"

/*** problema 1.1 ***/
int avl_conta_letras(no_avl *no)
{
    if(!no)
    {
        return 0;
    }

    int result = 0;
    int length = strlen(no->str);
    for(int i = 0; i < length; ++i)
    {
        if(no->str[i] >= 'a' && no->str[i] <= 'z')
        {
            ++result;
        }
    }

    result += avl_conta_letras(no->esquerda);
    result += avl_conta_letras(no->direita);

	return result;
}

/*** problema 1.2 ***/
int fila_reordena(fila *original, vetor *prioridades)
{
	/* complexidade do algoritmo: O(nlog(n))
     * O loop com maior complexidade é o que percorre os elementos todos e insere na heap
     */

    if(!original || !prioridades || fila_tamanho(original) != prioridades->tamanho)
    {
        return 0;
    }

    heap *priorityQueue = heap_nova(prioridades->tamanho);
    if(!priorityQueue)
    {
        return 0;
    }

    filaItem *item = original->cabeca;
    for(int i = 0;
        item;
        ++i, item = item->proximo)
    {
        int priority;
        sscanf(prioridades->elementos[i].str, "%d", &priority);
        if(!heap_insere(priorityQueue, item->string, -priority))
        {
            heap_apaga(priorityQueue);
            return 0;
        }
        fila_pop(original);
    }

    while(priorityQueue->tamanho)
    {
        char *str = heap_remove(priorityQueue);
        if(fila_push(original, str) == -1)
        {
            heap_apaga(priorityQueue);
            return 0;
        }
        free(str);
    }

    heap_apaga(priorityQueue);
	return 1;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	FILE *fm=fopen("estrelas.txt", "r");
	char str_aux[MAX_STR];

	/* teste problema 1.1 */
	{
		arvore_avl *arv;
		puts("* Problema 1.1 *");
		arv = avl_nova();
		while(fgets(str_aux,MAX_STR,fp) != NULL)
		{
			str_aux[strlen(str_aux)-1] = '\0';
			avl_insere(arv, str_aux);
		}
		printf("Numero de letras: %d\n", avl_conta_letras(arv->raiz));
		avl_apaga(arv);
	}

	/* teste problema 1.2 */
	{
		fila *f;
		vetor *p;
		int i, tam, res;
		char val[MAX_STR];
		puts("\n\n* Problema 1.2 *");
		f=fila_nova();
		p=vetor_novo();
		while(fscanf(fm, "%s %s", str_aux, val) == 2)
		{
			fila_push(f, str_aux);
			vetor_insere(p, val, p->tamanho);
		}
		res = fila_reordena(f, p);
		tam = fila_tamanho(f);
		for(i=0; i<3 && tam>0; i++)
		{
			printf("%s\n", fila_front(f));
			fila_pop(f);
		}
		for(i=3; i<tam-2; i++)
			fila_pop(f);
		puts("...");
		for(i=tam-2; i<tam; i++)
		{
			printf("%s\n", fila_front(f));
			fila_pop(f);
		}
		fila_apaga(f);
		vetor_apaga(p);
	}

	fclose(fp);
	fclose(fm);
	return 0;
}
