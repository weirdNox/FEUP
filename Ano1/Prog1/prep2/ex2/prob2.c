#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMANIMAIS 150

typedef struct {
    char nome[50];
    char tipo[25];
    char nome_dono[75];
    int tlm_dono;
} animal;

int ler_animais(animal *clinica);
animal* lista_animais(animal *clinica, int Na, char *tipo, int *Nl);
void guarda_lista(animal *lista, int n, char *nomeFicheiro);
void listaRegistos(animal *clinica, int num);

/*
  Para sortear (por seleção) os animais por ordem alfabética, temos de ter um loop com
  i=[0,n-1[, e definir um apontador `min` inicializado com o endereço do elemento i. Temos
  depois de ter um loop com j=[i+1, n[, e dentro desse loop é que vamos comparar os
  elementos. Começamos por comparar os nomes dos animais, e se esse nome for igual,
  comparamos então o nome dos donos. Se o resultado der que o elemento j vem antes do
  `min`, então damos o valor do endereço do elemento j a `min`. Fora deste loop interno,
  se `min` for diferente do elemento i, então trocamos o elemento de endereço `min` com o
  elemento i.
  Temos, finalmente, a lista sorteada.
 */

void sort(animal *lista, int n)
{
    for(int i = 0; i < n-1; ++i)
    {
        animal *min = lista+i;
        for(int j = i+1; j < n; ++j)
        {
            animal *test = lista+j;
            int cmp = strcmp(min->nome, test->nome);
            if(cmp == 0)
            {
                cmp = strcmp(min->nome_dono, test->nome_dono);
            }

            if(cmp > 0)
            {
                min = test;
            }
        }

        if(lista+i != min)
        {
            animal temp = *min;
            *min = *(lista+i);
            *(lista+i) = temp;
        }
    }
}

int main()
{
    animal clinica[NUMANIMAIS], *lista;
    int numRegistos, n, n_lista;

    numRegistos=ler_animais(clinica);

    printf("Numero registos lidos %d\n", numRegistos);
    sort(clinica, numRegistos);
    listaRegistos(clinica, numRegistos);

    lista = lista_animais(clinica, numRegistos, "coelho", &n_lista);
    printf("Numero de registos \"coelho\": %d\n", n_lista);
    /* listaRegistos(lista, n_lista); */

    guarda_lista(lista, n_lista, "teste.txt");

    return 0;
}

int ler_animais(animal *clinica)
{
    int numAnimais = 0;
    for(; numAnimais < NUMANIMAIS; ++numAnimais)
    {
        animal *atual = clinica + numAnimais;
        char primeiro[50], ultimo[50];
        if(scanf("%s %s %s %s %d", atual->nome, atual->tipo,
                 primeiro, ultimo, &atual->tlm_dono) < 5)
        {
            break;
        }
        strcat(atual->nome_dono, primeiro);
        strcat(atual->nome_dono, " ");
        strcat(atual->nome_dono, ultimo);
    }

    return numAnimais;
}

animal* lista_animais(animal *clinica, int Na, char *tipo, int *Nl)
{
    *Nl = 0;
    animal *lista = 0;
    for(int i = 0; i < Na; ++i)
    {
        animal *atual = clinica + i;
        if(strcmp(atual->tipo, tipo) == 0)
        {
            ++(*Nl);
            animal *temp = realloc(lista, sizeof(*lista)*(*Nl));
            if(!temp)
            {
                fprintf(stderr, "Erro na alocação dinâmica de memória!\n");
                return 0;
            }
            lista = temp;
            lista[*Nl-1] = *atual;
        }
    }

    return lista;
}

void guarda_lista(animal *lista, int n, char *nomeFicheiro)
{
    FILE *file = fopen(nomeFicheiro, "w");
    if(!file)
    {
        fprintf(stderr, "Erro ao abrir ficheiro!");
        return;
    }

    for(int i = 0; i < n; ++i)
    {
        animal *atual = lista + i;
        fprintf(file, "%s %s %s %d\n", atual->nome, atual->tipo,
                atual->nome_dono, atual->tlm_dono);
    }
    fclose(file);
    file = 0;
}

void listaRegistos(animal *animais, int num)
{
    int i;
    for(i=0; i<num; i++)
        printf("%s %s %s %d\n",animais[i].nome, animais[i].tipo, animais[i].nome_dono, animais[i].tlm_dono);
}
