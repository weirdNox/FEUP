#include "heap.h"

#include <stdlib.h>

#define HEAP_ROOT (0)
#define HEAP_PARENT(x) ((x-1)/2)
#define HEAP_LEFT_CHILD(x) ((x*2)+1)
#define HEAP_RIGHT_CHILD(x) ((x*2)+2)

HEAP_COMPARE_FUNCTION(heapCompareLess)
{
    return a < b;
}

HEAP_COMPARE_FUNCTION(heapCompareGreater)
{
    return a > b;
}

Heap *newHeap(int capacity, HeapCompareFunction compareFunction)
{
    if(capacity < 1)
    {
        return 0;
    }

    Heap *heap = malloc(sizeof(*heap));
    if(heap)
    {
        heap->size = 0;
        heap->capacity = capacity;
        heap->compareFunction = compareFunction;
        heap->elements = malloc(capacity*sizeof(int));
        if(!heap->elements)
        {
            free(heap);
            heap = 0;
        }
    }

    return heap;
}

void freeHeap(Heap *heap)
{
    if(!heap)
    {
        return;
    }

    free(heap->elements);
    free(heap);
    return;
}

int heapInsert(Heap *heap, int n)
{
    if(!heap || n < 0 || heap->size == heap->capacity)
    {
        return 0;
    }

    int position = heap->size++;
    while(position != HEAP_ROOT)
    {
        int parentPos = HEAP_PARENT(position);
        if(heap->compareFunction(n, heap->elements[parentPos]))
        {
            heap->elements[position] = heap->elements[parentPos];
            position = parentPos;
        }
        else
        {
            break;
        }
    }

    heap->elements[position] = n;
    return 1;
}

int heapPop(Heap *heap)
{
    if(!heap || heap->size <= 0)
    {
        return -1;
    }

    int returnValue = heap->elements[HEAP_ROOT];
    int n = heap->elements[--heap->size];

    int position = 0;
    while(HEAP_LEFT_CHILD(position) < heap->size)
    {
        int nextCandidate = HEAP_LEFT_CHILD(position);
        if(HEAP_RIGHT_CHILD(position) < heap->size &&
           heap->compareFunction(heap->elements[HEAP_RIGHT_CHILD(position)],
                                 heap->elements[HEAP_LEFT_CHILD(position)]))
        {
            nextCandidate = HEAP_RIGHT_CHILD(position);
        }

        if(heap->compareFunction(heap->elements[nextCandidate], n))
        {
            heap->elements[position] = heap->elements[nextCandidate];
            position = nextCandidate;
        }
        else
        {
            break;
        }
    }
    heap->elements[position] = n;

    return returnValue;
}
