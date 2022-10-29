#ifndef PERSONAGGI_H_INCLUDED
#define PERSONAGGI_H_INCLUDED

#include "inventario.h"

typedef struct equipment{
    obj_t* vect_equip[8];
    int n_equip;
}equip_t;

typedef struct player{
    char* codice; char* nome; char* classe; equip_t equip; stat_t stats;
}pg_t;

typedef struct player_node* link;

typedef struct player_node{
    pg_t player;
    link next;
}pg_node_t;

typedef struct players_wrapper{
    link head;
    link tail;
    int nPg;
}tabPg;

/*Equip*/
void equip(link pg_link, obj_t* obj_p);
void unequip(link pg_link, obj_t* obj_p);
/*Pg*/
pg_t pg_set_void();
int pg_check_void(pg_t pg);
pg_t new_pg(FILE* fp);
int leggi_file_pg(link* hp, link* tp, FILE* fp);
/*Lista*/
link new_node(pg_t val, link next);
void list_insert_tail(pg_t* player_p, link* hp, link* tp);
pg_t estrai_codice(char* str, link* hp, link* tp);
link ricerca_codice(char* str, link h);
/*Stampa*/
void stampa_equip(equip_t* e, FILE* fp);
void stampa_players(link h, link t, FILE* fp);
void stampa_pg_node_t(link x, FILE* fp);
void stampa_pg(pg_t* x, FILE* fp);

#endif // PERSONAGGI_H_INCLUDED
