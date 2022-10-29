#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#define MAXS 20

typedef char* Item;
typedef char* Key;

Item ITEMscan();
Item ITEMnew(char* x);
void ITEMstore(Item val);
int  ITEMcheckNull(Item val);
Item ITEMsetNull();
Key  KEYget(Item *pval);
int  KEYcmp(Key k1, Key k2);
void ITEMfree(Item val);

#endif


