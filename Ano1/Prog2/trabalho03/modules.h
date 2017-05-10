/*****************************************************************/
/*         Trabalho pratico 3 | PROG2 | MIEEC | 2016/17          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#ifndef MODULES_H
#define MODULES_H

/* Serve para realizar as inicializacoes necessarias e e' invocada no
   início da sessao. O parametro maxTransactions e' o numero maximo de
   transacoes que terao de ser processadas na sessao.
   */
void median_initModule(int maxTransactions);

/* Invocada sempre que ocorre uma nova transacao. O parametro numActions
   e' o numero de acoes transacionadas na nova transacao e o parametro
   updatedMedian devolve a mediana atualizada.
   A funcao retorna -1 em caso de erro e 1 em caso de funcionamento normal.
   */
int median_newObservation(int numActions, float *updatedMedian);

/* Invocada no fim da sessao e serve para libertar toda a memoria
   alocada previamente.
   */
void median_closeModule();


/* Serve para realizar as inicializacoes necessarias e e' invocada no
   início da sessao. O parametro maxTransactions e' o numero maximo de
   transacoes que terao de ser processadas na sessao.
   */
void mode_initModule(int maxTransactions);

/* Invocada sempre que ocorre uma nova transacao. O parametro companyName
   e' o nome da empresa cujas  acoes foram transacionadas na nova transacao
   e o parametro updatedMode recebe a moda atualizada (nome da empresa mais
   vezes transacionada ate' ao momento). Se houver mais do que uma moda a
   funcao deve retornar o nome da primeira empresa a atingir esse valor.
   A funcao retorna -1 em caso de erro e 1 em caso de funcionamento normal
   */
int mode_newObservation(const char *companyName, char *updatedMode);

/* Invocada no fim da sessao e serve para libertar toda a memoria
   alocada previamente.
   */
void mode_closeModule();

#endif
