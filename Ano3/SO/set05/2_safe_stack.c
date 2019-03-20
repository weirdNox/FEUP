typedef struct stack_element {
    struct stack_element *Next;
    char *String;
    int Integer;
} stack_element;

typedef struct {
    pthread_mutex_t Mutex;
    stack_element *First;
} stack;

void init(stack *Stack) {
    pthread_mutex_init(&Stack->Mutex, 0);
    Stack->First = 0;
}

void push(stack *Stack, int Integer, char *String) {
    stack_element *Element = malloc(sizeof(*Element));

    pthread_mutex_lock(&Stack->Mutex);
    Element->Next = Stack->First;
    Stack->First = Element;
    pthread_mutex_unlock(&Stack->Mutex);

    Element->String = String;
    Element->Integer = Integer;
}

void pop(stack *Stack) {
    pthread_mutex_lock(&Stack->Mutex);
    stack_element *Element = Stack->First;
    Stack->First = Element->Next;
    pthread_mutex_unlock(&Stack->Mutex);

    free(Element);
}

void clear(stack *Stack) {
    pthread_mutex_lock(&Stack->Mutex);
    stack_element *Element = Stack->First;
    Stack->First = 0;
    pthread_mutex_unlock(&Stack->Mutex);

    while(Element) {
        stack_element *NextElement = Element->Next;
        free(Element);
        Element = NextElement;
    }
}

void show(stack *Stack) {
    printf("Stack:\n");

    pthread_mutex_lock(&Stack->Mutex);
    for(stack_element *Element = Stack->First; Element; Element = Element->Next) {
        printf(" %s %d\t%s\n", Element->Next ? "├" : "└", Element->Integer, Element->String);
    }
    pthread_mutex_unlock(&Stack->Mutex);
}

long int count(stack *Stack) {
    long int Result = 0;

    pthread_mutex_lock(&Stack->Mutex);
    for(stack_element *Element = Stack->First; Element; Element = Element->Next) {
        ++Result;
    }
    pthread_mutex_unlock(&Stack->Mutex);

    return Result;
}
