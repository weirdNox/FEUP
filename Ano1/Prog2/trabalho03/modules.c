#include "modules.h"
#include "heap.h"
#include "hash.h"

#include <stdlib.h>
#include <string.h>

// NOTE(nox): Median
MaxHeap *leftHeap;
MinHeap *rightHeap;

// NOTE(nox): Each heap will keep half (+/- 1)  of the transactions, the left one is a max
// heap and it  will keep the lower end of  the number list, and the right  one a min heap
// and it will keep the upper end.

void median_initModule(int maxTransactions)
{
    leftHeap = newHeap(maxTransactions/2+3);
    rightHeap = newHeap(maxTransactions/2+3);
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

    int balance;

    // NOTE(nox): Insert number where it belongs
    if(numActions < *updatedMedian)
    {
        if(!maxHeapInsert(leftHeap, numActions))
        {
            return -1;
        }

        // NOTE(nox): After inserting in the left heap, there are three possible outcomes:
        //  1) Balance =  0
        //  2) Balance = -1
        //  3) Balance < -1
        // If it is  possibility 3), we have  to rebalance, removing 1 from  the left heap
        // and putting it in  the right one, so balance becomes 0. So,  the median from 1)
        // and 3) will be the average of the middle items.
        // If it is possibility 2), we don't have to rebalance, and the median will be the
        // top of the left heap.
        balance = rightHeap->size - leftHeap->size;
        if(balance < -1)
        {
            if(!minHeapInsert(rightHeap, maxHeapPop(leftHeap)))
            {
                return -1;
            }
        }
        else if(balance == -1)
        {
            // NOTE(nox): Possibility 2)
            *updatedMedian = leftHeap->elements[HEAP_ROOT];
            return 1;
        }

        // NOTE(nox): Possibility 1) and 3)
        *updatedMedian = (float)(leftHeap->elements[HEAP_ROOT] +
                                 rightHeap->elements[HEAP_ROOT]) / 2.0f;
        return 1;
    }
    else if(numActions > *updatedMedian)
    {
        if(!minHeapInsert(rightHeap, numActions))
        {
            return -1;
        }

        balance = rightHeap->size - leftHeap->size;
        if(balance > 1)
        {
            if(!maxHeapInsert(leftHeap, minHeapPop(rightHeap)))
            {
                return -1;
            }
        }
        else if(balance == 1)
        {
            *updatedMedian = rightHeap->elements[HEAP_ROOT];
            return 1;
        }

        *updatedMedian = (float)(leftHeap->elements[HEAP_ROOT] +
                                 rightHeap->elements[HEAP_ROOT]) / 2.0f;
        return 1;
    }
    else
    {
        // NOTE(nox): If it is the same as the current median, put it in the heap with
        // less items
        if(leftHeap->size > rightHeap->size)
        {
            if(!minHeapInsert(rightHeap, numActions))
            {
                return -1;
            }
        }
        else
        {
            if(!maxHeapInsert(leftHeap, numActions))
            {
                return -1;
            }
        }

        return 1;
    }
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
