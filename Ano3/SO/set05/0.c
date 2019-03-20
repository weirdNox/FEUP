#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


#define WithMutexes 1


#define arrayCount(Arr) (sizeof(Arr)/sizeof(*(Arr)))

enum {
    NumThreads = 3,
};

typedef struct {
    pthread_t ThreadId;
    int TimesToIncrement;
} thread_info;

pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
int Counter = 0;

void *threadFunc(void *RawArg) {
    thread_info *Arg = (thread_info *)RawArg;

    for(int Num = 0; Num < Arg->TimesToIncrement; ++Num) {
#if WithMutexes
        pthread_mutex_lock(&Mutex);
#endif
        ++Counter;
#if WithMutexes
        pthread_mutex_unlock(&Mutex);
#endif
    }

    return 0;
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s NumTimesToIncrement\n", ArgVals[0]);
        exit(1);
    }

    int TimesToIncrement;
    sscanf(ArgVals[1], "%d", &TimesToIncrement);

    thread_info ThreadInfos[NumThreads];

#if WithMutexes
    pthread_mutex_init(&Mutex, 0);
#endif

    for(size_t Idx = 0; Idx < arrayCount(ThreadInfos); ++Idx) {
        thread_info *Info = ThreadInfos + Idx;
        Info->TimesToIncrement = TimesToIncrement;
        pthread_create(&Info->ThreadId, 0, threadFunc, Info);
    }

    for(size_t Idx = 0; Idx < arrayCount(ThreadInfos); ++Idx) {
        pthread_join(ThreadInfos[Idx].ThreadId, 0);
    }

#if WithMutexes
    pthread_mutex_destroy(&Mutex);
#endif

    printf("After %d threads increment the counter %d times, the result is %d (expected %d)\n",
           NumThreads, TimesToIncrement, Counter, NumThreads*TimesToIncrement);

    return 0;
}
