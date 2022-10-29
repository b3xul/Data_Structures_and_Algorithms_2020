#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Item.h"

typedef struct stack *STACK;

STACK STACKinit(int maxN);
int STACKempty(STACK s);
void STACKpush(STACK s, Item val);
Item STACKpop (STACK s);

#endif // STACK_H_INCLUDED
