#include <stdio.h>
#include <stdlib.h>
#include "list.h"

link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

link list_insert_head(link h, Item val) {
    h = newNode(val,h);
    return h;
}

void list_insert_head_P(link *hp, Item val) {
    *hp = newNode(val, *hp);
}

link list_insert_tail(link h, Item val) {
    link x;
    if (h==NULL){
        h=newNode(val, NULL);
        return h;
    }
    for (x=h; x->next!=NULL; x=x->next);
    x->next = newNode(val, NULL);
    return h;
}


void list_insert_tail_P(link *hp, Item val) {
    link x=*hp;
    if (x==NULL)
        *hp = newNode(val, NULL);
    else {
        for (; x->next!=NULL; x=x->next);
        x->next = newNode(val, NULL);
    }
}

/*v2
void listInsTailP(link *hp, Item val) {
    link *xp = hp;
    while (*xp != NULL)
        xp = &((*xp)->next);
    *xp = newNode(val, NULL);
}*/

void list_insert_tail_Fast(link *hp,link *tp,Item val) {
    if (*hp==NULL)
        *hp = *tp = newNode(val, NULL);
    else {
        (*tp)->next = newNode(val, NULL);
        *tp = (*tp)->next;
    }
}

Item list_search(link h, Key k) {
    link x;
    for (x=h; x!=NULL; x=x->next)
        if (!KEYcmp(KEYget(x->val), k))
            return x->val;
    return ITEMsetNull();
}

link list_delete_head(link h) {
    link t = h;
    if (h == NULL)
        return NULL;
    h = h->next;
    free(t);
    return h;
}

Item list_extract_headP(link *hp) {
    link t = *hp;
    Item tmp;
    if (t == NULL)
        return ITEMsetNull();
    tmp = t->val;
    *hp = t->next;
    free(t);
    return tmp;
}

link list_delete_key(link h, Key k) {
    link x, p;
    if (h == NULL)
        return NULL;
    for (x=h, p=NULL; x!=NULL; p=x, x=x->next) {
        if (!KEYcmp(KEYget(x->val),k)) {
            if (x==h)
                h = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }
    return h;
}

link list_delete_keyR(link x, Key k) {
    link t;
    if (x == NULL)
        return NULL;
    if (!KEYcmp(KEYget(x->val), k)) {
        t = x->next;
        free(x);
        return t;
    }
    x->next = list_delete_keyR(x->next, k);
    return x;
}

Item list_extract_keyP(link *hp, Key k) {
    link *xp, t;
    Item i = ITEMsetNull();
    for (xp=hp; (*xp)!=NULL; xp=&((*xp)->next)) {
        if (!KEYcmp(KEYget((*xp)->val),k)) {
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

link sorted_list_insert(link h, Item val) {
    link x, p;
    Key k = KEYget(val);
    if (h==NULL || KEYcmp(KEYget(h->val),k)>0 )
        return newNode(val, h);
    for (x=h->next, p=h;
            x!=NULL && KEYcmp(k,KEYget(x->val)>0 );
            p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

Item sorted_list_search(link h, Key k) {
    link x;
    for (x=h;
         x!=NULL && KEYcmp(k, KEYget(x->val))>=0 ;
         x=x->next)
        if (!KEYcmp(KEYget(x->val), k))
            return x->val;
    return ITEMsetNull();
}

link sorted_list_delete(link h, Key k) {
	link x, p;
	if (h == NULL) return NULL;
	for (x=h, p=NULL;
         x!=NULL && KEYcmp(k,KEYget(x->val))>=0 ;
         p=x, x=x->next) {
		if (!KEYcmp(KEYget(x->val),k)) {
			if (x==h)
                h = x->next;
			else
                p->next = x->next;
			free(x);
			break;
		}
	}
	return h;
}

link listReverse(link x) {
    // x=old head; r=new head (old tail) e nodo appena sistemato; y=prossimo nodo da sistemare; t=nodo successivo al prossimo nodo da sistemare
    link t, y = x, r = NULL;
    while (y != NULL) {
        t = y->next;
        y->next = r;
        r = y;
        y = t;
    }
    return r;
}

/*v2
link listReverseF(link x) {
    link y = x, r = NULL;
    Item tmp;
    while (y != NULL) {
        tmp = listExtrHeadP(&y);
        r = listInsHead(r, tmp);
    }
    return r;
}*/

/*Insertion sort list*/
link listSort(link h) {
    link x, u, t, r = NULL;
    //h diventa head della lista ordinata.
	for(t=h->next, h->next=NULL; t!=NULL; t=u) { //h->next=NULL: h è il primo elemento ordinato. t scorre il resto della lista a partire dal secondo elemento
		u = t->next;                             //u: successore di t, scorre insieme a t.
		if (KEYcmp(KEYget(h->val),KEYget(t->val))>0) { //se h viene dopo t, inverti t e h (inserimento in testa del nodo con chiave minima
			t->next = h;
			h = t;
		}
		else { //se h viene prima di t
			for (x=h; x->next != NULL; x=x->next) //x punta alla testa.
				if (KEYcmp(KEYget(x->next->val),KEYget(t->val))>0)
					break; //Confronta tutti i nodi dal secondo all'ultimo con t finchè non trovo un nodo maggiore di t.
			t->next = x->next;  //Inserisco t prima del nodo maggiore di lui
			x->next = t;
		}
	}
    return r;
}

link listSortF(link h) { //Insertion Sort list
    link y = h, r = NULL;
    Item tmp;
    while (y != NULL) {
        tmp = list_extract_headP(&y);
        r = sorted_list_insert(r, tmp);
    }
    return r;
}

void list_show(link x) {
    int i;
    for(i=0; x != NULL; i++, x = x->next){
        printf("Nodo %d:   ",i);
        ITEMshow(x->val);
    }
    printf("-----------------------\n");
}

void list_free(link x) {
    link t;
    while(x != NULL){
        t = x;
        x = x->next;
        free(t);
    }
}

/*
void insertNext(link x, link t) {
    t->next = x->next;
    x->next = t;
}

link deleteNext(link x) {
    link t = x->next;
    x->next = t->next;
    return t;
}
*/
