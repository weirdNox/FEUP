#include <stdio.h>
#include "vetor.c"

int main()
{
    vetor *v = le_ficheiro("teste.txt");
    printf("Vetor com %d elementos.\n", v->tamanho);

    puts("SLOW QUICKSORT");
    v = le_ficheiro("teste.txt");
    vetor_ordena_qsort(v);
    for(int i = 0; i < v->tamanho; ++i)
    {
        printf("%s\n", v->elementos[i].str);
    }
    puts("\n\n");

    puts("FAST QUICKSORT");
    vetor_ordena(v);
    for(int i = 0; i < v->tamanho; ++i)
    {
        printf("%s\n", v->elementos[i].str);
    }
    vetor_apaga(v);

    return 0;
}
