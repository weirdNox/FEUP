/* ppd.c

   d) Desenvolva um novo programa que, para além de fazer o
   que é pedido nas alíneas anteriores, faça com que os 2 threads de
   inicialização inicializem *mesmo* o vector partilhado, mas sem
   tentarem evitar erros de competição ("race conditions").  A impressão
   da informação já pedida na alínea anterior irá permitir ver o trabalho
   que foi efectuado.

   *Nota:* aqui já deve ser possível observar que há erros de
   competição, mesmo para um vector partilhado com um nº de elementos
   relativamente pequeno! É óbvio, pois não houve esforço de
   sincronização no acesso ao vector!

   Exemplo de invocação:
   ./ppd 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

typedef struct {
    int Id;
    int NumElements;
    vector_t *Vec;
    pthread_t Thread;
} thread_info;

void *threadFunc(void *RawArg) {
    thread_info *Arg = (thread_info *)RawArg;
    printf("Thread %ld running\n", pthread_self());
    printf("Thread %d: cnt = %d, vp = %p\n", Arg->Id, Arg->Vec->cnt[Arg->Id], Arg->Vec);

    for(int I = 0; I < Arg->NumElements; ++I) {
        int IdxToFill = Arg->Vec->next++;
        Arg->Vec->array[IdxToFill] = Arg->Id;
        ++Arg->Vec->cnt[Arg->Id];
    }

    print_vector(Arg->Vec);
    return 0;
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    if(argc < 1+NT) {
        print_usage(argv[0]);
        exit(1);
    }

    vector.len = 0;
    thread_info Threads[NT];
    for(int I = 0; I < NT; ++I) {
        if(!parse_int(argv[I+1], &Threads[I].NumElements, I+1)) {
            exit(2);
        }
        Threads[I].NumElements *= 1000;
        Threads[I].Id = I;
        Threads[I].Vec = &vector;
        vector.len += Threads[I].NumElements;
        vector.cnt[I] = 0;
    }
    vector.array = malloc(sizeof(*vector.array)*vector.len);
    vector.next = 0;
    pthread_mutex_init(&vector.lock, 0);

    print_vector(&vector);

    for(int I = 0; I < NT; ++I) {
        pthread_create(&Threads[I].Thread, 0, threadFunc, Threads + I);
    }

    for(int I = 0; I < NT; ++I) {
        pthread_join(Threads[I].Thread, 0);
    }

    printf("Main thread exiting\n");
    return 0;
}
