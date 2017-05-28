#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.c"

int topSubmissoes(FILE *f)
{
    if(!f)
    {
        return 0;
    }

    heap *h = heap_cria(100);
    if(!h)
    {
        return 0;
    }

    char buff[15];
    int min, seg;
    while(fscanf(f, "%s %d %d", buff, &min, &seg) == 3)
    {
        heap_insere(h, buff, 60*min+seg);
    }

    puts("Top 5 submissões:");
    for(int i = 0; i < 5; ++i)
    {
        int tempo = h->elementos[0]->prioridade;
        char *g = heap_remove(h);
        printf("Grupo %s - %dmin %dseg\n", g, tempo/60, tempo%60);
        free(g);
    }

    heap_apaga(h);

	return 1;
}


/* v-- nao alterar funcao main --v */

int main()
{
	FILE *f;

	f = fopen("submissoes.txt", "r");

	if(topSubmissoes(f) == 0)
	{
		puts("Erro ao executar funcao.\n");
		fclose(f);
		return 1;
	}

	fclose(f);
	return 0;
}
