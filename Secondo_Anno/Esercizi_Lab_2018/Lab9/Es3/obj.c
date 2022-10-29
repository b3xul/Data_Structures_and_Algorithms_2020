#include <stdio.h>
#include "obj.h"

void obj_stampa(obj_t* o, FILE* fp){
    fprintf(fp,"%s %s\n",o->nome,o->tipo);
    obj_stampa_stats(&(o->modifiers),fp,1);
}

void obj_stampa_stats(stat_t* s, FILE* fp, int type){   //0: pg, 1: obj
    //TO-DO: statistiche nel formato statbase(+modifiers)
    if(type==0)
        fprintf(fp,"HP:%d   MP:%d   ATK:%d   DEF:%d   MAG:%d   SPR:%d\n",s->hp,s->mp,s->atk,s->def,s->mag,s->spr);
    else
        fprintf(fp,"HP:%s%d   MP:%s%d   ATK:%s%d   DEF:%s%d   MAG:%s%d   SPR:%s%d\n",(s->hp>0)?"+":"",s->hp,(s->mp>0)?"+":"",s->mp,(s->atk>0)?"+":"",s->atk,(s->def>0)?"+":"",s->def,(s->mag>0)?"+":"",s->mag,(s->spr>0)?"+":"",s->spr);
}
