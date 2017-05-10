#if !defined(HASH_H)

#define NUM_BUCKETS 2097152 // NOTE(nox): 2^21

typedef struct HashElement
{
    char companyName[20];
    int numberOfTransactions;
    struct HashElement *next;
} HashElement;

typedef struct
{
    HashElement *buckets[NUM_BUCKETS];
} HashTable;

HashTable *newHashTable();
void freeHashTable(HashTable *table);

HashElement *hashTableFetch(HashTable *table, char *name);

#define HASH_H
#endif
