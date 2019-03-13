#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

typedef struct {
    pthread_t ThreadInfo;
    int Argument;
} thread_info;

void *threadFun(int *Arg) {
    printf("Thread ID: %ld\n", syscall(SYS_gettid));
    return Arg;
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s NumThreads\n", ArgVals[0]);
        exit(1);
    }

    int NumThreads;
    sscanf(ArgVals[1], "%d", &NumThreads);
    thread_info *InfoArr = malloc(sizeof(*InfoArr)*NumThreads);
    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_info *Info = InfoArr + Idx;
        Info->Argument = Idx+1;
        pthread_create(&Info->ThreadInfo, 0, (void *(*)(void *))threadFun, &Info->Argument);
    }

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_info *Info = InfoArr + Idx;
        int *ReturnVal;
        pthread_join(Info->ThreadInfo, (void **)&ReturnVal);
        printf("Thread returned %d\n", *ReturnVal);
    }

    return 0;
}
