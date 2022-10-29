#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "Item.h"

typedef struct queue *QUEUE;

QUEUE QUEUEinit(int maxN);
int QUEUEempty(QUEUE q);
void QUEUEput(QUEUE q, Item val);
Item QUEUEget (QUEUE q);
#endif // QUEUE_H_INCLUDED
