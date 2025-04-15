#include "list.h"
#include <stdlib.h>

typedef struct Node
{
    void *Item; // Item will be a void* so that the list can hold any value
    struct Node *Next;
} *Node;

typedef struct List
{
    int ItemCount;
    Node Head;
    Node Tail;
} *List;

// Creates a new empty list
List CreateList()
{
    List NewList = malloc(sizeof(List));
    NewList->ItemCount = 0;
    NewList->Head = NULL;
    NewList->Tail = NULL;

    return NewList;
}

// Inserts a value into the list. Since it is a pointer, the value should not be edited anymore outside of the list functions.
// Returns the position of the new item
int InsertValue(List List, void *Item)
{
    Node NewNode = malloc(sizeof(Node));
    NewNode->Item = Item;
    NewNode->Next = NULL;

    List->Tail->Next = NewNode;
    List->Tail = NewNode;

    if (List->ItemCount == 0)
    { // The list was empty, update the head
        List->Head = Item;
    }
    List->ItemCount++;
    return List->ItemCount - 1;
}

// Returns the item at a certain position
void GetItem(List List, int Position)
{
    Node Current = List->Head;
    for (int i = 1; i < Position; i++)
    {
        Current = Current->Next;
    }
    return Current->Item;
}

// Deletes the value at a given position in the list.
// You can find the position of a certain item with FindValue()
void DeleteValue(List List, int Position)
{
    if (List->ItemCount >= Position)
    {
        // The position is not in the list
        return;
    }

    Node Previous;
    Node ToDelete;
    Node Current;
    for (int i = 0; i < Position + 1; i++)
    {
        if (i == 0)
        {
            Current = List->Head;
        }
        else
        {
            Current = Current->Next;
        }

        switch (i - Position)
        {
        case -1:
            Previous = Current;
            break;
        case 0:
            ToDelete = Current;
            break;
        }
    }

    Previous->Next = Current;
    free(ToDelete);
    if (Current == NULL)
    {
        List->Tail = Previous;
    }
    return;
}

// Finds a certain value in the list and returns its position
// Returns -1 if it does not find it
int FindValue(List List, void *Value)
{
    int Pos = -1;
    Node Current = List->Head;
    for (int i = 0; i < List->ItemCount; i++)
    {
        if (Current->Item == Value)
        {
            Pos = i;
            break;
        }
        Current = Current->Next;
    }
    return Pos;
}