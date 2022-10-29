#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "Item.h"

typedef struct node *link;

link LISTDelHead(link head, link z);
link LISTDelKey(link head, link z, Key k);
link LISTDelKeyR(link x, link z, Key k);
ITEM LISTExtrHeadP(link *head, link z)
ITEM LISTExtrKeyP(link *head, link z, Key k);
void LISTFree(link *head, link z);
void LISTInsHeadP(link *head, ITEM val);
void LISTInsTFast(link *head, link *tail, link z, ITEM val);
link LISTReverse(link x, link *tail, link z);
ITEM LISTSearch(link head, link z, Key k);
void LISTShow(link head, link z);
void LISTSort(link *head, link z);
link SortLISTDel(link head, link z, Key k);
link SortLISTIns(link head, link z, ITEM val);
ITEM SortLISTSearch(link head, link z, Key k);

#endif // LIST_H_INCLUDED
