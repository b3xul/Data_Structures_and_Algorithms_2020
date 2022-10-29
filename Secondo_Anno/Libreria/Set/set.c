#include <stdio.h>
#include <stdlib.h>
#include "set.h"

/*Implementazione con vettore ordinato*/
int min (int a,int b);

struct set {
	Item *v;
	int N;
};

SET SETinit(int maxN) {
	SET s = malloc(sizeof *s);
	s->v = malloc(maxN*sizeof(Item));
	s->N=0;

	return s;
}

int SETsearch(SET s, Key k) {
	int l = 0, m, r = s->N -1;
	while (l <= r) {
		m = l + (r-l)/2;
		if (!KEYcmp(KEYget(s->v[m]), k))
			return 1;
		if (KEYcmp(KEYget(s->v[m]), k)<0)
			l = m+1;
		else
			r = m-1;
	}
	return 0;
}

SET SETunion(SET s1, SET s2) {
	int i=0, j=0, k=0, size1=SETsize(s1);
	int size2=SETsize(s2);
	SET s;
	s = SETinit(size1+size2);
	for(k = 0; (i < size1) || (j < size2); k++)
		if (i >= size1) s->v[k] = s2->v[j++];
		else if (j >= size2) s->v[k] = s1->v[i++];
		else if (KEYcmp(KEYget(s1->v[i]), KEYget(s2->v[j])<0))
			s->v[k] = s1->v[i++];
		else if (KEYcmp(KEYget(s2->v[j]), KEYget(s1->v[i])<0))
			s->v[k] = s2->v[j++];
		else {
			s->v[k] = s1->v[i++];
			j++;
		}
	s->N = k;
	return s;
}

SET SETintersection(SET s1, SET s2) {
	int i=0, j=0, k=0, size1=SETsize(s1);
	int size2=SETsize(s2), minsize;
	SET s;
	minsize = min(size1, size2);
	s = SETinit(minsize);
	while ((i < size1) && (j < size2)) {
		if (!KEYcmp(KEYget(s1->v[i]), KEYget(s2->v[j]))) {
			s->v[k++] = s1->v[i++];
			j++;
		} else if (KEYcmp(KEYget(s1->v[i]), KEYget(s2->v[j])<0)) i++;
		else j++;
	}
	s->N = k;
	return s;
}

int SETsize (SET s){
    return s->N;
}

int min(int a,int b){
    return (a<=b)?a:b;
}
/*Implementazione con lista non ordinata

typedef struct SETnode *link;
struct set {
	link head;
	int N;
};
struct setNode {
	Item val;
	link next;
};
SET SETinit(int maxN) {
	SET s = malloc(sizeof *s);
	s->head = NULL;
	s->N = 0;
	return s;
}

int SETsearch(SET s, Key k) {
	link x;
	x = s->head;
	while (x != NULL) {
		if (KEYeq(key(x->val), k))
			return 1;
		x = x->next;
	}
	return 0;
}

SET SETunion(SET s1, SET s2) {
	link x1, x2;
	int founds2, counts2 =0;
	SET s = SETinit(s1->N + s2->N);
	x1 = s1->head;
	while (x1 != NULL) {
		SETfill(s, x1->val);
		x1 = x1->next;
	}
	x2 = s2->head;
	while (x2 != NULL) {
		x1 = s1->head;
		founds2 = 0;
		while (x1 != NULL) {
			if (ITEMeq(x1->val, x2->val))
				founds2 = 1;
			x1 = x1->next;
		}
		if (founds2 == 0) {
			SETfill(s, x2->val);
			counts2++;
		}
		x2 = x2->next;
	}
	s->N = s1->N + counts2;
	return s;
}

SET SETintersection(SET s1, SET s2) {
	link x1, x2;
	int counts=0;
	SET s;
	s = SETinit(s1->N + s2->N);
	x1 = s1->head;
	while (x1 != NULL) {
		x2 = s2->head;
		while (x2 != NULL) {
			if (ITEMeq(x1->val, x2->val)) {
				SETfill(s, x1->val);
				counts++;
				break;
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
	s->N = counts;
	return s;
}

SET SETfill (SET s, ITEM val){ ->ins in head
}
*/
