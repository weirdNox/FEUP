#include <stdio.h>
#include <string.h>

typedef struct
{
    char designacao[100];
    char marca[100];
    char modelo[100];
    int quantidade;
    float preco;
} Artigo;

void leArtigo(Artigo *item)
{
    printf("Nome do artigo: ");
    scanf("%s", item->designacao);
    printf("Marca: ");
    scanf("%s", item->marca);
    printf("Modelo: ");
    scanf("%s", item->modelo);
    printf("Número de artigos no armazém: ");
    scanf("%d", &item->quantidade);
    printf("Preço: ");
    scanf("%f", &item->preco);
}

int totalArtigos(Artigo armazem[], int n, char marca[], char modelo[])
{
    for(int i = 0; i < n; ++i)
    {
        if(strcmp(armazem[i].marca, marca) == 0 && strcmp(armazem[i].modelo, modelo) == 0)
        {
            return armazem[i].quantidade;
        }
    }
    return -1;
}

void alertaArtigos(Artigo armazem[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        if(armazem[i].quantidade < 10)
        {
            printf("O modelo %s da marca %s tem apenas %d artigos em stock!\n",
                   armazem[i].modelo, armazem[i].marca, armazem[i].quantidade);
        }
    }
}

void ordenaArtigos(Artigo armazem[], int n)
{
    for(int i = 0; i < n-1; ++i)
    {
        int min = armazem[i].quantidade;
        int minI = i;
        for(int j = i+1; j < n; ++j)
        {
            if(armazem[j].quantidade < min)
            {
                min = armazem[j].quantidade;
                minI = j;
            }
        }
        if(minI != i)
        {
            Artigo temp = armazem[i];
            armazem[i] = armazem[minI];
            armazem[minI] = temp;
        }
    }
}

void escreveArtigos(Artigo armazem[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%s  %d\n", armazem[i].modelo, armazem[i].quantidade);
    }
}
