#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define eq(A, B) (key(A) == key(B))
#define neq(A, B) (key(A) != key(B))
#define less(A, B) (key(A) < key(B))
#define greater(A, B) (key(A) > key(B))
#define maxKey 100

typedef int Item;
typedef int Key;

Key key(Item x);
Item ITEMscan();
void ITEMshow(Item x);
Item ITEMrand();
int ITEMlt(Item x, Item y);
int ITEMgt(Item x, Item y);

#endif // ITEM_H_INCLUDED
