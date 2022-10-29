#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#define MAXC 15

typedef struct {
  char name[MAXC];
  int value;
} Item;

typedef int Key;

Item ITEMscan(char* name, int value);
Item ITEMrand();
void ITEMshow(Item val);
int  ITEMcheckNull(Item val);
Item ITEMsetNull();
Key  KEYget(Item val);
int  KEYcmp(Key k1, Key k2);

#endif

