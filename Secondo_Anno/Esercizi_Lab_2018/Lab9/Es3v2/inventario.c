#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "inventario.h"

struct invArray_s{
    obj_t* inventory;
    int nInv;
    int maxInv;
};

invArray_t* inventario_init(){
    invArray_t* tab=(invArray_t*)malloc(sizeof(invArray_t));
    tab->inventory=NULL;
    tab->maxInv=tab->nInv=0;
    return tab;
}

void inventario_leggi(invArray_t* tab, FILE* fp){
    int i;

    fscanf(fp,"%d",&tab->maxInv);

    tab->inventory=(obj_t*)malloc(tab->maxInv*sizeof(obj_t));
    if(tab->inventory==NULL){
        fprintf(stderr,"Errore allocazione inventario\n");
        return;
    }

    for(i=0;i<tab->maxInv;i++){
        tab->inventory[i]=obj_leggi(fp);
        tab->nInv++;
    }

    return;
}

obj_t* inventario_ricerca_nome(char* str, invArray_t* tab){
    int i;
    for(i=0;i<tab->nInv;i++){
        if(!strcmp(str,tab->inventory[i].nome))
            return &tab->inventory[i];
    }
    return NULL;
}

void inventario_stampa(invArray_t* t, FILE* fp){
    int i;
    for(i=0;i<t->nInv;i++)
        obj_stampa(&t->inventory[i], fp);
}
