#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct List *List;

List CreateList();
void DeleteValue(List List, int Position);
int InsertValue(List List, void *Item);
void GetItem(List List, int Position);
int FindValue(List List, void *Value);

#endif