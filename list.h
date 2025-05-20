#ifndef LIST_H
#define LIST_H

// Opaque pointer to the list structure
typedef struct ListStruct* List;

/*
 * Creates and initializes an empty list.
 *
 * returns: pointer to the new List
 */
List createList();

/*
 * Inserts a new item at the beginning of the list.
 *
 * list: pointer to the list
 * data: generic pointer to the item to insert
 *
 * returns: 0 on success, -1 on allocation failure
 */
int insertList(List list, void* data);

/*
 * Retrieves an item from the list at the specified index.
 *
 * list: pointer to the list
 * index: index of the item (0-based)
 *
 * returns: pointer to the item, or NULL if index is invalid
 */
void* getItem(List list, int index);

/*
 * Returns the number of elements in the list.
 *
 * list: pointer to the list
 *
 * returns: size of the list, or 0 if list is NULL
 */
int getSize(List list);

/*
 * Frees all memory used by the list and its nodes.
 *
 * list: pointer to the list
 */
void freeList(List list);

#endif
