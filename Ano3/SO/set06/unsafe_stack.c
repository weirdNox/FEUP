#include <stdlib.h>

typedef struct {
    char *String;
    int Number;
} stack_element;

typedef struct {
    stack_element *Data;
    size_t Capacity;
    size_t Length;
} stack;

void init(stack *Stack, size_t Capacity) {
    Stack->Data = malloc(Capacity*sizeof(*Stack->Data));
    Stack->Capacity = Capacity;
    Stack->Length = 0;
}

stack_element *push(stack *Stack, int Number, char *String) {
    stack_element *NewElement = 0;

    if(Stack->Length < Stack->Capacity) {
        size_t NewIdx = Stack->Length++;

        Stack->Data[NewIdx] = (stack_element){
            .String = String,
            .Number = Number,
        };

        NewElement = Stack->Data + NewIdx;
    }

    return NewElement;
}

// NOTE(nox): The returned pointer is only guaranteed be valid until the next stack modification
stack_element *pop(stack *Stack) {
    stack_element *Element = 0;

    if(Stack->Length) {
        size_t ElementIdx = --Stack->Length;
        Element = Stack->Data + ElementIdx;
    }

    return Element;
}

void show(stack *Stack) {
    printf("Stack contents:\n");
    for(size_t Idx = 0; Idx < Stack->Length; ++Idx) {
        stack_element *Element = Stack->Data + Idx;
        printf("%3ld: %s %d\n", Idx, Element->String, Element->Number);
    }
}

void clear(stack *Stack) {
    Stack->Length = 0;
}
