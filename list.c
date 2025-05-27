#include <stdlib.h>
#include "list.h"

/*
 * File: list.c
 * ------------
 * Implements a simple singly linked list for storing generic pointers.
 * Provides basic operations such as creation, insertion, retrieval,
 * size calculation, and cleanup.
 */

// Structure representing a node in the list
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Structure representing the list itself
struct ListStruct {
    Node* head;
    int size;
};

/*
 * Function: createList
 * --------------------
 * Allocates and initializes an empty linked list.
 *
 * returns: pointer to the new List
 */
List createList() {
    List list = malloc(sizeof(struct ListStruct));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

/*
 * Function: insertList
 * --------------------
 * Inserts an item at the beginning of the list.
 *
 * list: pointer to the list
 * item: pointer to the data to be inserted
 *
 * returns: 0 on success, -1 on memory allocation failure
 */
int insertList(List list, void* item) {
    Node* node = malloc(sizeof(Node));
    if (!node) return -1;
    node->data = item;
    node->next = list->head;
    list->head = node;
    list->size++;
    return 0;
}

/*
 * Function: getItem
 * -----------------
 * Retrieves the item at a specific index in the list.
 *
 * list: pointer to the list
 * index: index of the item to retrieve (0-based)
 *
 * returns: pointer to the item, or NULL if index is invalid
 */
void* getItem(List list, int index) {
    if (!list || index < 0 || index >= list->size) return NULL;
    Node* current = list->head;
    for (int i = 0; i < index; i++) current = current->next;
    return current->data;
}

/*
 * Function: getSize
 * -----------------
 * Returns the number of elements in the list.
 *
 * list: pointer to the list
 *
 * returns: number of elements, or 0 if list is NULL
 */
int getSize(List list) {
    return list ? list->size : 0;
}

/*
 * Function: freeList
 * ------------------
 * Frees all memory associated with the list and its nodes.
 *
 * list: pointer to the list
 */
void freeList(List list) {
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
