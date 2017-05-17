#if !defined(HEAP_H)

#define HEAP_COMPARE_FUNCTION(name) int name(int a, int b)
typedef HEAP_COMPARE_FUNCTION(HeapCompareFunction);

HeapCompareFunction heapCompareLess;
HeapCompareFunction heapCompareGreater;

typedef struct
{
    HeapCompareFunction *compareFunction;
    int size;
    int capacity;
    int *elements;
} Heap;

// Allocate and initialize Heap dynamically
// capacity has to be greater than 0
// Returns pointer to created Heap or null on error
Heap *newHeap(int capacity, HeapCompareFunction compareFunction);

// Free Heap
void freeHeap(Heap *heap);

// Insert new item to heap
// Returns 0 on failure, and 1 on success
int heapInsert(Heap *heap, int n);

// Remove top of heap and return it
// Returns -1 on error
int heapPop(Heap *heap);

#define HEAP_H
#endif
