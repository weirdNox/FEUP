#include <assert.h>
#include <pthread.h>
#include <stdio.h>

#define Safe 2

#if   Safe==1
#define WarningText "SAFE BUSY WAIT"
#include "safe_stack.c"
#elif Safe==2
#define WarningText "SAFE CONDITION VARIABLES"
#include "safe_cond_stack.c"
#else
#define WarningText "UNSAFE"
#include "unsafe_stack.c"
#endif

enum {
    StackSize = 100,
    NumInserts = 10000,
    NumThreadPairs = 3,
    NumThreads = NumThreadPairs*2,
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
    init(&Stack, StackSize);

    printf("== Single-thread test - "WarningText" ==\n");
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
    for(size_t Idx = 0; Idx < Stack.Capacity; ++Idx) {
        stack_element *Element = push(&Stack,  12, "FILLER!");
        assert(Element);
    }

    clear(&Stack);
    printf("\n== Multi-thread test - " WarningText " ==\n");
    thread_info Threads[NumThreads];
    for(int Idx = 0, Consumer = 0; Idx < NumThreads; ++Idx, Consumer = !Consumer) {
        thread_info *Info = Threads + Idx;

        Info->Stack = &Stack;
        Info->StringToInsert = "Thread";
        Info->IntegerToInsert = Idx;
        Info->Count = NumInserts;

        pthread_create(&Info->ThreadId, 0, Consumer ? threadRemove : threadInsert, Info);
    }

    for(int Idx = 0; Idx < NumThreads; ++Idx) {
        thread_info *Info = Threads + Idx;
        pthread_join(Info->ThreadId, 0);
    }

    printf("Done! Stack count: %ld (expected: 0)\n", Stack.Length);

    return 0;
}
