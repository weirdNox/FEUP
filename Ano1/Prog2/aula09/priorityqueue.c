#define RAIZ            (1)
#define PAI(x)          (x/2)
#define FILHO_ESQ(x)    (x*2)
#define FILHO_DIR(x)    ((x*2)+1)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vetor.c"

typedef int (* compara)(elemento *, elemento *);

int fp_insere(vetor * fp, char * valor, int prioridade) {
    if(!fp || !valor || fp->tamanho == fp->capacidade)
    {
        return -1;
    }

    elemento *novo = malloc(sizeof(*novo));
    if(!novo)
    {
        return -1;
    }

    novo->prioridade = prioridade;
    novo->valor = malloc(strlen(valor)+1);
    if(!novo->valor)
    {
        free(novo);
        return -1;
    }
    strcpy(novo->valor, valor);

    int pos;
    for(pos = fp->tamanho-1; pos >= 0; --pos)
    {
        if(maior_que(novo, fp->elementos[pos]))
        {
            fp->elementos[pos+1] = fp->elementos[pos];
        }
        else
        {
            break;
        }
    }
    fp->elementos[pos+1] = novo;
    ++fp->tamanho;

    return 0;
}

char * fp_remove(vetor * fp) {
    if(!fp || !fp->tamanho)
    {
        return 0;
    }

    elemento *maximo = fp->elementos[0];
    char *str = maximo->valor;
    free(maximo);

    --fp->tamanho;

    int i;
    for(i = 0; i < fp->tamanho; ++i)
    {
        fp->elementos[i] = fp->elementos[i+1];
    }
    fp->elementos[i] = 0;

    return str;
}

void fp_carrega(vetor * fp, const char * filename) {

    char texto[256];
    int prioridade;

    FILE * file = fopen(filename, "r");
    if (!file) {
        printf("Nao foi possivel abrir ficheiro!\n");
        return;
    }

    while(!feof(file)) {
        fscanf(file, "%d ", &prioridade);
        fgets(texto, 256, file);
        texto[strlen(texto)-1] = '\0';
        fp_insere(fp, texto, prioridade);
    }

    fclose(file);
}


int heap_insere(vetor * h, compara cmp, char * texto, int prioridade) {
    if(!h || !texto || h->tamanho == h->capacidade)
    {
        return -1;
    }

    elemento *novo = malloc(sizeof(*novo));
    if(!novo)
    {
        return -1;
    }

    novo->prioridade = prioridade;
    novo->valor = malloc(strlen(texto)+1);
    if(!novo->valor)
    {
        free(novo);
        return -1;
    }
    strcpy(novo->valor, texto);

    int pos = ++h->tamanho;
    int prox = PAI(pos);
    while(prox && cmp(novo, h->elementos[prox]))
    {
        h->elementos[pos] = h->elementos[prox];
        pos = prox;
        prox = PAI(pos);
    }
    h->elementos[pos] = novo;

    return 0;
}

char * heap_remove(vetor * h, compara cmp) {
    if(!h || !h->tamanho)
    {
        return 0;
    }

    elemento *maximo = h->elementos[1];
    elemento *ultimo = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = 0;
    --h->tamanho;

    if(h->tamanho)
    {
        int pos, filho;
        for(pos = 1; pos*2 <= h->tamanho; pos = filho)
        {
            filho = pos*2;
            if(filho < h->tamanho && cmp(h->elementos[filho+1], h->elementos[filho]))
            {
                ++filho;
            }

            if(cmp(h->elementos[filho], ultimo))
            {
                h->elementos[pos] = h->elementos[filho];
            }
            else
            {
                break;
            }
        }
        h->elementos[pos] = ultimo;
    }

    char *str = maximo->valor;
    free(maximo);
    return str;
}

void heap_carrega(vetor * v, compara cmp, const char * filename) {

    char texto[256];
    int prioridade;

    FILE * file = fopen(filename, "r");
    if (!file) {
        printf("Nao foi possivel abrir ficheiro!\n");
        return;
    }

    while(!feof(file)) {
        fscanf(file, "%d ", &prioridade);
        fgets(texto, 256, file);
        texto[strlen(texto)-1] = '\0';
        heap_insere(v, cmp, texto, prioridade);
    }

    fclose(file);
}

int filmeMaiorHeap(elemento *e1, elemento *e2)
{
    if(!e1 || ! e2)
    {
        return 0;
    }
    return e1->prioridade < e2->prioridade;
}

void heap_carrega_filmes(vetor * v, const char * filename) {
    char texto[256];
    int prioridade;

    FILE * file = fopen(filename, "r");
    if (!file) {
        printf("Nao foi possivel abrir ficheiro!\n");
        return;
    }

    while(!feof(file)) {
        fscanf(file, "%d; ", &prioridade);
        fgets(texto, 256, file);
        texto[strlen(texto)-1] = '\0';
        heap_insere(v, filmeMaiorHeap, texto, prioridade);
    }

    fclose(file);
}

int main(int argc, char **argv) {
    vetor *v;
    char *str;

    /******* 1 *******/

    printf("Teste da implementacao de fila de prioridade com vetor\n");

    v = vetor_cria(42);
    fp_carrega(v, "dados.txt");
    printf("Comparacoes necessarias para carregar o ficheiro: %d.\n", ncomparacoes);

    /* se pretender imprimir o conteudo do vetor pode retirar o comentario em baixo */
    /* vetor_imprime(v); */

    if (v->tamanho != 42) {
        printf("Tamanho do vetor devia ser 42!\n");
        return 1;
    }

    str = fp_remove(v);
    if (strcmp("Maurice V. Wilkes", str)) {
        printf("[ERRO] Elemento com maior prioridade devia ser \"Maurice V. Wilkes\".\n");
        free(str);
        return 1;
    }
    free(str);

    ncomparacoes = 0;
    free(fp_remove(v));
    printf("Comparacoes necessarias para remover um valor: %d.\n", ncomparacoes);

    ncomparacoes = 0;
    fp_insere(v, "Novo elemento", 99);
    printf("Comparacoes necessarias para inserir valor com maxima prioridade: %d.\n", ncomparacoes);
    free(fp_remove(v));

    ncomparacoes = 0;
    fp_insere(v, "Novo elemento", 0);
    printf("Comparacoes necessarias para inserir valor com minima prioridade: %d.\n", ncomparacoes);
    free(fp_remove(v));

    ncomparacoes = 0;
    fp_insere(v, "Novo elemento", 42);
    printf("comparacoes necessarias para inserir valor com media prioridade: %d.\n", ncomparacoes);

    vetor_apaga(v);

    /******* 2 *******/

    printf("\n\nTeste da implementacao de fila de prioridade com heap\n");

    v = vetor_criaHeap(42);
    heap_carrega(v, maior_que, "dados.txt");
    printf("comparacoes necessarias para carregar o ficheiro: %d.\n", ncomparacoes);

    /* se pretender imprimir o conteudo do heap pode retirar o comentario em baixo */
    /* vetor_imprimeHeap(v); */

    if (v->tamanho != 42) {
        printf("Tamanho do vetor deviar ser 42!\n");
        return 1;
    }

    str = heap_remove(v, maior_que);
    if (strcmp("Maurice V. Wilkes", str)) {
        printf("[ERRO] Elemento com maior prioridade devia ser \"Maurice V. Wilkes\".\n");
        free(str);
        return 1;
    }
    free(str);

    ncomparacoes = 0;
    free(heap_remove(v, maior_que));
    printf("comparacoes necessarias para remover um valor: %d.\n", ncomparacoes);

    ncomparacoes = 0;
    heap_insere(v, maior_que, "Novo elemento", 99);
    printf("comparacoes necessarias para inserir valor com maxima prioridade: %d.\n", ncomparacoes);

    free(heap_remove(v, maior_que));

    ncomparacoes = 0;
    heap_insere(v, maior_que, "Novo elemento", 0);
    printf("comparacoes necessarias para inserir valor com minima prioridade: %d.\n", ncomparacoes);
    free(heap_remove(v, maior_que));

    ncomparacoes = 0;
    heap_insere(v, maior_que, "Novo elemento", 42);
    printf("comparacoes necessarias para inserir valor com media prioridade: %d.\n", ncomparacoes);

    vetor_apaga(v);

    /******* 3 *******/

    printf("\n\nTeste da implementacao de Heapsort\n");

    v = vetor_criaHeap(42);
    heap_carrega(v, maior_que_HeapSort, "dados.txt");
    printf("comparacoes necessarias para carregar o ficheiro: %d.\n", ncomparacoes);

    str = heap_remove(v, maior_que_HeapSort);
    while(str != NULL)
    {
        puts(str);
        free(str);
        str = heap_remove(v, maior_que_HeapSort);
    }

    vetor_apaga(v);


    // NOTE(nox): 4 ------------------------------
    puts("\nFILMES:");
    v = vetor_criaHeap(300);
    heap_carrega_filmes(v, "movies.csv");
    while(v->tamanho)
    {
        printf("%d - %s\n", v->elementos[1]->prioridade, heap_remove(v, filmeMaiorHeap));
    }

    vetor_apaga(v);

    return 0;
}
