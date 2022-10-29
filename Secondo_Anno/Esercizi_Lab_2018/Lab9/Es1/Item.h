#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct att{
    int S;
    int F;
}Item;

typedef int Key;

int  ITEMeq(Item A, Item B);
int  ITEMneq(Item A, Item B);
int  ITEMlt(Item A, Item B);
int  ITEMgt(Item A, Item B);
Item ITEMscan();
void ITEMshow(Item A);
Item ITEMrand();

#endif // ITEM_H_INCLUDED
