#include <stdio.h>
#include "pg.h"

void stampa_pg(pg_t* x, FILE* fp){
    fprintf(fp,"%s %s %s\n",x->codice, x->nome, x->classe);
    obj_stampa_stats(&x->stats,fp,0);
    stampa_equip(&x->equip,fp);
}
