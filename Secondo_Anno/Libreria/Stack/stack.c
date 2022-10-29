#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/*Implementazione con vettore*/
struct stack {
	Item *s;
	int N;
};

STACK STACKinit(int maxN) {
	STACK sp = malloc(sizeof *sp) ;
	sp->s = malloc(maxN*sizeof(Item));
	sp->N=0;
	return sp;
}
int STACKempty(STACK sp) {
	return sp->N == 0;
}
void STACKpush(STACK sp, Item val) {
	sp->s[sp->N++] = val;
}
Item STACKpop(STACK sp) {
	return sp->s[--(sp->N)];
}

/*Implementazione con lista
typedef struct STACKnode* link;
struct STACKnode {
	Item val;
	link next;
};
struct stack {
	link head;
	int N;
};

static link NEW (Item val, link next) {
	link x = (link) malloc(sizeof *x);
	x->val = val;
	x->next = next;
	return x;
}
STACK STACKinit(int maxN) {
	STACK s = malloc(sizeof *s) ;
	s->head = NULL;
	s->N = 0;
	return s;
}
int STACKempty(STACK s) {
	return s->head == NULL;
}
void STACKpush(STACK s, Item val) {
	s->head = NEW(val, s->head);
}
Item STACKpop (STACK s) {
	Item tmp;
	tmp = s->head->val;
	link t = s->head->next;
	free(s->head);
	s->head = t;
	return tmp;
}
*/
