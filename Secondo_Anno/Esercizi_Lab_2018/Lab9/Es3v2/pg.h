#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED

#include "equipment.h"

typedef struct player{
    char* codice; char* nome; char* classe; equip_t* equip; stat_t stats;
}pg_t;

/*Pg*/
pg_t pg_set_void();
int pg_check_void(pg_t pg);
pg_t pg_new(FILE* fp);
void pg_stampa(pg_t* x, FILE* fp);

#endif // PG_H_INCLUDED
