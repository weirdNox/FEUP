/*****************************************************************/
/*         Trabalho pratico 3 | PROG2 | MIEEC | 2016/17          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "modules.h"
#define TIMEOUT 2

int main()
{
	int obser;
	float median = 0, medianref = -1;
	char company[16] = "", mode[16] = "", companyref[16] = "";
	int nerrors = 0;

	srand((int)time(NULL));

	/* PHASE 1: CHECK CORRECTNESS */
	FILE *fin = fopen("data.txt", "r");
	FILE *fout = fopen("results.txt", "r");
	if (!fin || !fout)
	{
		printf("erro ao abrir ficheiro\n");
		return -1;
	}

	median_initModule(100000);
	mode_initModule(100000);
	while (!feof(fin))
	{
		fscanf(fin, "%d;", &obser);
		fgets(company,sizeof(company), fin);
		if (strchr(company, '\r') != NULL)
			*strchr(company, '\r')=0;
		if (strchr(company, '\n') != NULL)
			*strchr(company, '\n')=0;

		fscanf(fout, "%f;", &medianref);
		fgets(companyref,sizeof(companyref), fout);
		if (strchr(companyref, '\r') != NULL)
			*strchr(companyref, '\r')=0;
		if (strchr(companyref, '\n') != NULL)
			*strchr(companyref, '\n')=0;

		median_newObservation(obser, &median);
		mode_newObservation(company, mode);

		if ((median!=medianref))
			{nerrors++; break;}
		if ((strcmp(mode, companyref)!=0))
			{nerrors++; break;}
	}
	median_closeModule();
	mode_closeModule();
	fclose(fin);
	fclose(fout);
	if (nerrors)
	{
		printf("ERROS no calculo da mediana ou moda\n");
		return -1;
	}
	else
		printf("OK no calculo da mediana e moda\n");

	/* PHASE 2: CHECK EFFICIENCY Median Module */
	clock_t inicio, fim;
    double tempo;
	int score;
	int cap = 10000000;

	median_initModule(cap);
	score = 0;
	inicio = clock();
 	while(1)
	{
		obser = rand()%(cap/100);
		median_newObservation(obser, &median);
		fim = clock();
		tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
		if (tempo>TIMEOUT)
			break;
		score++;
		if (score>=cap)
			break;
	}
	median_closeModule();
	printf ("Median SCORE %d\n", score);

	/* PHASE 3: CHECK EFFICIENCY Mode Module */
	char modeCompany[16];
	char name[16];

	mode_initModule(cap);
	score = 0;
	inicio = clock();
 	while(1)
	{
		obser = rand()%(cap/100);
		sprintf(name, "%d", obser);
		mode_newObservation(name, modeCompany);
		fim = clock();
		tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
		if (tempo>TIMEOUT)
			break;
		score++;
		if (score>=cap)
			break;
	}
	mode_closeModule();
	printf ("Mode SCORE %d\n", score);
}
