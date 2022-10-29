#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "personaggi.h"

typedef struct player_node* link;

typedef struct player_node{
    pg_t player;
    link next;
}pg_node_t;

struct pgList_s{
    link head;
    link tail;
    int nPg;
};

/*Lista*/
static link new_node(pg_t val, link next);
static void list_insert_tail(pg_t* player_p, link* hp, link* tp);
static pg_t estrai_codice(char* str, link* hp, link* tp);
static pg_t ricerca_codice(char* str, link h);
static link ricerca_codice_link(char* str, link h);

static link new_node(pg_t val, link next){
    link x=(link)malloc(sizeof(pg_node_t));
    if(x==NULL){
        fprintf(stderr,"Allocazione nodo fallita");
        return NULL;
    }
    x->player=val;
    x->next=next;

    return x;
}

static void list_insert_tail(pg_t* player_p, link* hp, link* tp){
    pg_t player=*player_p;
    if(*hp==NULL)   //Inserimento in coda=Inserimento in testa, aggiorno hp e tp
        *hp=*tp=new_node(player,NULL);     //HP=TP: nuovo nodo sarà sia la testa che la coda della lista e punterà a null
    else{           //Inserimento in coda: aggiorno solo tp
        (*tp)->next=new_node(player,NULL);      //Creo nuovo nodo dopo tail
        *tp=(*tp)->next;                         //Nuovo nodo diventa tail
    }
}

static pg_t estrai_codice(char* str, link* hp, link* tp){
    link* xp;
    link tmp;
    pg_t d;
    for(xp=hp; *xp!=NULL; xp=&((*xp)->next)){
        if(!strcmp(str,(*xp)->player.codice)){
            tmp=*xp;          //tmp:link corrispondente al nodo trovato
            *xp=(*xp)->next;  //nodo attuale viene eliminato dalla lista
            d=tmp->player;    //salvo item del nodo attuale
            free(tmp);        //libero nodo trovato
            return d;
        }
    }
    return pg_set_void();
}

static pg_t ricerca_codice(char* str, link h){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(!strcmp(str,x->player.codice))
            return x->player;
    }
    return pg_set_void();
}

static link ricerca_codice_link(char* str, link h){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(!strcmp(str,x->player.codice))
            return x;
    }
    return NULL;
}
/*PG*/
pgList_t* personaggi_init(){
    pgList_t* tab_pg=(pgList_t*)malloc(sizeof(pgList_t));
    tab_pg->head=tab_pg->tail=NULL;
    tab_pg->nPg=0;
    return tab_pg;
}

void personaggi_leggi(pgList_t* tab_pg, FILE* fp){
    pg_t d;
    int prosegui=1;

    while(prosegui){
        d=pg_new(fp);
        if(pg_check_void(d))
            prosegui=0;
        else{
            personaggi_add_player(&d,tab_pg);
            (tab_pg->nPg)++;
        }
    }

    return;
}

void personaggi_add_player(pg_t* player, pgList_t* tab_pg){
    list_insert_tail(player,&(tab_pg->head),&(tab_pg->tail));
}

pg_t personaggi_ricerca_player(char* str, pgList_t* tab_pg){
    return ricerca_codice(str,tab_pg->head);
}
pg_t personaggi_estrai_player(char* str,pgList_t* tab_pg){
    return estrai_codice(str,&(tab_pg->head),&(tab_pg->tail));
}

/*Equip*/
void personaggi_add_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv){
    link pg_link=ricerca_codice_link(player_name,tab_pg->head);
    if(pg_link==NULL){
        printf("Codice personaggio non trovato\n");
        return;
    }
    else
        pg_stampa(&pg_link->player,stdout);

    equip( pg_link->player.equip, &(pg_link->player.stats), object_name, tab_inv);

    pg_stampa(&(pg_link->player),stdout);
}

void personaggi_remove_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv){
    link pg_link=ricerca_codice_link(player_name,tab_pg->head);
    if(pg_link==NULL){
        printf("Codice non trovato\n");
        return;
    }
    else
        pg_stampa(&pg_link->player,stdout);

    unequip( pg_link->player.equip, &(pg_link->player.stats), object_name, tab_inv);

    pg_stampa(&(pg_link->player),stdout);
}


/*Stampa*/

/*Potrebbe essere necessario invArray per fare stampare Obj equipaggiati, indicati da indice*/
void personaggi_stampa(pgList_t* tab_pg, FILE* fp){
    link x;
    for(x=tab_pg->head; x!=NULL; x=x->next)
        pg_stampa(&(x->player),fp);
}
