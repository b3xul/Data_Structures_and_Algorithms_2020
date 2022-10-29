#include <stdio.h>
#include "pg.h"

pg_t pg_set_void(){
    pg_t dummy;
    dummy.nome="";
    return dummy;
}

int pg_check_void(pg_t pg){     //Ritorna 1 se pg vuoto
    return (strcmp(pg.nome,"")==0);
}

pg_t pg_new(FILE* fp){
    char buffer[MAX_STR];
    pg_t d;

    if(fscanf(fp,"%s",buffer)==EOF)
        return pg_set_void();

    d.codice=strdup(buffer);

    fscanf(fp,"%s",buffer);
    d.nome=strdup(buffer);

    fscanf(fp,"%s",buffer);
    d.classe=strdup(buffer);

    fscanf(fp,"%d%d%d%d%d%d",&d.stats.hp,&d.stats.mp,&d.stats.atk,&d.stats.def,&d.stats.mag,&d.stats.spr);

    d.equip=equip_init();

    return d;
}


void pg_stampa(pg_t* x, FILE* fp){
    fprintf(fp,"%s %s %s\n",x->codice, x->nome, x->classe);
    obj_stampa_stats(&x->stats,fp,0);
    stampa_equip(&x->equip,fp);
}
