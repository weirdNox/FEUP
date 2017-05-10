#if !defined(HEAP_H)

#define HEAP_COMPARE_FUNCTION(name) int name(int a, int b)
typedef HEAP_COMPARE_FUNCTION(HeapCompareFunction);

HEAP_COMPARE_FUNCTION(heapCompareLess);
HEAP_COMPARE_FUNCTION(heapCompareGreater);

typedef struct
{
    HeapCompareFunction *compareFunction;
    int size;
    int capacity;
    int *elements;
} Heap;

Heap *newHeap(int capacity, HeapCompareFunction compareFunction);
void freeHeap(Heap *heap);

// NOTE(nox): Returns 0 on failure, and 1 on success
int heapInsert(Heap *heap, int n);
int heapPop(Heap *heap);

#define HEAP_H
#endif
