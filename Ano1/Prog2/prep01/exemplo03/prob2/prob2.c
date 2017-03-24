#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char nome[15];
    int vitorias;
} jogador;


/* problema 2 */
jogador* conta_vitorias(FILE* f, int *njogadores)
{
    if(!f || !njogadores)
    {
        return 0;
    }

    int n = 0;
    jogador *jogadores = 0;

    char nome[15];
    while(fscanf(f, "%14s", nome) == 1)
    {
        for(int i = 0; i <= n; ++i)
        {
            if(i == n)
            {
                jogador *temp = realloc(jogadores, sizeof(*jogadores)*(n+1));
                if(!temp)
                {
                    free(jogadores);
                    return 0;
                }
                jogadores = temp;
                strcpy(jogadores[i].nome, nome);
                jogadores[i].vitorias = 1;
                ++n;
                break;
            }
            else if(strcmp(jogadores[i].nome, nome) == 0)
            {
                ++jogadores[i].vitorias;
                break;
            }
        }
    }

    for(int i = 0; i < n-1; ++i)
    {
        int iMin = i;
        for(int j = i+1; j < n; ++j)
        {
            if(jogadores[j].vitorias < jogadores[iMin].vitorias)
            {
                iMin = j;
            }
        }
        if(iMin != i)
        {
            jogador temp = jogadores[i];
            jogadores[i] = jogadores[iMin];
            jogadores[iMin] = temp;
        }
    }

    *njogadores = n;
    return jogadores;
}

/***************************************************/
/*** não alterar o ficheiro a partir deste ponto ***/
/***************************************************/

int main()
{
    FILE * f = fopen("log.txt", "r");
    jogador *j;
    int i, n=0;

    j = conta_vitorias(f, &n);

    fprintf(stderr, "Vencedores:\n");
    if(j != NULL)
    {
        for(i=0; i<n; i++)
            fprintf(stderr, "%s - %d\n", j[i].nome, j[i].vitorias);
    }

    free(j);
    fclose(f);
    return 0;
}
