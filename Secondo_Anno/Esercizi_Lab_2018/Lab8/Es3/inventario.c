#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "inventario.h"

void leggi_file_obj(tabInv* tab, FILE* fp){
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

obj_t* ricerca_nome(char* str, tabInv tab){
    int i;
    for(i=0;i<tab.nInv;i++){
        if(!strcmp(str,tab.inventory[i].nome))
            return &tab.inventory[i];
    }
    return NULL;
}

void stampa_inventory(tabInv t, FILE* fp){
    int i;
    for(i=0;i<t.nInv;i++)
        stampa_object(&t.inventory[i], fp);
}

void stampa_object(obj_t* o, FILE* fp){
    fprintf(fp,"%s %s\n",o->nome,o->tipo);
    stampa_stats(&(o->modifiers),fp,1);
}

void stampa_stats(stat_t* s, FILE* fp, int type){   //0: pg, 1: obj
    //TO-DO: statistiche nel formato statbase(+modifiers)
    if(type==0)
        fprintf(fp,"HP:%d   MP:%d   ATK:%d   DEF:%d   MAG:%d   SPR:%d\n",s->hp,s->mp,s->atk,s->def,s->mag,s->spr);
    else
        fprintf(fp,"HP:%s%d   MP:%s%d   ATK:%s%d   DEF:%s%d   MAG:%s%d   SPR:%s%d\n",(s->hp>0)?"+":"",s->hp,(s->mp>0)?"+":"",s->mp,(s->atk>0)?"+":"",s->atk,(s->def>0)?"+":"",s->def,(s->mag>0)?"+":"",s->mag,(s->spr>0)?"+":"",s->spr);
}
