#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_t Thread;
    int *Array;
    int NumToFill;
    int StartIdx;
} thread_work;

typedef void *thread_func_t(void *);

void *threadFunc(thread_work *Work) {
    int PartitionSize = Work->NumToFill;
    int End = Work->StartIdx + PartitionSize;
    for(int Idx = Work->StartIdx; Idx < End; ++Idx) {
        Work->Array[Idx] = Idx;
    }

    return 0;
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 3) {
        fprintf(stderr, "Usage: %s ArraySize NumThreads\n", ArgVals[0]);
        exit(1);
    }

    int ArraySize, NumThreads;
    sscanf(ArgVals[1], "%d", &ArraySize);
    sscanf(ArgVals[2], "%d", &NumThreads);

    if(ArraySize < 0 || NumThreads <= 0) {
        exit(1);
    }

    int PartitionSize = ArraySize / NumThreads;
    if(PartitionSize == 0) {
        PartitionSize = 1;
        NumThreads = ArraySize;
        printf("Limiting thread count to array size (%d)\n", NumThreads);
    }

    int *IntArray = malloc(sizeof(*IntArray)*ArraySize);
    thread_work *ThreadWorkArr = malloc(sizeof(*ThreadWorkArr)*NumThreads);

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_work *Work = ThreadWorkArr + Idx;

        Work->Array = IntArray;
        Work->StartIdx = Idx*PartitionSize;

        if(Idx + 1 == NumThreads) {
            Work->NumToFill = ArraySize - Work->StartIdx;
        }
        else {
            Work->NumToFill = PartitionSize;
        }

        pthread_create(&Work->Thread, 0, (thread_func_t *)threadFunc, Work);
    }

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_work *Work = ThreadWorkArr + Idx;
        pthread_join(Work->Thread, 0);
    }

    printf("ARRAY:\n");
    for(int Idx = 0; Idx < ArraySize; ++Idx) {
        printf("Index %2d: %2d\n", Idx, IntArray[Idx]);
    }

    return 0;
}
