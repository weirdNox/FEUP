#include <stdio.h>
#include <stdlib.h>

#define N_PECAS 100
#define MAX_NOME 32

typedef struct{
    char nome[MAX_NOME];
    int quantidade;
    float preco;
} peca;


int ler_pecas(peca modelo[]);
peca* lista_compras(peca modelo[], int Nm, float limite, int *Nc);
void guarda_lista(peca lista[], int n, char *nomeFicheiro);
void lista_pecas(peca modelo[], int n);

int main()
{
    peca modelo[N_PECAS], *compras;
    int nPecas, nCompras=0;

    nPecas = ler_pecas(modelo);
    printf("\n*** Lista de pecas (%d) ***\n", nPecas);
    lista_pecas(modelo, nPecas);
    printf("\n");

    compras = lista_compras(modelo, nPecas, 50, &nCompras);
    printf("\n*** Lista de compras (%d) ***\n", nCompras);
    lista_pecas(compras, nCompras);
    printf("\n");

    guarda_lista(compras, nCompras, "compras.txt");
    return 0;
}

/* Le todas as pecas do modelo para o vetor modelo e retorna
   numero de pecas armazenadas nesse vetor */
int ler_pecas(peca modelo[])
{
    int numPecas = 0;
    for(; numPecas < N_PECAS; ++numPecas)
    {
        if(scanf("%31s %d %f", modelo[numPecas].nome, &modelo[numPecas].quantidade,
                 &modelo[numPecas].preco) < 3)
        {
            break;
        }
    }

    return numPecas;
}

/* Retorna um vetor contendo a lista de compras. O numero de
   elementos nesse vetor e devolvido por referencia no parametro Nc.
   Os parametros modelo e Nm sao o vetor com as pecas do modelo e
   o respetivo tamanho. O parametro limite indica o limite de custo por peca. */
peca* lista_compras(peca modelo[], int Nm, float limite, int *Nc)
{
    peca *lista = 0;
    *Nc = 0;
    for(int i = 0; i < Nm; ++i)
    {
        peca *atual = modelo+i;
        if(atual->quantidade*atual->preco <= limite)
        {
            ++*Nc;
            peca *temp = realloc(lista, sizeof(*lista)*(*Nc));
            if(!temp)
            {
                fprintf(stderr, "Erro a alocar memória!\n");
                return 0;
            }
            lista = temp;
            lista[*Nc-1] = *atual;
        }
    }

    return lista;
}

/* Guarda no ficheiro com nome especificado por nomeFicheiro a lista de compras.
   Os parametros lista e n sao o vetor com a lista de compras e o respetivo tamanho. */
void guarda_lista(peca lista[], int n, char *nomeFicheiro)
{
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if(!ficheiro)
    {
        fprintf(stderr, "Erro a abrir o ficheiro %s!\n", nomeFicheiro);
        return;
    }

    for(int i = 0; i < n; ++i)
    {
        peca *atual = lista+i;
        fprintf(ficheiro, "%s %d %.2f\n", atual->nome, atual->quantidade, atual->preco);
    }
    fclose(ficheiro);
    ficheiro = 0;
}


/* Lista os medicamentos representados na lista de medicamentos */
void lista_pecas(peca modelo[], int n) {
    int index;
    if (modelo == NULL)
        return;
    for (index = 0 ; index < n ; index++)
        printf("%s - %d - %.2f\n", modelo[index].nome, modelo[index].quantidade, modelo[index].preco);
}
