#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
/*
Vettore implementa come indici, lista come puntatori, ma sempre
HEAD: prossimo elemento da estrarre usando GET.
TAIL: posizione prossimo elemento da inserire usando PUT.

usando buffer circolare:
N=maxN+1;
HEAD e TAIL vengono incrementati %N. HEAD VARIA TRA 1 E N, TAIL VARIA TRA 0 E N-1 (MAXN)
INIT: TAIL=0 HEAD=N
EMPTY: HEAD%N==TAIL
FULL: TAIL==HEAD-1
PUT: se la coda non è piena 1.inserisco in tail (tra 0 e MAXN) (anche se inserisco in maxn non avrò mai + di maxn elementi perchè si sarà spostata tail.)
                            2.tail=(tail+1)%N
GET: se la coda non è vuota 1.head=head%N (se head valeva N ora vale zero, indice del prossimo elemento da estrarre)
                            2.estraggo da head (tra 0 e MAXN)
                            3.head++;
*/
/*Implementazione tramite vettore*/


struct queue {
	Item *q;
	int N, head, tail;
};
QUEUE QUEUEinit(int maxN) {
	QUEUE q = malloc(sizeof *q) ;
	q->q = malloc(maxN*sizeof(Item));
	q->N=maxN+1;
	q->head = q->N;
	q->tail = 0;
	return q;
}
int QUEUEempty(QUEUE q) {
	return (q->head)%(q->N) == q->tail;
}
void QUEUEput(QUEUE q, Item val) {
	q->q[q->tail++] = val;
	q->tail = q->tail%q->N;
}
Item QUEUEget(QUEUE q) {
	q->head = q->head%q->N;
	return q->q[q->head++];
}

/*Implementazione con lista
typedef struct QUEUEnode *link;
struct QUEUEnode {
	Item val;
	link next;
};
struct queue {
	link head;
	link tail;
};

link NEW(Item val, link next) {
	link x = malloc(sizeof *x) ;
	x->val = val;
	x->next = next;
	return x;
}
QUEUE QUEUEinit(int maxN) {
	QUEUE q = malloc(sizeof *q) ;
	q->head = NULL;
	return q;
	int QUEUEempty(QUEUE q) {
		return q->head == NULL;
	}
}
void QUEUEput (QUEUE q, Item val) {
	if (q->head == NULL) {
		q->tail = NEW(val, q->head) ;
		q->head = q->tail;
		return;
	}
	q->tail->next = NEW(val, q->tail->next) ;
	q->tail = q->tail->next;
}
Item QUEUEget(QUEUE q) {
	Item tmp = q->head->tmp;
	link t = q->head->next;
	free(q->head);
	q->head = t;
	return tmp;
}
*/
