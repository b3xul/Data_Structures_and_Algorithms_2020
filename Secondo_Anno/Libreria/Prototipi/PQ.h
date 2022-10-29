#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

#include "Item.h"

typedef struct _pq *PQ;

void PQchange(PQ pq, int pos, ITEM x);
// PQchange relativa ad una PQ che fa uso degli indici
//void PQchange(PQ pq, ITEM x);
void PQdisplay(PQ pq);
int PQempty(PQ pq);
ITEM PQextractMax(PQ pq);
PQ PQinit(int maxN);
void PQinsert(PQ pq, ITEM x);
ITEM PQshowMax(PQ pq);
int PQsize(PQ pq);

#endif
