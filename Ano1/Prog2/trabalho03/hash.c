#include "hash.h"
#include <stdlib.h>
#include <string.h>

unsigned long sdbm(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

HashTable *newHashTable()
{
    HashTable *result = calloc(1, sizeof(*result));
    return result;
}

HashElement *hashTableFetch(HashTable *table, char *name)
{
    if(!table || !name)
    {
        return 0;
    }

    int hash = sdbm((unsigned char *)name) % NUM_BUCKETS;
    HashElement **resultPtr = table->buckets + hash;

    for(;;)
    {
        HashElement *result = *resultPtr;

        if(!result)
        {
            result = (*resultPtr) = calloc(1, sizeof(HashElement));
            if(result)
            {
                result->next = 0;
                result->numberOfTransactions = 0;
                strcpy(result->companyName, name);
            }

            break;
        }
        else if(strcmp(result->companyName, name) == 0)
        {
            break;
        }

        resultPtr = &result->next;
    }

    return *resultPtr;
}

void freeHashTable(HashTable *table)
{
    if(!table)
    {
        return;
    }

    for(int i = 0; i < NUM_BUCKETS; ++i)
    {
        HashElement *el = table->buckets[i];
        while(el)
        {
            HashElement *temp = el->next;
            free(el);
            el = temp;
        }
    }
    free(table);
}
