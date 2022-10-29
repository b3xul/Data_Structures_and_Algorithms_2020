#include <stdio.h>
#include <stdlib.h>
#include "list.h"

link newNode(int val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

link list_insert_head(link h, int val) {
    h = newNode(val,h);
    return h;
}

void list_show(link x) {
    int i;
    for(i=0; x != NULL; i++, x = x->next){
        printf("Nodo %d:   ",i);
        printf("%d\n",x->val);
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
