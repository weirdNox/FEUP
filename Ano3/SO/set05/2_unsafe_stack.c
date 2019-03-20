typedef struct stack_element {
    struct stack_element *Next;
    char *String;
    int Integer;
} stack_element;

typedef struct {
    stack_element *First;
} stack;

void init(stack *Stack) {
    Stack->First = 0;
}

void push(stack *Stack, int Integer, char *String) {
    stack_element *Element = malloc(sizeof(*Element));

    Element->Next = Stack->First;
    Element->String = String;
    Element->Integer = Integer;

    Stack->First = Element;
}

void pop(stack *Stack) {
    stack_element *Element = Stack->First;
    Stack->First = Element->Next;
    free(Element);
}

void clear(stack *Stack) {
    for(stack_element *Element = Stack->First; Element;) {
        stack_element *NextElement = Element->Next;
        free(Element);
        Element = NextElement;
    }
    Stack->First = 0;
}

void show(stack *Stack) {
    printf("Stack:\n");
    for(stack_element *Element = Stack->First; Element; Element = Element->Next) {
        printf(" %s %d\t%s\n", Element->Next ? "├" : "└", Element->Integer, Element->String);
    }
}

long int count(stack *Stack) {
    long int Result = 0;
    for(stack_element *Element = Stack->First; Element; Element = Element->Next) {
        ++Result;
    }

    return Result;
}
