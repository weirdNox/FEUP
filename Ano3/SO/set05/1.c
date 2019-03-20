#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


#define Sync 1


pthread_mutex_t Mutex;
#include "tfun.c"

enum {
    NumThreads = 3,
};

#if Sync
#define Func sfun
#else
#define Func tfun
#endif

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s TimesToIncrement\n", ArgVals[0]);
        exit(1);
    }

    int TimesToIncrement;
    sscanf(ArgVals[1], "%d", &TimesToIncrement);

    pthread_t Threads[NumThreads];
    targ_t ThreadArgs[NumThreads];

    long int Counter = 0;
    pthread_mutex_init(&Mutex, 0);

    for(size_t Idx = 0; Idx < NumThreads; ++Idx) {
        targ_t *Arg = ThreadArgs + Idx;

        Arg->cnt = &Counter;
        Arg->n = TimesToIncrement;
        Arg->id = Idx;

        pthread_create(Threads + Idx, 0, Func, Arg);
    }

    for(size_t Idx = 0; Idx < NumThreads; ++Idx) {
        pthread_join(Threads[Idx], 0);
    }

    pthread_mutex_destroy(&Mutex);

    printf("Counter result: %ld\n", Counter);

    return 0;
}
