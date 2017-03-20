#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
float comprimento_medio(lista *lst)
{
	/* complexidade do algoritmo: ______________ */
	return 0;
}

/*** problema 1.2 ***/
lista* filtra_nomes(lista *lst, char *existe)
{
	return NULL;
}

/*** problema 1.3 ***/
const char* mais_palavras(vetor *vec)
{
	return NULL;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

vetor* lerParaVetor(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	vetor* v;
	
	if (ficheiro == NULL)
		return NULL;

	v = vetor_novo();

	while(!feof(ficheiro)) 
	{	
		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr) 
			*nlptr = '\0';
		
		vetor_insere(v,buffer,v->tamanho);
	}

	return v;
}

lista* lerParaLista(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	lista* l;
	
	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();
	
	while(!feof(ficheiro)) 
	{	
		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr) 
			*nlptr = '\0';
		
		lista_insere(l,buffer,NULL);
	}

	return l;
}

int main()
{
	FILE *f;
    vetor *v;
    lista *l, *resultado;
    elemento *e;
    const char *nome;
    int i;
    double comp;
    
	/* testes */
	f = fopen("freguesias.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l = lerParaLista(f);
		
	/* testa comprimento_medio */
	comp = comprimento_medio(l);
	if(comp)
		printf("\nComprimento medio das palavras: %.1f\n", comp);
	else
	   	printf("\ncomprimento_medio retornou 0\n");

	/* testa filtra_nomes */
    resultado = filtra_nomes(l, "Mamede");
    
	if(resultado)
	{
            printf("\nNomes filtrados (total de %d):\n", lista_tamanho(resultado));
            for (e = resultado->inicio; e != NULL; e = e->proximo)
                printf("%s\n", e->str);

            if(lista_tamanho(l) != 4230)
            	printf("Nem todos os nomes foram removidos do vetor (tamanho: %d; esperado: 4218)\n", lista_tamanho(l));
    }
	else
		printf("\nfiltra_nomes retornou NULL\n");

	/* testa mais_palavras */
	rewind(f);
	v = lerParaVetor(f);    
	nome = mais_palavras(v);
	if(nome)
	  	printf("\nNome com mais palavras: %s\n\n", nome);
	else
	   	printf("\nmais_palavras retornou NULL\n\n");
	
	vetor_apaga(v);
	lista_apaga(l);
	lista_apaga(resultado);
	
	fclose(f);
		
	return 0;
}