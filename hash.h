#ifndef HASH_H
#define HASH_H

#define TABLE_SIZE 101

typedef struct HashTable HashTable;

/*
 * Creates and initializes a new hash table.
 */
HashTable* createHashTable();

/*
 * Inserts a key-value pair into the hash table.
 */
void insertHashTable(HashTable* table, const char* key, void* value);

/*
 * Searches for a value by its key in the hash table.
 */
void* searchHashTable(HashTable* table, const char* key);

/*
 * Deletes a key and its associated value from the hash table.
 */
void deleteHashTable(HashTable* table, const char* key);

/*
 * Frees the memory used by the hash table.
 */
void freeHashTable(HashTable* table);

/*
 * Iterates over all key-value pairs in the hash table,
 * calling the provided callback on each.
 *
 * ht: pointer to the hash table
 * callback: function to be called for each pair
 * userData: additional data passed to the callback
 */
void forEachHash(HashTable* ht, void (*callback)(const char* key, void* value, void* userData), void* userData);

#endif
