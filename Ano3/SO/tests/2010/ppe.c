/* ppe.c
e) Desenvolva um novo programa que, além de fazer o que é
pedido nas alíneas anteriores, cria um thread de verificação, i.e. que
executa a função checker() declarada em util.h. O argumento
desta função deve ser um apontador para uma variável do tipo
chkr_arg_t definida também em util.h, e aqui reproduzida:

typedef struct {
    int argc;          // to be initialized with argc of main()
    char **argv;       // to be initializedwith argv of main()
    vector_t *pvector; // to be initialized with pointer to the shared structure
} chkr_arg_t;

O thread de verificação deve ser criado antes dos threads de
inicialização e esperado pelo thread principal apenas depois daqueles
terem terminado.

*Nota:* aqui também ainda devem ser patentes
os erros de competição, mesmo para um vector partilhado com um nº de
elementos relativamente pequeno, pois ainda pois não houve esforço de
sincronização no acesso ao vector!

Exemplo de invocação:
     ./ppe 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;  // estrutura de dados a partilhar pelos threads
chkr_arg_t ac;	  // estrutura de dados a usar no argumento para o thread de verificação

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
