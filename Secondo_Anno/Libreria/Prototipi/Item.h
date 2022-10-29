#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <stdio.h>

typedef char *Key;
typedef struct _item *ITEM;

ITEM ITEMalloc();
int ITEMcheckvoid(ITEM x);
ITEM ITEMchange();
void ITEMfree(ITEM x);
ITEM ITEMfscan(FILE *filePointer);
ITEM ITEMnew(Key x);
ITEM ITEMscan();
ITEM ITEMsetvoid();
void ITEMshow(ITEM x);

int KEYcompare(Key x, Key y);
int KEYeq(Key x, Key y);
Key KEYfscan(FILE *filePointer);
Key KEYget(ITEM x);
int KEYgreater(Key x, Key y);
int KEYless(Key x, Key y);
Key KEYscan();

int CMPprio(ITEM x, ITEM y);
int CMPname(ITEM x, ITEM y);
KEYname GETname(ITEM x);
KEYprio GETprio(ITEM x);

#endif // ITEM_H_INCLUDED

