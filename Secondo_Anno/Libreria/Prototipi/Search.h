#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "Item.h"

int BinarySearch(ITEM *v, int l, int r, Key k);
int BinarySearchR(ITEM *v, int l, int r, Key k);
int LinearSearch(ITEM *v, int l, int r, Key k);

#endif // SEARCH_H_INCLUDED
