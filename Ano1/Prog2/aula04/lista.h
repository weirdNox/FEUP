/*****************************************************************/
/*      Biblioteca lista ligada | PROG2 | MIEEC | 2016/17        */
/*****************************************************************/


#ifndef LISTA_H

/**
* registo para armazenar elementos da lista duplamente ligada
* este registo contem uma string e apontadores para o proximo e
* anterior elementos da lista
*/
typedef struct _l_elemento
{
	/* string armazenada */
	char* str;
	/* apontadores para elementos vizinhos */
    struct _l_elemento *proximo;
    struct _l_elemento *anterior;
} l_elemento;

typedef struct
{
	l_elemento *inicio;
	l_elemento *fim;
	int tamanho;
} lista;

#define LISTA_INICIO 0
#define LISTA_FIM 1

/**
 *  cria uma nova lista ligada vazia
 *  retorno: apontador para a lista
 *  observacao: se a lista não foi criada retorna NULL
 */
lista* lista_nova();

/**
 *  elimina uma lista, libertando toda a memoria ocupada
 *  parametro: lst apontador para a lista
 *  observacao: se lista = NULL retorna sem fazer nada
 */
void lista_apaga(lista *lst);

/**
 *  indica o comprimento da lista
 *  parametro: lst apontador para a lista
 *  retorno: numero de elementos da lista ou -1 se lista = NULL
 */
int lista_tamanho(lista *lst);

/**
 *  devolve o apontador para o primeiro elemento da lista
 *  parametro: lst apontador para a lista
 *  retorno: apontador para o primeiro elemento da lista ou NULL se lista = NULL
 */
l_elemento* lista_inicio(lista *lst);

/**
 *  devolve o apontador para o ultimo elemento da lista
 *  parametro: lst apontador para a lista
 *  retorno: apontador para o ultimo elemento da lista ou NULL se lista = NULL
 */
l_elemento* lista_fim(lista *lst);

/**
*  retorna o elemento armazenado na posicao especificada
*  parametro: lst apontador para lista ligada
*  parametro: pos indice do elemento
*  retorno: apontador para a string na posicao correspondente
*  nota: se ocorrer algum erro retorna NULL (p.ex. se valor pos indicar uma posicao invalida)
*/
l_elemento* lista_elemento(lista *lst, int pos);

/**
 *  insere um elemento na posicao especificada
 *  parametro: lst apontador para a lista
 *  parametro: valor string a inserir
 *  parametro: pos posicao da lista onde se pretende inserir o novo elemento,
 *             se pos=NULL insere no fim da lista
 *  retorno: apontador para novo elemento inserido na lista ou NULL se ocorrer um erro
 */
l_elemento* lista_insere(lista *lst, const char* valor, l_elemento *pos);

/**
 *  remove o elemento especificado
 *  parametro: lst apontador para a lista
 *  parametro: pos elemento que se pretende remover
 *  retorno: apontador para proximo elemento ao que foi removido ou NULL se ocorrer um erro
 */
l_elemento* lista_remove(lista *lst, l_elemento *pos);

/**
*  atribui o valor especificado a um elemento da lista
*  parametro: lst apontador para a lista
*  parametro: pos elemento onde colocar valor
*  parametro: str string pretendida
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou pos se bem sucedido
*/
int lista_atribui(lista *lst, l_elemento *pos, const char* str);

/**
 *  devolve a posicao do primeiro elemento da lista com a string especificada
 *  parametro: lst apontador para a lista
 *  parametro: str string a pesquisar
 *  parametro: origem origem da pesquisa: a partir do início (LISTA_INICIO) ou a partir do fim (LISTA_FIM)
 *  retorno: elemento ou NULL se nao encontrar elemento ou ocorrer um erro
 */
l_elemento* lista_pesquisa(lista *lst, const char* str, int origem);

/**
 *  ordena uma lista por ordem alfabetica
 *  parametro: lst apontador para a lista
 *  retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
 */
int lista_ordena(lista *lst);


#define LISTA_H
#endif
