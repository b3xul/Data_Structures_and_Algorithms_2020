#ifndef STACK_H_DEFINED
#define STACK_H_DEFINED

#include "Item.h"

typedef struct STACKnode *link;
typedef struct _stack *Stack;

Stack STACKinit(int N);
// funzione STACKinit relativa ad uno Stack implementato con una lista concatenata
//Stack STACKinit();
int STACKempty(Stack stack);
ITEM STACKpop(Stack stack);
void STACKpush(Stack stack, ITEM x);

#endif //STACK_H_DEFINED
