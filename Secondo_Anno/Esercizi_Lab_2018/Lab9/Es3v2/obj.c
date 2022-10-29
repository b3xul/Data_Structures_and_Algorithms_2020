#include "obj.h"

obj_t obj_leggi(FILE* fp){
    obj_t d;
    char buffer[MAX_STR];

    fscanf(fp,"%s",buffer);
    d.nome=strdup(buffer);

    fscanf(fp,"%s",buffer);
    d.tipo=strdup(buffer);

    d.modifiers=obj_leggi_stats(fp);

    return d;
}

stat_t obj_leggi_stats(FILE* fp){
    stat_t s;
    fscanf(fp,"%d%d%d%d%d%d",&s.hp,&s.mp,&s.atk,&s.def,&s.mag,&s.spr);
    return s;
}

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
