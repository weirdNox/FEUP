#if !defined(HASH_H)

#include <stdint.h>

typedef struct HashElement
{
    int numberOfTransactions;
    char companyName[16];
} HashElement;

// Open addressed Hash Table
// It will  have some  available space  and a bigger  number of  buckets, however,  if the
// number of  used entries gets to  available space, no more  entries can be added  to the
// hash table, even with empty buckets. This serves to enforce the ~70-80% load factor.
// Also, even when full, there will be unused memory, but it was designed with performance
// in mind.
typedef struct
{
    HashElement *buckets;
    uint32_t usedEntries;
    uint32_t availableSpace;
    uint32_t numBuckets;
    uint32_t moduloMask;
} HashTable;

// Initializes Hash Table passed by pointer
// If table is already initialized, won't do anything
// Return 0 on error, 1 on success
int initHashTable(HashTable *table, uint32_t size);

// Free table buckets
// Will set struct members to null on success
void freeHashTable(HashTable *table);

// Fetch table element by name, or create it if it doesn't exist
// Return null on error or the element on success
HashElement *hashTableFetch(HashTable *table, char *name);

#define HASH_H
#endif
