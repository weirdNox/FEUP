#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.c"
#include "grafo.c"
#include "heap.c"

int proximas_n_chegadas(lista *tempos, lista *origens, lista *aeroportos, int n)
{
    if(!tempos || !origens || !aeroportos || n < 0 || tempos->tamanho != origens->tamanho)
    {
        return 0;
    }

    heap *h = heap_nova(tempos->tamanho);
    if(!h)
    {
        return 0;
    }

    for(l_elemento *t = tempos->inicio, *o = origens->inicio;
        t && o;
        t = t->proximo, o = o->proximo)
    {
        int prioridade = atoi(t->str);
        int indiceNome = atoi(o->str);
        l_elemento *nome = lista_elemento(aeroportos, indiceNome);
        if(!nome || !heap_insere(h, nome->str, prioridade))
        {
            heap_apaga(h);
            return 0;
        }
    }

    for(int i = 0; i < n; ++i)
    {
        char *str = heap_remove(h);
        printf("%d: %s\n", i+1, str);
        free(str);
    }

    heap_apaga(h);

    return 1;
}

lista* pesquisa_destinos (grafo *rotas, lista *aeroportos, const char *origem)
{
    if(!rotas || !aeroportos || !origem || rotas->tamanho != aeroportos->tamanho)
    {
        return 0;
    }

    lista *resultado = lista_nova();
    if(!resultado)
    {
        return 0;
    }

    int indiceOrig = 0;
    l_elemento *orig = aeroportos->inicio;
    while(orig)
    {
        if(strcmp(orig->str, origem) == 0)
        {
            break;
        }
        orig = orig->proximo;
        ++indiceOrig;
    }
    if(!orig)
    {
        lista_apaga(resultado);
        return 0;
    }

    lista_no *voo = rotas->adjacencias[indiceOrig].inicio;
    while(voo)
    {
        char *nome = lista_elemento(aeroportos, voo->vertice)->str;
        if(!lista_insere(resultado, nome, 0))
        {
            lista_apaga(resultado);
            return 0;
        }

        voo = voo->proximo;
    }

    lista_ordena(resultado);

	return resultado;
}

/* Aqui começa o código de teste. Não modificar! */

grafo* carrega_rotas (lista *aeroportos, const char *filename)
{
	if(!filename) return NULL;
	grafo* g=NULL;
	FILE *f;
	int origem, destino;
	f = fopen(filename, "r");
	if (!f) {
		printf("Erro na leitura do ficheiro: %s\n",filename);
		return NULL;
	}
	g = grafo_novo(lista_tamanho(aeroportos), NAODIRECIONADO);
	if (!g) {
			printf("Erro na criacao do grafo\n");
			return NULL;
	}
	while(fscanf(f, "%d\t%d", &origem, &destino) == 2) {
		grafo_adiciona(g, origem, destino);
	}
	fclose(f);
	return g;
}

int main()
{
	FILE *f;
	grafo *g=NULL;
	lista *aeroportos;
	char* buff;
	size_t n;

	setvbuf(stdout, NULL, _IONBF, 0);
	f = fopen("aeroportos.txt", "r");
	aeroportos = lista_nova();
	buff=NULL;
	n=0;
	while(getline(&buff,&n,f)!=-1) {
		buff[strlen(buff)-1]='\0';
		lista_insere(aeroportos,buff,NULL);
	}
	free(buff);
	fclose(f);

	g = carrega_rotas(aeroportos, "rotas.txt");

	/* teste problema 2.1 */
	{
		FILE *f;
		char tempo[5], origem[10];
		lista *tempos, *origens;

		printf("* Problema 2.1 *\n");

		f = fopen("chegadas.txt", "r");
		tempos = lista_nova();
		origens = lista_nova();

		while(fscanf(f, "%s\t%s", tempo, origem) == 2) {
			lista_insere(tempos, tempo, NULL);
			lista_insere(origens, origem, NULL);
		}

		if(proximas_n_chegadas(tempos, origens, aeroportos, 5) != 1)
    		printf("Erro ao executar a funcao\n");

    	lista_apaga(tempos);
    	lista_apaga(origens);
    	fclose(f);
	}

	/* teste problema 2.2 */
	{
		printf("\n* Problema 2.2 *\n");
		const char *origem = "Lille (FR)";
		l_elemento *elem;
		lista *l = pesquisa_destinos(g,aeroportos, origem);
		if(l == NULL)
			printf("Destinos diretos a partir de %s = 0\n", origem);
		else
		{
			printf("Destinos diretos a partir de %s = %d\n",
									origem, lista_tamanho(l));
			for(elem=l->inicio;elem!=NULL;elem=elem->proximo)
				printf("%s\n",elem->str);
			lista_apaga(l);
		}
	}

	grafo_apaga(g);
	lista_apaga(aeroportos);
	return 0;
}
