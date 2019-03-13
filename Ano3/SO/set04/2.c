#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define THREAD_FUNC(Name) void *Name(void *)
typedef THREAD_FUNC(thread_func);

enum { NumThreads = 3 };

typedef struct {
    int Number;
} thread_arg;

void *threadFunc(thread_arg *Arg) {
    printf("Thread ID: %ld\t\tProcess ID: %d\n", syscall(SYS_gettid), getpid());
    return &Arg->Number;
}

int main() {
    pthread_t Threads[NumThreads];
    thread_arg ThreadArgs[NumThreads] = {
        {1}, {2}, {3},
    };
    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        pthread_create(Threads + Idx, 0, (thread_func *)threadFunc, ThreadArgs + Idx);
    }

    printf("Process ID: %d\n", getpid());

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        int *Result;
        pthread_join(Threads[Idx], (void **)&Result);
        printf("Thread returned: %d\n", *Result);
    }

    return 0;
}
