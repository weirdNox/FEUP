#include <stdio.h>
#include <stdlib.h>
#include "avl.c"

void imprimirFiltro(no_avl *no)
{
    if(!no)
    {
        return;
    }

    if(atoi(no->str) < 15000)
    {
        printf("%s\n", no->str);
        imprimirFiltro(no->esquerda);
        imprimirFiltro(no->direita);
    }
    else
    {
        imprimirFiltro(no->esquerda);
    }
}

int imprimirMaxMinLeituras(const char *nomeFicheiro)
{
    FILE *f = fopen(nomeFicheiro, "r");
    if(!f)
    {
        return 0;
    }

    arvore_avl *avl = avl_nova();
    if(!avl)
    {
        fclose(f);
        return 0;
    }

    char buff[50];
    while(fscanf(f, "%s", buff) == 1)
    {
        avl_insere(avl, buff);
    }
    printf("Mínimo: %s\nMáximo: %s\n", avl_min(avl),
           avl_max(avl));

    imprimirFiltro(avl->raiz);

    avl_apaga(avl);
    fclose(f);

    return 1;
}


/*----------------------------------*/
/*    nao alterar a funcao main     */

int main()
{
	if(imprimirMaxMinLeituras("leituras.txt") == 0)
	{
		printf("Erro ao executar funcao.\n");
		return 1;
	}

	return 0;
}
