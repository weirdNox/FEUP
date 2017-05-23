/*****************************************************************/
/*       Tabela de Dispersao | PROG2 | MIEEC | 2016/17           */
/*****************************************************************/

#ifndef TABDISPERSAO_H
#define TABDISPERSAO_H

#define TABDISPERSAO_EXISTE     (1)
#define TABDISPERSAO_OK   		(0)
#define TABDISPERSAO_INVALIDA   (-1)
#define TABDISPERSAO_ERRO       (-2)
#define TABDISPERSAO_NAOEXISTE  (-3)

#define TAMANHO_CHAVE	 25
#define TAMANHO_VALOR	100

/* tabela de dispersao de strings baseada em encadeamento */

typedef unsigned long hash_func(const char *, int);

/** conteudo individual da tabela de dispersao:
 * cada objeto tem uma chave e um texto associado
 */
typedef struct
{
	char chave[TAMANHO_CHAVE];
	char valor[TAMANHO_VALOR];
} objeto;

/** elemento da tabela de dispersao */
typedef struct elem
{
	objeto* obj;
	struct elem * proximo;
} td_elemento;

/**
 * A estrutura tabela_dispersao para armazenar dados relativos a uma tabela de dispersao
 */
struct tab_dispersao
{
	hash_func *hfunc;		/* apontador para a funcao a ser usada (hash_djbm, hash_krm, ...) */
	td_elemento **elementos;	/* vetor de elementos */
	int tamanho;			/* tamanho do vetor de elementos */
};

 typedef struct tab_dispersao tabela_dispersao;

/**
 * cria uma tabela de dispersao
 * parametro: tamanho tamanho da tabela de dispersao
 * parametro: hash_func apontador para funcao de dispersao a ser usada nesta tabela
 * retorno: uma tabela de dispersao vazia que usa a funcao de dispersao escolhida
 */
tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc);

/**
 * elimina uma tabela, libertando toda a memoria ocupada
 * parametro: td tabela de dispersao a ser apagada da memoria
 * observacao: apagar _todos_ os elementos anteriormente alocados na memoria
 */
void tabela_apaga(tabela_dispersao *td);

/**
 * adiciona um novo objeto 'a tabela; se a chave ja' existir atualiza o texto associado com o novo texto
 * parametro: td tabela onde adicionar o objeto
 * parametro: valor objeto a ser adicionado
 * retorno: se o valor for adicionado correctamente, a funcao retorna TABDISPERSAO_OK
 * retorno: caso contrario deve devolver TABDISPERSAO_ERRO ou TABDISPERSAO_INVALIDA
 * observacao: valor deve ser copiado para outro local em memoria.
 */
int tabela_insere(tabela_dispersao *td, const char *chave, const char *valor);

/**
 * remove um valor da tabela
 * parametro: td tabela de onde remover o valor
 * parametro: chave chave do objeto a ser removido da tabela
 * retorno: TABDISPERSAO_NAOEXISTE se o valor passado como argumento nao existir na tabela
 * retorno: ou TABDISPERSAO_OK se o valor foi removido correctamente
 * retorno: ou TABDISPERSAO_INVALIDA se a tabela não existe
 */
int tabela_remove(tabela_dispersao *td, const char *chave);

/**
 * verifica se um valor existe na tabela
 * parametro: td tabela onde procurar o valor
 * parametro: valor objeto a ser procurado
 * retorno: TABDISPERSAO_NAOEXISTE se o valor nao existir
 * retorno: ou TABDISPERSAO_EXISTE se o valor existir
 * retorno: ou TABDISPERSAO_INVALIDA se a tabela não existe
 */
int tabela_existe(tabela_dispersao *td, const char *chave);

/**
 * devolve o valor correspondente 'a chave
 * parametro: td tabela onde procurar o objeto
 * parametro: chave chave do objeto a ser procurado
 * retorno: apontador para a string valor se existir, ou NULL se nao existir objeto ou tabela
 */
const char* tabela_valor(tabela_dispersao *td, const char *chave);

/**
 * apaga todos os valores correntemente na tabela, ficando a tabela vazia
 * parametro: td tabela a ser esvaziada
 * retorno: TABDISPERSAO_OK ou TABDISPERSAO_INVALIDA de acordo com o resultado
 */
int tabela_esvazia(tabela_dispersao *td);

/**
 * determina o numero de elementos na tabela de dispersao
 * parametro: td tabela de dispersao
 * retorno: numero de elementos na tabela
 * retorno: ou TABDISPERSAO_NAOEXISTE se a tabela não existe
 */
int tabela_numelementos(tabela_dispersao *td);

/**
 * devolve um vetor com os elementos da tabela de dispersao
 * parametro: td tabela de dispersao
 * retorno: vetor com os objetos da tabela ou NULL se nao existir tabela ou tabela vazia
 */
objeto* tabela_elementos(tabela_dispersao *td, int *n);

/**
 * calcula hash com base na seguinte formula:
 *            hash(i) = hash(i-1) + chave[i]
 *    em que hash(0) = 7
 *
 * parametro: chave string para a qual se pretende calcular o chave de hash
 * parametro: tamanho da tabela de dispersão
 * observacao: chave[i] e' o caracter no indice de i da chave
 */
unsigned long hash_krm(const char* chave, int tamanho);

/**
 * calcula hash com base na seguinte formula:
 *            hash(i) = hash(i-1)* 31 (+) chave[i]
 *        em que hash(0) = 5347
 *
 * parametro: chave string para o qual se pretende calcular o chave de hash
 * parametro: tamanho da tabela de dispersão
 * observacao: chave[i] e' o caracter no indice de i da chave
 * observacao: (+) representa "ou exclusivo" que em C e' indicado por ^
 */
unsigned long hash_djbm(const char *chave, int tamanho);

/**
 * Esta funcao imprime o estado actual da tabela para o ecra
 * parametro: td Tabela a ser mostrada no ecra
 */
void mostraTabela(tabela_dispersao *td);

#endif
