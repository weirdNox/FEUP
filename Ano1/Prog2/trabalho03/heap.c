#include "heap.h"

#include <stdlib.h>

#define HEAP_PARENT(x) ((x)/2)
#define HEAP_LEFT_CHILD(x) ((x)*2)
#define HEAP_RIGHT_CHILD(x) ((x)*2+1)

Heap *newHeap(int capacity)
{
    if(capacity <= 0)
    {
        return 0;
    }

    Heap *heap = malloc(sizeof(*heap));
    if(heap)
    {
        heap->size = 0;
        heap->capacity = capacity;
        heap->elements = malloc((capacity+1)*sizeof(int));
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

int minHeapInsert(Heap *heap, int n)
{
    if(!heap || n < 0 || heap->size == heap->capacity)
    {
        return 0;
    }

    int position = ++heap->size;
    while(position != HEAP_ROOT)
    {
        int parentPos = HEAP_PARENT(position);
        if(n < heap->elements[parentPos])
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

int minHeapPop(Heap *heap)
{
    if(!heap || heap->size <= 0)
    {
        return -1;
    }

    int returnValue = heap->elements[HEAP_ROOT];
    int n = heap->elements[heap->size--];

    int position = HEAP_ROOT;
    int leftPos;
    while((leftPos = HEAP_LEFT_CHILD(position)) <= heap->size)
    {
        int rightPos = HEAP_RIGHT_CHILD(position);

        int nextCandidate;
        if(rightPos <= heap->size &&
           heap->elements[rightPos] < heap->elements[leftPos])
        {
            nextCandidate = rightPos;
        }
        else
        {
            nextCandidate = leftPos;
        }

        if(heap->elements[nextCandidate] < n)
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

int maxHeapInsert(Heap *heap, int n)
{
    if(!heap || n < 0 || heap->size == heap->capacity)
    {
        return 0;
    }

    int position = ++heap->size;
    while(position != HEAP_ROOT)
    {
        int parentPos = HEAP_PARENT(position);
        if(n > heap->elements[parentPos])
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

int maxHeapPop(Heap *heap)
{
    if(!heap || heap->size <= 0)
    {
        return -1;
    }

    int returnValue = heap->elements[HEAP_ROOT];
    int n = heap->elements[heap->size--];

    int position = HEAP_ROOT;
    int leftPos;
    while((leftPos = HEAP_LEFT_CHILD(position)) <= heap->size)
    {
        int rightPos = HEAP_RIGHT_CHILD(position);

        int nextCandidate;
        if(rightPos <= heap->size &&
           heap->elements[rightPos] > heap->elements[leftPos])
        {
            nextCandidate = rightPos;
        }
        else
        {
            nextCandidate = leftPos;
        }

        if(heap->elements[nextCandidate] > n)
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
