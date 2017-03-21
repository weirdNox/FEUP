/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2016/17          */
/*****************************************************************/


#include "vetor.h"
#include "vetorg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define TOL 1e-6

#define INICIA_TESTE() \
	int erros = 0;

#define ERRO(msg) \
	{ \
	printf("\n\t"#msg); \
		erros++; \
	}

#define FINALIZA_TESTE() \
	if (!erros) \
		printf("OK\n"); \
	else \
		printf("\n"); \
	return erros;

#define FICH1 "./plantas.txt"
#define FICH2 "./IMDB.txt"


int teste_le_ficheiro()
{
	INICIA_TESTE()

	printf("le_ficheiro(): ");

	vetor* v = le_ficheiro(FICH1);
	if(!v)
	{
		printf("\n\terro na leitura do ficheiro '%s'",FICH1);
		erros++;
		FINALIZA_TESTE();
	}

	if(v->tamanho != 77182)
		ERRO("o vetor resultante deveria ter tamanho 77182")

	vetor_apaga(v);

	FINALIZA_TESTE()
}

int teste_vetor_ordena_sel(vetor *v)
{
	clock_t inicio, fim;

	INICIA_TESTE()

	printf("vetor_ordena_sel(): ");

	inicio=clock();
	vetor_ordena_sel(v);
	fim=clock();


	if(strcmp(vetor_elemento(v,0), "Abelia x grandiflora (Andre) Rehder") != 0 ||
			strcmp(vetor_elemento(v,vetor_tamanho(v)-1), "Viburnum opulus L.") != 0)
		ERRO("elemento inicial e/ou final errado depois de ordenar");

	printf("\n\tTempo de execucao (s): %f\n",(double) (fim - inicio) / CLOCKS_PER_SEC);

	FINALIZA_TESTE()
}

int teste_vetor_ordena_qsort(vetor *v)
{
	clock_t inicio, fim;

	INICIA_TESTE()

	printf("vetor_ordena_qsort(): ");

	inicio=clock();
	vetor_ordena_qsort(v);
	fim=clock();


	if(strcmp(vetor_elemento(v,0), "Abelia x grandiflora (Andre) Rehder") != 0 ||
			strcmp(vetor_elemento(v,vetor_tamanho(v)-1), "Viburnum opulus L.") != 0)
		ERRO("elemento inicial e/ou final errado depois de ordenar");

	printf("\n\tTempo de execucao (s): %f\n",(double) (fim - inicio) / CLOCKS_PER_SEC);

	FINALIZA_TESTE()
}


int teste_vetor_ordena(vetor *v)
{
	clock_t inicio, fim;

	INICIA_TESTE()

	printf("vetor_ordena(): ");

	inicio=clock();
	vetor_ordena(v);
	fim=clock();


	if(strcmp(vetor_elemento(v,0), "Abelia x grandiflora (Andre) Rehder") != 0 ||
			strcmp(vetor_elemento(v,vetor_tamanho(v)-1), "Viburnum opulus L.") != 0)
		ERRO("elemento inicial e/ou final errado depois de ordenar");

	printf("\n\tTempo de execucao (s): %f\n",(double) (fim - inicio) / CLOCKS_PER_SEC);

	FINALIZA_TESTE()
}

int teste_vetorg_insere()
{
	INICIA_TESTE()

	printf("vetorg_insere(): ");

	vetorg* vg = vetorg_novo();

	int i = 0;
	i = vetorg_insere(vg, 121881, 8.4,  2012, "Django Unchained", -1);
	i+= vetorg_insere(vg, 121881, 8.4,  2012, "Django Unchained", vg->tamanho);

	if(i!=1){
		printf("\n\terro na inserção no vetor genérico\n");
		erros++;
		FINALIZA_TESTE();
	}

	vetorg_apaga(vg);

	FINALIZA_TESTE()
}

int teste_le_ficheiro_g()
{
	INICIA_TESTE()

	printf("le_ficheiro_g(): ");

	vetorg* vg = le_ficheiro_g(FICH2);
	if(!vg)
	{
		printf("\n\terro na leitura do ficheiro '%s'",FICH2);
		erros++;
		FINALIZA_TESTE();
	}

	if(vg->tamanho != 100000)
		ERRO("o vetor generico resultante deveria ter tamanho 100000")

	vetorg_apaga(vg);

	FINALIZA_TESTE()
}

int teste_vetorg_ordena(vetorg *vg)
{
	clock_t inicio, fim;

	INICIA_TESTE()

	printf("vetorg_ordena() (por título): ");

	inicio=clock();
	vetorg_ordena(vg, comp_titulo_asc);
	fim=clock();

	if(strcmp(vg->elementos[0].titulo, "12 Angry Men") != 0 ||
			strcmp(vg->elementos[vg->tamanho-1].titulo, "Yojinbo") != 0)
		ERRO("elemento inicial e/ou final errado depois de ordenar por titulo");

	printf("\n\tTempo de execucao (s): %f\n",(double) (fim - inicio) / CLOCKS_PER_SEC);

	FINALIZA_TESTE()
}


int main()
{
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	int erros = 0, erros_prev;
	vetor *v=NULL;
	vetorg *vg=NULL;
	printf("TESTES VETOR.\n");
	erros += teste_le_ficheiro();
	if (erros==0) {
		v = le_ficheiro(FICH1);
		erros += teste_vetor_ordena_sel(v);
		vetor_apaga(v);
		v = le_ficheiro(FICH1);
		erros += teste_vetor_ordena_qsort(v);
		vetor_apaga(v);
		v = le_ficheiro(FICH1);
		erros += teste_vetor_ordena(v);
		vetor_apaga(v);
	}
	printf("FIM DE TESTES VETOR.\n");
	printf("\nTESTES VETOR GENERICO.\n");
	erros += teste_vetorg_insere();
	erros_prev=erros;
	erros += teste_le_ficheiro_g();
	if (erros==erros_prev) {
		vg = le_ficheiro_g(FICH2);
		erros += teste_vetorg_ordena(vg);
		vetorg_apaga(vg);
	}
	printf("FIM DE TESTES VETOR GENERICO.\n");
	if (!erros)
		printf("FIM DE TODOS OS TESTES.\n");
	else
		printf("FOI ENCONTRADO UM TOTAL DE %d ERROS.\n", erros);
	return 0;
}
