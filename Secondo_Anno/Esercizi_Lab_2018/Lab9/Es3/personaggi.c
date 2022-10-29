#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "personaggi.h"

typedef struct player_node* link;

typedef struct player_node{
    pg_t player;
    link next;
}pg_node_t;

typedef struct pgList_s{
    link head;
    link tail;
    int nPg;
}pgList_t;

/*Lista*/
static link new_node(pg_t val, link next);
static void list_insert_tail(pg_t* player_p, link* hp, link* tp);
static pg_t estrai_codice(char* str, link* hp, link* tp);
static pg_t ricerca_codice(char* str, link h);
static link ricerca_codice_link(char* str, link h);

link new_node(pg_t val, link next){
    link x=(link)malloc(sizeof(pg_node_t));
    if(x==NULL){
        fprintf(stderr,"Allocazione nodo fallita");
        return NULL;
    }
    x->player=val;
    x->next=next;

    return x;
}

void list_insert_tail(pg_t* player_p, link* hp, link* tp){
    pg_t player=*player_p;
    if(*hp==NULL)   //Inserimento in coda=Inserimento in testa, aggiorno hp e tp
        *hp=*tp=new_node(player,NULL);     //HP=TP: nuovo nodo sarà sia la testa che la coda della lista e punterà a null
    else{           //Inserimento in coda: aggiorno solo tp
        (*tp)->next=new_node(player,NULL);      //Creo nuovo nodo dopo tail
        *tp=(*tp)->next;                         //Nuovo nodo diventa tail
    }
}

pg_t estrai_codice(char* str, link* hp, link* tp){
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

pg_t ricerca_codice(char* str, link h){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(!strcmp(str,x->player.codice))
            return x->player;
    }
    return pg_set_void();
}

link ricerca_codice_link(char* str, link h){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(!strcmp(str,x->player.codice))
            return x;
    }
    return NULL;
}
/*PG*/
pgList_t* tab_pg_init(){
    pgList_t* tab_pg=(pgList_t*)malloc(sizeof(pgList_t));
    tab_pg->head=tab_pg->tail=NULL;
    tab_pg->nPg=0;
    return tab_pg;
}

pg_t pg_set_void(){
    pg_t dummy;
    dummy.nome="";
    return dummy;
}

int pg_check_void(pg_t pg){     //Ritorna 1 se pg vuoto
    return (strcmp(pg.nome,"")==0);
}

pg_t new_pg(FILE* fp){
    int i;
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

    d.equip->n_equip=0;

    for(i=0;i<8;i++)
        d.equip.vect_equip[i]=NULL;

    return d;
}

void leggi_file_pg(pgList_t* tab_pg, FILE* fp){
    pg_t d;
    int prosegui=1;

    while(prosegui){
        d=new_pg(fp);
        if(pg_check_void(d))
            prosegui=0;
        else{
            add_player(&d,tab_pg);
            (tab_pg->nPg)++;
        }
    }

    return;
}

void add_player(pg_t* player, pgList_t* tab_pg){
    list_insert_tail(player,&(tab_pg->head),&(tab_pg->tail));
}

pg_t ricerca_player(char* str, pgList_t* tab_pg){
    return ricerca_codice(str,tab_pg->head);
}
pg_t estrai_player(char* str,pgList_t* tab_pg){
    return estrai_codice(str,&(tab_pg->head),&(tab_pg->tail));
}

/*Equip*/
void add_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv){
    link pg_link=ricerca_codice_link(player_name,tab_pg->head);
    if(pg_link==NULL){
        printf("Codice personaggio non trovato\n");
        return;
    }

    equip(&(pg_link->player.equip), &(pg_link->player.stats), object_name, tab_inv);

    stampa_pg(&(pg_link->player),stdout);
}

void remove_equip(char* player_name, char* object_name, pgList_t* tab_pg, invArray_t* tab_inv){
    link pg_link=ricerca_codice_link(player_name,tab_pg->head);
    if(pg_link==NULL){
        printf("Codice non trovato\n");
        return;
    }

    unequip(&(pg_link->player.equip), &(pg_link->player.stats), object_name, tab_inv);

    stampa_pg(&(pg_link->player),stdout);
}

/*Stampa*/
void stampa_players(pgList_t* tab_pg, FILE* fp){
    link x;
    for(x=tab_pg->head; x!=NULL; x=x->next)
        stampa_pg(&(x->player),fp);
}
