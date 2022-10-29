#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "inventario.h"

typedef struct invArray_s{
    obj_t* inventory;
    int nInv;
    int maxInv;
}invArray_t;

invArray_t* tab_inv_init(){
    invArray_t* tab=(invArray_t*)malloc(sizeof(invArray_t));
    tab->inventory=NULL;
    tab->maxInv=tab->nInv=0;
    return tab;
}

void leggi_file_obj(invArray_t* tab, FILE* fp){
    obj_t d;
    int i;
    char buffer[MAX_STR];

    fscanf(fp,"%d",&tab->maxInv);

    tab->inventory=(obj_t*)malloc(tab->maxInv*sizeof(obj_t));
    if(tab->inventory==NULL){
        fprintf(stderr,"Errore allocazione inventario\n");
        return;
    }

    for(i=0;i<tab->maxInv;i++){
        fscanf(fp,"%s",buffer);
        d.nome=strdup(buffer);

        fscanf(fp,"%s",buffer);
        d.tipo=strdup(buffer);

        fscanf(fp,"%d%d%d%d%d%d",&d.modifiers.hp,&d.modifiers.mp,&d.modifiers.atk,&d.modifiers.def,&d.modifiers.mag,&d.modifiers.spr);

        tab->inventory[i]=d;
        tab->nInv++;
    }

    return;
}

obj_t* ricerca_nome(char* str, invArray_t* tab){
    int i;
    for(i=0;i<tab->nInv;i++){
        if(!strcmp(str,tab->inventory[i].nome))
            return &tab->inventory[i];
    }
    return NULL;
}

void stampa_inventory(invArray_t* t, FILE* fp){
    int i;
    for(i=0;i<t->nInv;i++)
        obj_stampa(&t->inventory[i], fp);
}
