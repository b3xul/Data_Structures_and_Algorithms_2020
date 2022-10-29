#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "Item.h"

typedef struct _heap *Heap;

void HEAPbuild (Heap h);
void HEAPdisplay(Heap h);
void HEAPfill(Heap h, ITEM item);
void HEAPfree(Heap h);
void HEAPify(Heap h, int i);
Heap HEAPinit(int maxN);
void HEAPsort(Heap h);

#endif // HEAP_H_INCLUDED
