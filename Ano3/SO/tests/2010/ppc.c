/* ppc.c

   c) Desenvolva um novo programa, que além de fazer o que é pedido
   nas alíneas anteriores, deverá fazer com que cada um dos threads
   de inicialização invoque a função printf() do seguinte modo:

   printf ("Thread %d: cnt = %d, vp = %p\n", X, Y, Z);

   onde X representa o identificador do thread (ou 0 ou 1), Y representa
   o nº de elementos que o thread deverá inicializar, e Z o endereço da
   estrutura de dados do tipo vector_t partilhada pelos threads de
   inicialização.  Antes de terminar cada thread deverá ainda
   invocar a função print_vector() já referida.

   Nota: Cada thread deverá invocar esta instrução com um valor X diferente.

   Exemplo de invocação:
   ./ppc 6000 4000
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
        Threads[I].Id = I;
        Threads[I].Vec = &vector;
        vector.len += 1000*Threads[I].NumElements;
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
