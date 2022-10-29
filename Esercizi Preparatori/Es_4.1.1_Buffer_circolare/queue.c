#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*Implementazione tramite vettore*/

struct queue {
	Item *q;
	int N, head, tail, n_el;
};

QUEUE QUEUEinit(int maxN) {
	QUEUE q = malloc(sizeof *q) ;
	q->q = malloc(maxN*sizeof(Item));
	q->N=maxN+1;
	q->head = q->N;
	q->tail = 0;
	q->n_el=0;
	return q;
}

int QUEUEempty(QUEUE q) {
	return (q->head)%(q->N) == q->tail;
}
void QUEUEput(QUEUE q, Item val) {
    q->n_el++;
	q->q[q->tail++] = val;
	q->tail = q->tail%q->N;
}
Item QUEUEget(QUEUE q) {
    q->n_el--;
	q->head = q->head%q->N;
	return q->q[q->head++];
}

int QUEUEsize(QUEUE q){
    return q->N;
}

void QUEUEshow(FILE* out, QUEUE q){
    int i;
    for(i=0;i<q->N;i++){

    }
}

void QUEUEfree(QUEUE q){
    if(q==NULL || q->q==NULL)
        return;
    free(q->q);
    free(q);
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
