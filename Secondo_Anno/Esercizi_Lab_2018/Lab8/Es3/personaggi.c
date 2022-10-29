#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "personaggi.h"

/*EQUIP*/
void equip(link pg_link, obj_t* obj_p){
    int n;
    n=pg_link->player.equip.n_equip;
    if(n>=8){
        printf("Raggiunto numero massimo di oggetti equipaggiabili.\n");
        return;
    }
    pg_link->player.equip.vect_equip[n]=obj_p;
    pg_link->player.equip.n_equip++;

    pg_link->player.stats.hp+=obj_p->modifiers.hp;
    if(pg_link->player.stats.hp<1)
        pg_link->player.stats.hp=1;
    pg_link->player.stats.mp+=obj_p->modifiers.mp;
    if(pg_link->player.stats.mp<1)
        pg_link->player.stats.mp=1;
    pg_link->player.stats.atk+=obj_p->modifiers.atk;
    if(pg_link->player.stats.atk<1)
        pg_link->player.stats.atk=1;
    pg_link->player.stats.def+=obj_p->modifiers.def;
    if(pg_link->player.stats.def<1)
        pg_link->player.stats.def=1;
    pg_link->player.stats.mag+=obj_p->modifiers.mag;
    if(pg_link->player.stats.mag<1)
        pg_link->player.stats.mag=1;
    pg_link->player.stats.spr+=obj_p->modifiers.spr;
    if(pg_link->player.stats.spr<1)
        pg_link->player.stats.spr=1;
    //pg_link->player.equip.vect_equip[pg_link.player.equip.n_equip++]=obj_p;
}
void unequip(link pg_link, obj_t* obj_p){
    int i;
    for(i=0;i<pg_link->player.equip.n_equip;i++){
        if(pg_link->player.equip.vect_equip[i]==obj_p){
            pg_link->player.equip.vect_equip[i]=NULL;
            pg_link->player.equip.n_equip--;

            pg_link->player.stats.hp-=obj_p->modifiers.hp;
            if(pg_link->player.stats.hp<1)
                pg_link->player.stats.hp=1;
            pg_link->player.stats.mp-=obj_p->modifiers.mp;
            if(pg_link->player.stats.mp<1)
                pg_link->player.stats.mp=1;
            pg_link->player.stats.atk-=obj_p->modifiers.atk;
            if(pg_link->player.stats.atk<1)
                pg_link->player.stats.atk=1;
            pg_link->player.stats.def-=obj_p->modifiers.def;
            if(pg_link->player.stats.def<1)
                pg_link->player.stats.def=1;
            pg_link->player.stats.mag-=obj_p->modifiers.mag;
            if(pg_link->player.stats.mag<1)
                pg_link->player.stats.mag=1;
            pg_link->player.stats.spr-=obj_p->modifiers.spr;
            if(pg_link->player.stats.spr<1)
                pg_link->player.stats.spr=1;
            break;
        }
    }
}
/*PG*/
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

    d.equip.n_equip=0;

    for(i=0;i<8;i++)
        d.equip.vect_equip[i]=NULL;

    return d;
}

int leggi_file_pg(link* hp, link* tp, FILE* fp){
    pg_t d;
    int prosegui=1;
    int count=0;

    while(prosegui){
        d=new_pg(fp);
        if(pg_check_void(d))
            prosegui=0;
        else{
            list_insert_tail(&d,hp,tp);
            count++;
        }
    }

    return count;
}

/*Lista*/
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

link ricerca_codice(char* str, link h){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(!strcmp(str,x->player.codice))
            return x;
    }
    return NULL;
}

/*Stampa*/
void stampa_equip(equip_t* e, FILE* fp){
    int i;
    for(i=0;i<8;i++){
        if(e->vect_equip[i]!=NULL){
            printf("Oggetto %d: ",i);
            fprintf(fp,"%s\n",e->vect_equip[i]->nome);     //Non stampo tutte le stat per chiarezza ma basterebbe fare stampa_object(vect_equip[i])
        }
    }
}

void stampa_players(link h, link t, FILE* fp){
    link x;
    for(x=h; x!=NULL; x=x->next)
        stampa_pg_node_t(x,fp);
}

void stampa_pg_node_t(link x, FILE* fp){
    fprintf(fp,"%s %s %s\n",x->player.codice, x->player.nome, x->player.classe);
    stampa_stats(&x->player.stats,fp,0);
    stampa_equip(&x->player.equip,fp);
}

void stampa_pg(pg_t* x, FILE* fp){
    fprintf(fp,"%s %s %s\n",x->codice, x->nome, x->classe);
    stampa_stats(&x->stats,fp,0);
    stampa_equip(&x->equip,fp);
}

