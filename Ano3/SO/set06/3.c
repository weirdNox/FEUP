#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum {
    ArrayCount = 10000000,
    QueueSize = 200,
};

typedef struct {
    size_t LeftRunIdx;
    size_t RightRunIdx;
    size_t EndIdx;
} queue_item;

typedef struct {
    queue_item Data[QueueSize];
    size_t WriteIdx;
    size_t ReadIdx;
    size_t NotDone;
    sem_t FillSem;
    sem_t ReadSem;
    sem_t Lock;
} queue;

typedef struct {
    pthread_t ThreadId;
    queue *Queue;
    int *Array;
    int *WorkArray;
    int Killed;
} thread_data;

size_t min(size_t A, size_t B) {
    if(A <= B) {
        return A;
    }
    else {
        return B;
    }
}

void merge(int *Array, int *WorkArray, size_t LeftRunIdx, size_t RightRunIdx, size_t EndIdx) {
    size_t LeftHead = LeftRunIdx;
    size_t RightHead = RightRunIdx;

    for(size_t Idx = LeftRunIdx; Idx < EndIdx; ++Idx) {
        if(LeftHead < RightRunIdx && (RightHead >= EndIdx || Array[LeftHead] <= Array[RightHead])) {
            WorkArray[Idx] = Array[LeftHead];
            ++LeftHead;
        }
        else {
            WorkArray[Idx] = Array[RightHead];
            ++RightHead;
        }
    }
}

void *threadMerge(void *RawArg) {
    thread_data *Arg = (thread_data *)RawArg;

    for(;;) {
        sem_wait(&Arg->Queue->ReadSem);

        if(Arg->Killed) {
            break;
        }

        sem_wait(&Arg->Queue->Lock);
        queue_item Item = Arg->Queue->Data[Arg->Queue->ReadIdx];
        Arg->Queue->ReadIdx = (Arg->Queue->ReadIdx + 1) % QueueSize;
        sem_post(&Arg->Queue->Lock);
        sem_post(&Arg->Queue->FillSem);

        size_t LeftHead = Item.LeftRunIdx;
        size_t RightHead = Item.RightRunIdx;

        for(size_t Idx = Item.LeftRunIdx; Idx < Item.EndIdx; ++Idx) {
            if(LeftHead < Item.RightRunIdx && (RightHead >= Item.EndIdx ||
                                               Arg->Array[LeftHead] <= Arg->Array[RightHead]))
            {
                Arg->WorkArray[Idx] = Arg->Array[LeftHead];
                ++LeftHead;
            }
            else {
                Arg->WorkArray[Idx] = Arg->Array[RightHead];
                ++RightHead;
            }
        }

        sem_wait(&Arg->Queue->Lock);
        --Arg->Queue->NotDone;
        sem_post(&Arg->Queue->Lock);
    }

    return 0;
}

void sort(int *Array, size_t Length, int NumThreads) {
    int *WorkArray = malloc(Length*sizeof(*WorkArray));

    queue Queue = {};
    sem_init(&Queue.FillSem, 0, QueueSize);
    sem_init(&Queue.ReadSem, 0, 0);
    sem_init(&Queue.Lock, 0, 1);

    thread_data *Threads = malloc(NumThreads*sizeof(*Threads));
    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        Threads[Idx].Queue = &Queue;
        Threads[Idx].Array = Array;
        Threads[Idx].WorkArray = WorkArray;
        Threads[Idx].Killed = 0;
        pthread_create(&Threads[Idx].ThreadId, 0, threadMerge, Threads + Idx);
    }

    for(size_t Width = 1; Width < Length; Width = 2*Width) {
        for(size_t Idx = 0; Idx < Length; Idx = Idx + 2*Width) {
            sem_wait(&Queue.FillSem);
            queue_item *Item = Queue.Data + Queue.WriteIdx;
            Queue.WriteIdx = (Queue.WriteIdx + 1) % QueueSize;

            Item->LeftRunIdx = Idx;
            Item->RightRunIdx = min(Idx+Width, Length);
            Item->EndIdx = min(Idx+2*Width, Length);

            sem_wait(&Queue.Lock);
            ++Queue.NotDone;
            sem_post(&Queue.Lock);

            sem_post(&Queue.ReadSem);
        }

        while(Queue.NotDone) {
            __asm__ volatile("" : : : "memory");
        }

        for(size_t Idx = 0; Idx < Length; ++Idx) {
            Array[Idx] = WorkArray[Idx];
        }
    }

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        Threads[Idx].Killed = 1;
        sem_post(&Queue.ReadSem);
    }

    free(WorkArray);
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s NumThreads\n", ArgVals[0]);
        exit(1);
    }

    int NumThreads;
    sscanf(ArgVals[1], "%d", &NumThreads);

    int *Array = malloc(ArrayCount * sizeof(*Array));
    for(int Idx = 0; Idx < ArrayCount; ++Idx) {
        Array[Idx] = ArrayCount-1-Idx;
    }

    struct timespec Start, End;
    clock_gettime(CLOCK_MONOTONIC, &Start);
    sort(Array, ArrayCount, NumThreads);
    clock_gettime(CLOCK_MONOTONIC, &End);

    for(int Idx = 0; Idx < ArrayCount; ++Idx) {
        assert(Array[Idx] == Idx);
    }
    printf("Time spent with %d threads: %f\n", NumThreads, (((double)End.tv_sec + 1.0e-9*End.tv_nsec) -
                                                            ((double)Start.tv_sec + 1.0e-9*Start.tv_nsec)));

    return 0;
}
