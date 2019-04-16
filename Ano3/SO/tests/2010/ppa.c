/* ppa.c
   a) Escreva um programa que processe os argumentos da linha
   de comando, inicialize a estrutura de tipo "vector_t" a usar e,
   finalmente, mostre o estado do vector partilhado por via da invocação
   da função "print_vector()" (incluída em util.c)

   Exemplo de invocação:
   ./ppa 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

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
    return 0;
}
