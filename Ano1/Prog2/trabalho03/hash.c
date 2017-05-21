#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int initHashTable(HashTable *table, uint32_t maxFilled)
{
    if(!table || maxFilled == 0 || maxFilled > INT32_MAX || table->buckets)
    {
        return 0;
    }

    // NOTE(nox): We want to keep a maximum load factor of 80%
    uint32_t numBuckets = maxFilled / 0.8f;
    if(numBuckets > INT32_MAX)
    {
        numBuckets = 0x80000000;
    }
    else
    {
        // NOTE(nox): Round to next power of two
        numBuckets -= 1;
        numBuckets |= numBuckets >> 1;
        numBuckets |= numBuckets >> 2;
        numBuckets |= numBuckets >> 4;
        numBuckets |= numBuckets >> 8;
        numBuckets |= numBuckets >> 16;
        numBuckets++;
    }

    table->usedEntries = 0;
    table->availableSpace = maxFilled;
    table->numBuckets = numBuckets;
    table->moduloMask = numBuckets-1;
    table->buckets = calloc(table->numBuckets, sizeof(*table->buckets));
    if(!table->buckets)
    {
        free(table->buckets);
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
    hash &= table->moduloMask;

    HashElement *result;
    for(;;)
    {
        result = table->buckets + hash;

        if(result->companyName[0] == '\0')
        {
            if(table->usedEntries < table->availableSpace)
            {
                ++table->usedEntries;
                strcpy(result->companyName, name);
            }
            else
            {
                result = 0;
            }

            break;
        }
        else if(strcmp(result->companyName, name) == 0)
        {
            break;
        }

        hash = (hash + 1) & table->moduloMask;
    }

    return result;
}
