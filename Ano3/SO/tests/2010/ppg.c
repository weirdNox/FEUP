/* ppg.c

   g) Desenvolva um novo programa que garanta que, em qualquer
   instante da inicialização do vector partilhado, a diferença máxima (em
   milhares) entre o nº de elementos inicializado por cada thread não
   excede um dado valor. Isto permitirá um maior grau de "entremeação" -
   e competição - na execução dos threads. Tal diferença máxima de
   elementos inicializados será apresentada como um parâmetro adicional
   na linha de comando. Por ex., com uma invocação na forma :

   ./ppg 5000 5000 1

   o seu programa deverá criar 2 threads, o primeiro dos quais deverá
   inicializar 5000 milhares de elementos com o valor 0 e o segundo com
   5000 milhares com o valor 1, sendo que em qualquer instante o nº de
   elementos inicializado por cada thread não pode diferir em mais de
   1000.

   O seu programa deverá usar semáforos ou variáveis de condição para
   sincronizar correctamente os 2 threads de inicialização sem "busy
   waiting."

   Nota: Assuma que o programa é invocado sempre com argumentos
   cujos valores são tais que o valor absoluto da diferença dos 2
   primeiros argumentos não excede o valor do 3º argumento.

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
    pthread_cond_t *CondVar;
    int MaxDiff;
} thread_info;

void *threadFunc(void *RawArg) {
    thread_info *Arg = (thread_info *)RawArg;
    printf("Thread %ld running\n", pthread_self());
    printf("Thread %d: cnt = %d, vp = %p\n", Arg->Id, Arg->Vec->cnt[Arg->Id], Arg->Vec);

    int Id = Arg->Id;
    for(int I = 0; I < Arg->NumElements; ++I) {
        pthread_mutex_lock(&Arg->Vec->lock);
        while(Arg->Vec->cnt[Id] - Arg->Vec->cnt[(Id+1) % NT] >= Arg->MaxDiff) {
            pthread_cond_wait(Arg->CondVar, &Arg->Vec->lock);
        }
        ++Arg->Vec->cnt[Id];
        int IdxToFill = Arg->Vec->next++;
        if(Arg->Vec->cnt[(Id+1) % NT] - Arg->Vec->cnt[Id] < Arg->MaxDiff) {
            pthread_cond_signal(Arg->CondVar);
        }
        pthread_mutex_unlock(&Arg->Vec->lock);
        Arg->Vec->array[IdxToFill] = Id;
    }

    print_vector(Arg->Vec);
    return 0;
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    if(argc < 1+NT+1) {
        print_usage(argv[0]);
        exit(1);
    }

    int MaxDiff;
    parse_int(argv[3], &MaxDiff, 3);
    MaxDiff *= 1000;

    pthread_cond_t CondVar = PTHREAD_COND_INITIALIZER;

    vector.len = 0;
    thread_info Threads[NT];
    for(int I = 0; I < NT; ++I) {
        if(!parse_int(argv[I+1], &Threads[I].NumElements, I+1)) {
            exit(2);
        }
        Threads[I].NumElements *= 1000;
        Threads[I].Id = I;
        Threads[I].Vec = &vector;
        Threads[I].CondVar = &CondVar;
        Threads[I].MaxDiff = MaxDiff;
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
