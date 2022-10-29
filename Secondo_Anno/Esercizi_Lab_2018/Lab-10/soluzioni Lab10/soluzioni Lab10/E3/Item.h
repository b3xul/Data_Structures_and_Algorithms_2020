#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#define MAXL 31

typedef struct {
  char elab[MAXL];
  char net[MAXL];
} Item;

typedef char *Key;

Item  ITEMload(char uno[], char due[]);
void  ITEMstore(Item val);
Item  ITEMsetNull();
Key   KEYget(Item *pval);
void  KEYscan(char nodo[]);
int   KEYcmp(Key k1, Key k2);

#endif


