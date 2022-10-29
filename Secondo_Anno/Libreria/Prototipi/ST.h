#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#include "Item.h"

typedef struct symboltable *ST;
typedef struct STnode *link;

void STchange(ST symbolTable,ITEM x);
int STcount(ST symbolTable);
void STdelete(ST symbolTable, Key x);
void STdisplay(ST symbolTable);
int STempty(ST symbolTable);
int STgetindex(ST symbolTable, ITEM x);
ITEM STgetitem(ST symbolTable, int i);
ST STinit(int maxN);
int STinsert(ST symbolTable, ITEM x);
char *STretrieve(ST symbolTable, int i);
ITEM STsearch(ST symbolTable, Key x);
int STsize(int maxN);

#endif //ST_H_DEFINED
