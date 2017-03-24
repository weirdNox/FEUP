#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char palavra[100];
    int ocorrencias;
} registo;

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** exercicio 2.1 ***/
registo *analisarFicheiro(FILE *ficheiro, int *num_palavras)
{
    if(!ficheiro || !num_palavras)
    {
        return 0;
    }

    registo *result = 0;
    char word[100];
    int n = 0;
    while(fscanf(ficheiro, "%99s", word) == 1)
    {
        for(int i = 0; i <= n; ++i)
        {
            if(i == n)
            {
                registo *temp = realloc(result, sizeof(*result)*(n+1));
                if(!temp)
                {
                    free(result);
                    return 0;
                }
                result = temp;
                strcpy(result[n].palavra, word);
                result[n].ocorrencias = 1;
                ++n;
                break;
            }
            else if(strcmp(result[i].palavra, word) == 0)
            {
                ++result[i].ocorrencias;
                break;
            }
        }
    }

    *num_palavras = n;
    return result;
}

/*** exercicio 2.2 ***/
void gerarRelatorio(FILE *ficheiro, registo *resultados, int num_palavras)
{
    if(!ficheiro || !resultados)
    {
        return;
    }

    fprintf(ficheiro, "Palavras encontradas:\n-----------------------\n");
    for(int i = 0; i < num_palavras; ++i)
    {
        registo *current = resultados + i;
        fprintf(ficheiro, "%d:\t%s (%d)\n", i+1, current->palavra, current->ocorrencias);
    }
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main() {
    FILE *fin, *fout;
    char nomeIn[50], nomeOut[50];
    registo *resultados;
    int n;

    printf("Ficheiro de entrada? ");
    scanf("%s", nomeIn);
    printf("Ficheiro de saida? ");
    scanf("%s", nomeOut);

    fin = fopen(nomeIn, "r");
    if (fin == NULL)
        return 1;

    fout = fopen(nomeOut, "w");
    if (fout == NULL)
        return 1;

    resultados = analisarFicheiro(fin, &n);
    gerarRelatorio(fout, resultados, n);

    fclose(fin);
    fclose(fout);
    free(resultados);

    return 0;
}
