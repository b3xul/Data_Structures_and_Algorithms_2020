#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#define MAXC 31

typedef struct item{ char name[MAXC]; int index} Item ;

typedef char* Key;

Item ITEMnew(char* name);
Item ITEMscan();
void ITEMstore(Item val);
int  ITEMcheckNull(Item val);
Item ITEMsetNull();
Key  KEYget(Item *pval);
int  KEYcmp(Key k1, Key k2);

#endif


