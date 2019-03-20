#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define Safe 1

#if Safe
#define WarningText
#include "2_safe_stack.c"
#else
#define WarningText "(UNSAFE) "
#include "2_unsafe_stack.c"
#endif

enum {
    NumThreads = 5,
    NumInserts = 10000,
};

typedef struct {
    pthread_t ThreadId;
    stack *Stack;
    char *StringToInsert;
    int IntegerToInsert;
    int Count;
} thread_info;

void *threadInsert(void *RawArg) {
    thread_info *Info = (thread_info *)RawArg;

    for(int Idx = 0; Idx < Info->Count; ++Idx) {
        push(Info->Stack, Info->IntegerToInsert, Info->StringToInsert);
    }

    return 0;
}

void *threadRemove(void *RawArg) {
    thread_info *Info = (thread_info *)RawArg;

    for(int Idx = 0; Idx < Info->Count; ++Idx) {
        pop(Info->Stack);
    }

    return 0;
}

int main() {
    stack Stack;
    init(&Stack);

    printf("== Single-thread test ==\n");
    push(&Stack,   1, "Ahhh");
    push(&Stack, 123, "Hello");
    push(&Stack,  20, "Adios");
    push(&Stack,  78, ":D");
    push(&Stack,   9, ":(");

    show(&Stack);
    puts("");

    pop(&Stack);
    pop(&Stack);
    push(&Stack,  12, "Ahah");
    push(&Stack,   0, ":3");

    show(&Stack);


    clear(&Stack);
    printf("\n== Multi-thread test " WarningText "==\n");
    thread_info Threads[NumThreads];
    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_info *Info = Threads + Idx;

        Info->Stack = &Stack;
        Info->StringToInsert = "Thread";
        Info->IntegerToInsert = Idx;
        Info->Count = NumInserts;

        pthread_create(&Info->ThreadId, 0, threadInsert, Info);
    }

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_info *Info = Threads + Idx;
        pthread_join(Info->ThreadId, 0);
    }

    long int ActualCount = count(&Stack);
    printf("Stack count: %ld (expected %ld)\n", ActualCount, (long int)(NumThreads*NumInserts));

    int ToRemove = ActualCount / NumThreads;
    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_info *Info = Threads + Idx;

        Info->Stack = &Stack;
        Info->Count = ToRemove;

        pthread_create(&Info->ThreadId, 0, threadRemove, Info);
    }

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_info *Info = Threads + Idx;
        pthread_join(Info->ThreadId, 0);
    }

    printf("Stack count: %ld (expected %ld)\n", count(&Stack), ActualCount - NumThreads*ToRemove);

    return 0;
}
