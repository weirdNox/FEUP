#if !defined(HASH_H)

typedef struct HashElement
{
    char companyName[20];
    int numberOfTransactions;
} HashElement;

// Open addressed Hash Table
typedef struct
{
    HashElement **buckets;
    long int size;
} HashTable;

// Initializes Hash Table passed by pointer
// If table is already initialized, won't do anything
// Return 0 on error, 1 on success
int initHashTable(HashTable *table, long int size);

// Free table buckets
// Will set table members to null on success
void freeHashTable(HashTable *table);

// Fetch table element by name, or create it if it doesn't exist
// Return null on error or the element on success
HashElement *hashTableFetch(HashTable *table, char *name);

#define HASH_H
#endif