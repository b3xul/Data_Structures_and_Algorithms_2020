#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED

#include "equipment.h"

typedef struct player{
    char* codice; char* nome; char* classe; equip_t* equip; stat_t stats;
}pg_t;

void stampa_pg(pg_t* x, FILE* fp);
#endif // PG_H_INCLUDED
