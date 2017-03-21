/*****************************************************************/
/*          Biblioteca vetorg | PROG2 | MIEEC | 2016/17           */
/*****************************************************************/

#ifndef VETORG_H


/**
* registo para armazenar cada elemento (apenas uma string neste caso)
*/
typedef struct
{
  int votos;
  float classifica;
  char* titulo;
  int ano;
} vg_elemento;

/**
* este registo contem um vetorg de elementos, um contador do tamanho e outro para a capacidade
*/
typedef struct
{
  /** numero de elementos do vetorg */
  int tamanho;

  /** capacidade do vetorg */
  int capacidade;

  /** array de elementos armazenados */
  vg_elemento* elementos;

} vetorg;

/**
* tipo "comp" representa um apontador para uma função de ordem.
* uma função que implemente esta assinatura deverá retornar:
*  -1 se a < b
*  0 se a == b
*  1 se a > b
*/

typedef int (*comp)(const vg_elemento a, const vg_elemento b);

/**
*  cria um novo vetorg com tamanho 0 e capacidade 0
*  retorno: apontador para o vetorg criado
*  nota: se vetorg nao foi criado retorna NULL
*/
vetorg* vetorg_novo();

/**
*  elimina um vetorg, libertando toda a memoria ocupada
*  parametro: vec apontador para vetorg
*  nota: se vec = NULL retorna sem fazer nada
*/
void vetorg_apaga(vetorg *vec);

/**
*  indica o o numero de elementos do vetorg
*  parametro: vec apontador para vetorg
*  retorno: -1 se ocorrer algum erro ou numero de elementos do vetorg
*/
int vetorg_tamanho(vetorg *vec);

/**
*  insere um elemento na posicao especificada
*  parametro: vec apontador para vetorg
*  parametro: valor int a inserir
*  parametro: valor float a inserir
*  parametro: valor int a inserir
*  parametro: valor string a inserir
*  parametro: pos indice do elemento onde se pretende inserir a string, se pos=tamanho ou pos=-1 insere no fim do vetorg
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou o valor de pos se bem sucedido
*  nota: se a capacidade nao for suficiente para guardar novo elemento, devera ser aumentada para 2x em relacao a capacidade anterior; inicialmente aumenta para capacidade 1
*/
int vetorg_insere(vetorg *vec, int votos, float classifica, int ano, const char* titulo, int pos);

/**
*  ordena um vetorg por ordem alfabetica
*  parametro: vec apontador para vetorg
*  retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
*/
int vetorg_ordena(vetorg *vec, comp ordem);

/**
*  le o conteudo do ficheiro de texto com nome para um vetorg
*  parametro: nome do ficheiro de texto
*  retorno: NULL se ocorrer um erro ou apontador para vetor se bem sucedido
*/
vetorg *le_ficheiro_g(char* nome);


/* comparação do campo votos de forma ascendente */
int comp_votos_asc(const vg_elemento a, const vg_elemento b);

/* comparação do campo classifica de forma ascendente */
int comp_classifica_asc(const vg_elemento a, const vg_elemento b);

/* comparação do campo ano de forma ascendente */
int comp_ano_asc(const vg_elemento a, const vg_elemento b);

/* comparação do campo título de forma ascendente */
int comp_titulo_asc(const vg_elemento a, const vg_elemento b);


#define VETORG_H
#endif
