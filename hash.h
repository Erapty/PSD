#ifndef HASH_H
#define HASH_H

// Number of buckets in the hash table
#define TABLE_SIZE 101

// Opaque declaration of the HashTable structure
typedef struct HashTable HashTable;

/*
 * Creates and initializes a new hash table.
 *
 * returns: pointer to the new HashTable
 */
HashTable* createHashTable();

/*
 * Hash function to compute an index from a string key.
 *
 * key: the input string
 *
 * returns: the corresponding index in the hash table
 */
unsigned int hashFunction(const char* key);

/*
 * Inserts a key-value pair into the hash table.
 *
 * ht: pointer to the hash table
 * key: the string key
 * value: generic pointer to the value
 */
void insertHashTable(HashTable* ht, const char* key, void* value);

/*
 * Searches for a value in the hash table using the given key.
 *
 * ht: pointer to the hash table
 * key: the string key to search for
 *
 * returns: pointer to the value if found, NULL otherwise
 */
void* searchHashTable(HashTable* ht, const char* key);

/*
 * Deletes a key-value pair from the hash table.
 *
 * ht: pointer to the hash table
 * key: the string key to delete
 */
void deleteHashTable(HashTable* ht, const char* key);

/*
 * Frees all memory associated with the hash table.
 *
 * ht: pointer to the hash table
 */
void freeHashTable(HashTable* ht);

#endif
