#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <stdio.h>

#define MAXS 11

typedef struct item *Item;

typedef int Key;

Item ITEMscan(FILE* in);
Item ITEMrand();
void ITEMstore(Item val);
void ITEMstoreFile(Item val, FILE* out);
int  ITEMcheckNull(Item val);
Item ITEMsetNull();
void ITEMfree(Item val);
char* NAMEget(Item val);
Key  KEYget(Item val);
int  KEYcmp(Key k1, Key k2);

int exchange_points(Item winner, Item loser);
#endif

