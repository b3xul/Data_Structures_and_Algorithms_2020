#ifndef PERSONAGGI_H_INCLUDED
#define PERSONAGGI_H_INCLUDED

#include "pg.h"

typedef struct pgList_s pgList_t;

/*Pg*/
pgList_t* personaggi_init();
void personaggi_add_player(pg_t* player, pgList_t* tab_pg);
void personaggi_leggi(pgList_t* tab_pg, FILE* fp);
pg_t personaggi_ricerca_player(char* str, pgList_t* tab_pg);
pg_t personaggi_estrai_player(char* str, pgList_t* tab_pg);

/*Equip*/
void personaggi_add_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv);
void personaggi_remove_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv);

/*Stampa*/
void personaggi_stampa(pgList_t* tab_pg, FILE* fp);

#endif // PERSONAGGI_H_INCLUDED
