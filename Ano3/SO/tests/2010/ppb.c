/* ppb.c

   b) Desenvolva um novo programa que, para além de fazer o
   que é pedido em a) crie os 2 threads de inicialização. Cada
   um destes threads deverá invocar a função printf() do seguinte
   modo:

   printf ("Thread %d running\n", pthread_self());

   O thread principal deverá esperar que cada um dos threads de inicialização
   termine, após o que deverá imprimir:

   printf ("Main thread exiting\n");

   Nota: Nesta alínea não precisa de passar qualquer argumento aos threads
   de inicialização.

   Exemplo de invocação:
   ./ppb 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

void *threadFunc(void *RawArg) {
    printf("Thread %ld running\n", pthread_self());
    return 0;
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    if(argc < 3) {
        print_usage(argv[0]);
        exit(1);
    }

    int Thread0Count;
    if(!parse_int(argv[1], &Thread0Count, 1)) {
        exit(2);
    }

    int Thread1Count;
    if(!parse_int(argv[2], &Thread1Count, 2)) {
        exit(2);
    }

    vector.len = 1000*(Thread0Count + Thread1Count);
    vector.array = malloc(sizeof(*vector.array)*vector.len);
    vector.next = 0;
    vector.cnt[0] = 0;
    vector.cnt[1] = 0;
    pthread_mutex_init(&vector.lock, 0);

    print_vector(&vector);

    pthread_t Threads[NT];
    for(int I = 0; I < NT; ++I) {
        pthread_create(Threads + I, 0, threadFunc, 0);
    }

    for(int I = 0; I < NT; ++I) {
        pthread_join(Threads[I], 0);
    }

    printf("Main thread exiting\n");

    return 0;
}
