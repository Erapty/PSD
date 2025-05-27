#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/*
 * File: hash.c
 * ------------
 * Implements a simple hash table using separate chaining for collision handling.
 * Allows insertion, search, deletion, and cleanup of key-value pairs, where the key is a string.
 */

// Structure representing a node in a hash table bucket
typedef struct HashNode {
    char* key;
    void* value;
    struct HashNode* next;
} HashNode;

// Structure representing the hash table
struct HashTable {
    HashNode* table[TABLE_SIZE];
};

/*
 * Function: hashFunction
 * ----------------------
 * Computes the hash value of a string key using a basic polynomial rolling hash.
 *
 * key: the input string
 *
 * returns: index in the hash table
 */
unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;  // hash * 32 + current char
    }
    return hash % TABLE_SIZE;
}

/*
 * Function: createHashTable
 * -------------------------
 * Allocates and initializes a new hash table.
 *
 * returns: pointer to the new HashTable
 */
HashTable* createHashTable() {
    HashTable* ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

/*
 * Function: insertHashTable
 * -------------------------
 * Inserts a key-value pair into the hash table.
 * If collisions occur, the new node is added to the front of the chain.
 *
 * ht: pointer to the hash table
 * key: string key
 * value: associated value (generic pointer)
 */
void insertHashTable(HashTable* ht, const char* key, void* value) {
    unsigned int index = hashFunction(key);

    HashNode* node = malloc(sizeof(HashNode));
    if (!node) return;

    node->key = strdup(key);  // oppure: my_strdup(key)
    node->value = value;
    node->next = ht->table[index];
    ht->table[index] = node;
}


/*
 * Function: searchHashTable
 * -------------------------
 * Searches for a key in the hash table and returns the associated value.
 *
 * ht: pointer to the hash table
 * key: string key to search
 *
 * returns: pointer to the associated value if found, NULL otherwise
 */
void* searchHashTable(HashTable* ht, const char* key) {
    unsigned int index = hashFunction(key);
    HashNode* node = ht->table[index];
    while (node) {
        if (strcmp(node->key, key) == 0) return node->value;
        node = node->next;
    }
    return NULL;
}

/*
 * Function: deleteHashTable
 * -------------------------
 * Deletes a key-value pair from the hash table if it exists.
 *
 * ht: pointer to the hash table
 * key: string key to delete
 */
void deleteHashTable(HashTable* ht, const char* key) {
    unsigned int index = hashFunction(key);
    HashNode* node = ht->table[index];
    HashNode* prev = NULL;
    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) prev->next = node->next;
            else ht->table[index] = node->next;
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

/*
 * Function: freeHashTable
 * -----------------------
 * Frees all memory associated with the hash table, including all nodes.
 *
 * ht: pointer to the hash table
 */
void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = ht->table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(ht);
}

/*
 * Iterates over each key-value pair in the hash table
 * and applies a user-provided callback function.
 *
 * ht: the hash table
 * callback: the function to call on each key-value pair
 * userData: optional pointer passed to the callback
 */
 void forEachHash(HashTable* ht, void (*callback)(const char* key, void* value, void* userData), void* userData) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = ht->table[i];
        while (node) {
            callback(node->key, node->value, userData);
            node = node->next;
        }
    }
}