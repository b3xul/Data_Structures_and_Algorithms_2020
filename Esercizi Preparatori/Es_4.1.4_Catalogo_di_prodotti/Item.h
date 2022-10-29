#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

#define MAXS 21

typedef struct {
  float price;
  char name[MAXS];
} Item;

typedef float Key;
typedef char* SearchKey;

Item ITEMscan(FILE *fin);
int  ITEMgreater(Item val1, Item val2);
void ITEMstore(FILE *fout, Item val);
Item ITEMsetNull();
int ITEMcheckNull(Item);
Key  KEYget(Item val);
Key  KEYcmp(Key A, Key B);
SearchKey  SearchKEYget(Item* val);
int  SearchKEYcmp(SearchKey A, SearchKey B);
#endif


