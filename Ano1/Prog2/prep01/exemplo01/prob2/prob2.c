#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char nome[100];
	int pop2001;
	int pop2012;
}
municipio;

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
municipio *lerFicheiro(FILE *ficheiro, int *num_municipios)
{
    if(!ficheiro)
    {
        return 0;
    }

    municipio *result = 0;

    char buffer[1<<13];
    while(fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), ficheiro))
    {
        ++(*num_municipios);
        municipio *test = realloc(result, sizeof(*result)*(*num_municipios));
        if(!test)
        {
            free(result);
            return 0;
        }
        result = test;

        municipio *atual = result + (*num_municipios)-1;
        char *token = strtok(buffer, "\t");
        strncpy(atual->nome, token, 100);
        token = strtok(0, "\t");
        atual->pop2001 = atoi(token);
        token = strtok(0, "\t");
        atual->pop2012 = atoi(token);
    }

	return result;
}

/*** problema 2.2 ***/
void gerarRelatorio(FILE *ficheiro, municipio *resultados, int num_municipios)
{
    if(!ficheiro)
    {
        return;
    }

    for(int i = 0; i < 10; ++i)
    {
        int maxIdx = i;
        int maxPerdida = resultados[i].pop2001 - resultados[i].pop2012;
        for(int j = i+1; j < num_municipios; ++j)
        {
            int testePerdida = resultados[j].pop2001 - resultados[j].pop2012;
            if(testePerdida > maxPerdida)
            {
                maxIdx = j;
                maxPerdida = testePerdida;
            }
        }
        if(maxIdx != i)
        {
            municipio temp = resultados[i];
            resultados[i] = resultados[maxIdx];
            resultados[maxIdx] = temp;
        }
        fprintf(ficheiro, "%s, %d\n", resultados[i].nome, maxPerdida);
    }
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
	FILE *fin, *fout;
	municipio *resultados;
	int n;

	fin = fopen("municipios.txt", "r");
	if(fin == NULL)
		return 1;

	fout = fopen("relatorio.txt", "w");
	if(fout == NULL)
		return 1;

	resultados = lerFicheiro(fin, &n);
	gerarRelatorio(fout, resultados, n);

	fclose(fin);
	fclose(fout);
	free(resultados);

	return 0;
}
