/* ppf.c

f) Desenvolva um novo programa, corrijindo a versão da
alínea e) por forma a que, garantidamente, não haja "race conditions",
mesmo para um vector partilhado com um elevado nº de elementos!

Exemplo de invocação:
     ./ppf 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads
chkr_arg_t ac;	// estrutura de dados a usar no argumento para o thread de verificação

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

    int Id = Arg->Id;
    for(int I = 0; I < Arg->NumElements; ++I) {
        pthread_mutex_lock(&Arg->Vec->lock);
        int IdxToFill = Arg->Vec->next++;
        pthread_mutex_unlock(&Arg->Vec->lock);
        Arg->Vec->array[IdxToFill] = Id;
        ++Arg->Vec->cnt[Id];
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

    pthread_t CheckerThread;
    ac.argc = argc;
    ac.argv = argv;
    ac.vector = &vector;
    pthread_create(&CheckerThread, 0, checker, &ac);

    for(int I = 0; I < NT; ++I) {
        pthread_create(&Threads[I].Thread, 0, threadFunc, Threads + I);
    }

    for(int I = 0; I < NT; ++I) {
        pthread_join(Threads[I].Thread, 0);
    }

    pthread_join(CheckerThread, 0);

    printf("Main thread exiting\n");

    return 0;
}
