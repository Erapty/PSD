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
 * Inserts a new item at the end of the list.
 *
 * list: pointer to the list
 * data: generic pointer to the item to insert
 *
 * This function allocates memory for a new node and appends it
 * at the tail of the singly linked list. The list preserves insertion order.
 *
 * returns: void
 */

void insertList(List list, void* item) {
    Node* n = malloc(sizeof(Node));
    n->data = item;
    n->next = NULL;

    if (list->head == NULL) {
        list->head = n;
    } else {
        Node* current = list->head;
        while (current->next != NULL)
            current = current->next;
        current->next = n;
    }

    list->size++;
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



/*
 *Accessor to get the head of the list
*/
void* getListHead(List list) {
    return (void*)list->head;

}
