#include "modules.h"
#include "heap.h"
#include "hash.h"

#include <stdlib.h>
#include <string.h>

Heap *rightHeap;
Heap *leftHeap;

void median_initModule(int maxTransactions)
{
    leftHeap = newHeap(maxTransactions/2+3, heapCompareGreater);
    rightHeap = newHeap(maxTransactions/2+3, heapCompareLess);
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

    int balance = rightHeap->size - leftHeap->size;
    switch(balance)
    {
        case -1:
        {
            if(numActions < *updatedMedian)
            {
                heapInsert(rightHeap, heapPop(leftHeap));
                heapInsert(leftHeap, numActions);
            }
            else
            {
                heapInsert(rightHeap, numActions);
            }
            *updatedMedian = (float)(leftHeap->elements[0] + rightHeap->elements[0]) / 2.0f;
        } break;

        case 0:
        {
            if(numActions < *updatedMedian)
            {
                heapInsert(leftHeap, numActions);
                *updatedMedian = leftHeap->elements[0];
            }
            else
            {
                heapInsert(rightHeap, numActions);
                *updatedMedian = rightHeap->elements[0];
            }
        } break;

        case 1:
        {
            if(numActions < *updatedMedian)
            {
                heapInsert(leftHeap, numActions);
            }
            else
            {
                heapInsert(leftHeap, heapPop(rightHeap));
                heapInsert(rightHeap, numActions);
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


HashTable *table;
int mostTransactions;
void mode_initModule(int maxTransactions)
{
    table = newHashTable();
    mostTransactions = 0;
}

int mode_newObservation(const char *companyName, char *updatedMode)
{
    if(!table || !companyName || !updatedMode)
    {
        return -1;
    }

    HashElement *company = hashTableFetch(table, (char*)companyName);
    if(!company)
    {
        return -1;
    }

    if(++company->numberOfTransactions > mostTransactions)
    {
        mostTransactions = company->numberOfTransactions;
        strcpy(updatedMode, company->companyName);
    }

    return 1;
}

void mode_closeModule()
{
    freeHashTable(table); table = 0;
}
