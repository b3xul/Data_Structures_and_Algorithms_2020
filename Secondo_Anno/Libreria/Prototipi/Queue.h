#ifndef QUEUE_H_DEFINED
#define QUEUE_H_DEFINED

#include "Item.h"

typedef struct QUEUEnode *link;
typedef struct _queue *Queue;

Queue QUEUEinit(int N);
//funzione QUEUEinit relativa ad una Queue implementata con una lista concatenata
//Queue QUEUEinit();
int QUEUEempty(Queue queue);
ITEM QUEUEget(Queue queue);
void QUEUEput(Queue queue, ITEM x);

#endif //QUEUE_H_DEFINED
