#include "modules.h"
#include "heap.h"
#include "hash.h"

#include <stdlib.h>
#include <string.h>

// NOTE(nox): Median
Heap *leftHeap;
Heap *rightHeap;

// NOTE(nox): Each heap will keep half (+/- 1)  of the transactions, the left one is a max
// heap and it  will keep the lower end of  the number list, and the right  one a min heap
// and it will keep the upper end.

void median_initModule(int maxTransactions)
{
    leftHeap = newHeap(maxTransactions/2+1, heapCompareGreater);
    rightHeap = newHeap(maxTransactions/2+1, heapCompareLess);
    if(!leftHeap || !rightHeap)
    {
        free(leftHeap); leftHeap = 0;
        free(rightHeap); rightHeap = 0;
    }
}

int median_newObservation(int numActions, float *updatedMedian)
{
    if(!leftHeap || !rightHeap || !updatedMedian)
    {
        return -1;
    }

    // NOTE(nox): When  inserting, we will check  which one has  more or if they  have the
    // same number of items - the possible balance result is -1, 0 and 1.
    int balance = rightHeap->size - leftHeap->size;
    switch(balance)
    {
        case -1:
        {
            // NOTE(nox): Left heap has one more item and the current median is its top
            if(numActions < *updatedMedian)
            {
                // NOTE(nox): If less than the median, move  top of left heap to the right
                // and put the new item on the left (new item < top of left)
                // Also, we don't need to check if  the pop returns an error because it is
                // certain that it has at least one item
                if(!heapInsert(rightHeap, heapPop(leftHeap)) ||
                   !heapInsert(leftHeap, numActions))
                {
                    return -1;
                }
            }
            else
            {
                // NOTE(nox): If it is greater or equal, put it on the right
                // (new item >= top of left)
                if(!heapInsert(rightHeap, numActions))
                {
                    return -1;
                }
            }

            // NOTE(nox): The two heaps will be balanced in the end, so the new median is
            // the average
            *updatedMedian = (float)(leftHeap->elements[0] + rightHeap->elements[0]) / 2.0f;
        } break;

        case 0:
        {
            // NOTE(nox): Heaps are balanced, we can just  insert the new item on the left
            // if it is  less than the median or  on the right if it is  greater or equal.
            // The resulting  median is the  top of  the heap where  we put the  new item,
            // because it now has 1 more item than the other.
            if(numActions < *updatedMedian)
            {
                if(!heapInsert(leftHeap, numActions))
                {
                    return -1;
                }
                *updatedMedian = leftHeap->elements[0];
            }
            else
            {
                if(!heapInsert(rightHeap, numActions))
                {
                    return -1;
                }
                *updatedMedian = rightHeap->elements[0];
            }
        } break;

        case 1:
        {
            // NOTE(nox): Analogous to case -1.
            if(numActions > *updatedMedian)
            {
                if(!heapInsert(leftHeap, heapPop(rightHeap)) ||
                   !heapInsert(rightHeap, numActions))
                {
                    return -1;
                }
            }
            else
            {
                if(!heapInsert(leftHeap, numActions))
                {
                    return -1;
                }
            }

            *updatedMedian = (float)(leftHeap->elements[0] + rightHeap->elements[0]) / 2.0f;
        } break;

        default:
        {
            return -1;
        } break;
    }

    return 1;
}

void median_closeModule()
{
    freeHeap(leftHeap); leftHeap = 0;
    freeHeap(rightHeap); rightHeap = 0;
}


// NOTE(nox): Mode
HashTable table;
HashElement *best;

void mode_initModule(int maxTransactions)
{
    initHashTable(&table, maxTransactions);
    best = 0;
}

int mode_newObservation(const char *companyName, char *updatedMode)
{
    if(!updatedMode)
    {
        return -1;
    }

    // NOTE(nox): This  observation is very  simple to do, just  get the company  from the
    // table, add 1 to  transactions and check if it is more  than most transactions until
    // now. If yes, update stats and done.
    HashElement *company = hashTableFetch(&table, (char*)companyName);
    if(!company)
    {
        return -1;
    }

    ++company->numberOfTransactions;
    if(!best || (company != best &&
                 company->numberOfTransactions > best->numberOfTransactions))
    {
        best = company;
        strcpy(updatedMode, company->companyName);
    }

    return 1;
}

void mode_closeModule()
{
    freeHashTable(&table);
}
