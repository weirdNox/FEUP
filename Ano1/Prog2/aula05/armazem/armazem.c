#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
    armazem *result = malloc(sizeof(*result));
    if(result)
    {
        result->comprimento = comprimento;
        result->altura = altura;
        result->contentores = fila_nova();
    }

    return result;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
	return (fila_tamanho(armz->contentores) == 0);
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
    if(fila_tamanho(armz->contentores) == armz->comprimento)
    {
        pilha *last = fila_back(armz->contentores);
        if(last->tamanho == armz->altura)
        {
            return 1;
        }
    }
	return 0;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
    pilha *atual = fila_back(armz->contentores);
    if(!atual || (atual->tamanho >= armz->altura && fila_tamanho(armz->contentores) < armz->comprimento))
    {
        atual = pilha_nova();
        fila_push(armz->contentores, atual);
    }

    if(atual->tamanho < armz->altura)
    {
        pilha_push(atual, contr);
        return 1;
    }

	return 0;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
    pilha *atual = fila_front(armz->contentores);
    if(!atual)
    {
        return 0;
    }

    contentor *topo = pilha_top(atual);
    contentor *novo = contentor_novo(topo->destino, topo->valor);
    pilha_pop(atual);
    if(pilha_tamanho(atual) == 0)
    {
        fila_pop(armz->contentores);
    }
    return novo;
}
