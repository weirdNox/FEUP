#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int initHashTable(HashTable *table, long int maxFilled)
{
    if(!table || maxFilled <= 0 || table->buckets)
    {
        return 0;
    }

    table->usedEntries = 0;
    table->availableSpace = maxFilled;
    table->entriesMemory = calloc(table->availableSpace, sizeof(*table->entriesMemory));

    // NOTE(nox): We want to keep a maximum load factor of 60%
    table->numBuckets = maxFilled / 0.6f;
    table->buckets = calloc(table->numBuckets, sizeof(*table->buckets));
    if(!table->entriesMemory || !table->buckets)
    {
        free(table->buckets);
        free(table->entriesMemory);
        *table = (HashTable){};
        return 0;
    }

    return 1;
}

void freeHashTable(HashTable *table)
{
    if(!table || !table->buckets)
    {
        return;
    }

    free(table->entriesMemory);
    free(table->buckets);

    *table = (HashTable){};
}

HashElement *hashTableFetch(HashTable *table, char *name)
{
    if(!table || !table->buckets || !name)
    {
        return 0;
    }

    // NOTE(nox): DJB2
    unsigned char *str = (unsigned char *)name;
    uint32_t hash = 5381;
    uint8_t c;
    while((c = *(str++)))
    {
        hash = hash * 33 + c;
    }
    hash %= table->numBuckets;

    HashElement *result;
    for(;;)
    {
        result = table->buckets[hash];

        if(!result)
        {
            if(table->usedEntries < table->availableSpace)
            {
                result = table->buckets[hash] = table->entriesMemory + table->usedEntries++;
                strcpy(result->companyName, name);
            }

            break;
        }
        else if(strcmp(result->companyName, name) == 0)
        {
            break;
        }

        hash = (hash + 1) % table->numBuckets;
    }

    return result;
}
