#ifndef PERSONAGGI_H_INCLUDED
#define PERSONAGGI_H_INCLUDED

#include "pg.h"
#include "equipment.h"

typedef struct pgList_s pgList_t;

/*Pg*/
pgList_t* tab_pg_init();
pg_t pg_set_void();
int pg_check_void(pg_t pg);
pg_t new_pg(FILE* fp);
void add_player(pg_t* player, pgList_t* tab_pg);
void leggi_file_pg(pgList_t* tab_pg, FILE* fp);
pg_t ricerca_player(char* str, pgList_t* tab_pg);
pg_t estrai_player(char* str, pgList_t* tab_pg);

/*Equip*/
void add_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv);
void remove_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv);

/*Stampa*/
void stampa_players(pgList_t* tab_pg, FILE* fp);

#endif // PERSONAGGI_H_INCLUDED
