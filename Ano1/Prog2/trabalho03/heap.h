#if !defined(HEAP_H)

#define HEAP_ROOT 1

// NOTE(nox): For performance reasons,  max and min heaps are the same thing  and it is up
// to the user to enforce that their respective functions are used accordingly!!
typedef struct
{
    int size;
    int capacity;
    int *elements;
} Heap;

typedef Heap MinHeap;
typedef Heap MaxHeap;

// Allocate and initialize Heap dynamically
// capacity has to be greater than 0
// Returns pointer to created Heap or null on error
Heap *newHeap(int capacity);

// Free Heap
void freeHeap(Heap *heap);

// Insert new item to heap
// Returns 0 on failure, and 1 on success
int minHeapInsert(MinHeap *heap, int n);
int maxHeapInsert(MaxHeap *heap, int n);

// Remove top of heap and return it
// Returns -1 on error
int minHeapPop(MinHeap *heap);
int maxHeapPop(MaxHeap *heap);

#define HEAP_H
#endif
