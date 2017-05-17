#include "hash.h"
#include <stdlib.h>
#include <string.h>

unsigned long sdbm(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

int initHashTable(HashTable *table, long int size)
{
    if(!table || size <= 0 || table->buckets)
    {
        return 0;
    }

    table->buckets = calloc(size, sizeof(*table->buckets));
    if(table->buckets)
    {
        table->size = size;
        return 1;
    }

    table->size = 0;
    return 0;
}

void freeHashTable(HashTable *table)
{
    if(!table || !table->buckets)
    {
        return;
    }

    for(int i = 0; i < table->size; ++i)
    {
        free(table->buckets[i]);
    }
    free(table->buckets);

    table->size = 0;
    table->buckets = 0;
}

HashElement *hashTableFetch(HashTable *table, char *name)
{
    if(!table || !table->buckets || !name)
    {
        return 0;
    }

    int hash = sdbm((unsigned char *)name) % table->size;

    for(;;)
    {
        HashElement *result = table->buckets[hash];

        if(!result)
        {
            result = table->buckets[hash] = calloc(1, sizeof(HashElement));
            if(result)
            {
                strcpy(result->companyName, name);
            }

            break;
        }
        else if(strcmp(result->companyName, name) == 0)
        {
            break;
        }

        hash = (hash + 1) % table->size;
    }

    return table->buckets[hash];
}
