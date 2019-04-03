#include <stdlib.h>

typedef struct {
    char *String;
    int Number;
} stack_element;

typedef struct {
    stack_element *Data;
    size_t Capacity;
    size_t Length;
    pthread_mutex_t Mutex;
} stack;

void init(stack *Stack, size_t Capacity) {
    Stack->Data = malloc(Capacity*sizeof(*Stack->Data));
    Stack->Capacity = Capacity;
    Stack->Length = 0;
    pthread_mutex_init(&Stack->Mutex, 0);
}

stack_element *push(stack *Stack, int Number, char *String) {
    size_t NewIdx = 0;

    int HasAvailableSpace = 0;
    while(!HasAvailableSpace) {
        if(Stack->Length < Stack->Capacity) {
            pthread_mutex_lock(&Stack->Mutex);
            if(Stack->Length < Stack->Capacity) {
                NewIdx = Stack->Length++;
                HasAvailableSpace = 1;
            }
            pthread_mutex_unlock(&Stack->Mutex);
        }
    }

    stack_element *NewElement = Stack->Data + NewIdx;
    *NewElement = (stack_element){
        .String = String,
        .Number = Number,
    };

    return NewElement;
}

void pop(stack *Stack) {
    int HasElementToPop = 0;
    while(!HasElementToPop) {
        if(Stack->Length) {
            pthread_mutex_lock(&Stack->Mutex);
            if(Stack->Length) {
                --Stack->Length;
                HasElementToPop = 1;
            }
            pthread_mutex_unlock(&Stack->Mutex);
        }
    }
}

void show(stack *Stack) {
    pthread_mutex_lock(&Stack->Mutex);
    printf("Stack contents:\n");
    for(size_t Idx = 0; Idx < Stack->Length; ++Idx) {
        stack_element *Element = Stack->Data + Idx;
        printf("%3ld: %s %d\n", Idx, Element->String, Element->Number);
    }
    pthread_mutex_unlock(&Stack->Mutex);
}

void clear(stack *Stack) {
    pthread_mutex_lock(&Stack->Mutex);
    Stack->Length = 0;
    pthread_mutex_unlock(&Stack->Mutex);
}
