#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define N_OPERATIONS 8
#define MAX_STR 51

typedef struct statistics{
    int hp; int mp; int atk; int def; int mag; int spr;
}stat_t;

typedef struct object{
    char* nome; char* tipo; stat_t modifiers;
}obj_t;

typedef struct inventory_wrapper{
    obj_t* inventory;
    int nInv;
    int maxInv;
}tabInv;

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

/*Obj*/
void leggi_file_obj(tabInv* tab, FILE* fp);
obj_t* ricerca_nome(char* str, tabInv tab);
/*EQUIP*/
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
/*Stampe*/
void stampa_players(link h, link t, FILE* fp);
void stampa_pg_node_t(link x, FILE* fp);
void stampa_pg(pg_t* x, FILE* fp);
void stampa_stats(stat_t* s, FILE* fp, int type);
void stampa_inventory(tabInv t, FILE* fp);
void stampa_object(obj_t* o, FILE* fp);
void stampa_equip(equip_t* e, FILE* fp);

//PG0130 Basco Robrasco 8000 400 1 5 90000 25
int main()
{
    char* prompt[N_OPERATIONS]={"Caricare l'elenco di personaggi (da file)",
                    "Caricare l'elenco di oggetti (da file)",
                    "Aggiungere un nuovo personaggio",
                    "Eliminare un personaggio",
                    "Aggiungere un oggetto dall'equipaggiamento di un personaggio",
                    "Rimuovere un oggetto dall'equipaggiamento di un personaggio",
                    "Mostrare le statistiche di un personaggio",
                    "Termina il programma"};

    tabInv tab_inv;
    tab_inv.inventory=NULL;
    tab_inv.maxInv=tab_inv.nInv=0;

    tabPg tab_pg;
    tab_pg.head=tab_pg.tail=NULL;
    tab_pg.nPg=0;

    int i,cmd;
    char target[MAX_STR];
    FILE* fp;
    pg_t player;
    link pg_link;
    obj_t* obj_p;

    do{
        for(i=0; i<N_OPERATIONS; i++){
            printf("%d: %s\n", i, prompt[i]);
        }
        printf("Inserire comando> ");
        scanf("%d",&cmd);
        switch(cmd){
            case 0:
                printf("Inserire nome file: ");
                scanf("%s",target);
                fp=fopen(target,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                tab_pg.nPg+=leggi_file_pg(&tab_pg.head, &tab_pg.tail, fp);
                stampa_players(tab_pg.head, tab_pg.tail, stdout);
                break;
            case 1:
                printf("Inserire nome file: ");
                scanf("%s",target);
                fp=fopen(target,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                leggi_file_obj(&tab_inv, fp);
                stampa_inventory(tab_inv, stdout);
                break;
            case 2:
                printf("Inserire nuovo personaggio nel formato <codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>:\n");
                player=new_pg(stdin);
                list_insert_tail(&player,&tab_pg.head,&tab_pg.tail);
                stampa_players(tab_pg.head, tab_pg.tail, stdout);
                break;
            case 3:
                printf("Inserire codice del personaggio che si vuole eliminare: ");
                scanf("%s",target);
                player=estrai_codice(target,&tab_pg.head,&tab_pg.tail);
                if(pg_check_void(player))
                    printf("Codice non trovato\n");
                else{
                    printf("Elimino: ");
                    stampa_pg(&player,stdout);
                    printf("Nuova lista personaggi: \n");
                }
                stampa_players(tab_pg.head, tab_pg.tail, stdout);
                break;
            case 4:
                printf("Inserire codice del personaggio a cui si vuole equipaggiare un oggetto: ");
                scanf("%s",target);
                pg_link=ricerca_codice(target,tab_pg.head);
                if(pg_link==NULL){
                    printf("Codice non trovato\n");
                    break;
                }

                printf("Inserire nome dell'oggetto da equipaggiare: ");
                scanf("%s",target);
                obj_p=ricerca_nome(target,tab_inv);
                if(obj_p==NULL){
                    printf("Nome non trovato\n");
                    break;
                }

                equip(pg_link,obj_p);
                stampa_pg_node_t(pg_link,stdout);
                break;
            case 5:
                printf("Inserire codice del personaggio a cui si vuole rimuovere un oggetto: ");
                scanf("%s",target);
                pg_link=ricerca_codice(target,tab_pg.head);
                if(pg_link==NULL){
                    printf("Codice non trovato\n");
                    break;
                }

                printf("Inserire nome dell'oggetto da rimuovere: ");
                scanf("%s",target);
                obj_p=ricerca_nome(target,tab_inv);
                if(obj_p==NULL){
                    printf("Nome non trovato\n");
                    break;
                }

                unequip(pg_link,obj_p);
                stampa_pg_node_t(pg_link,stdout);
                break;
                break;
            case 6:
                printf("Inserire codice del personaggio di cui si vuole sapere le statistiche: ");
                scanf("%s",target);
                pg_link=ricerca_codice(target,tab_pg.head);
                stampa_pg_node_t(pg_link,stdout);
                break;
            case 7:
                break;
            default:
                printf("Comando non riconosciuto\n");
                break;
        }
        printf("\n");
    }
    while(cmd!=7);

    return 0;
}
/*Obj*/
void leggi_file_obj(tabInv* tab, FILE* fp){
    obj_t d;
    int i;
    char buffer[MAX_STR];

    fscanf(fp,"%d",&tab->maxInv);

    tab->inventory=(obj_t*)malloc(tab->maxInv*sizeof(obj_t));
    if(tab->inventory==NULL){
        fprintf(stderr,"Errore allocazione inventario\n");
        return;
    }

    for(i=0;i<tab->maxInv;i++){
        fscanf(fp,"%s",buffer);
        d.nome=strdup(buffer);

        fscanf(fp,"%s",buffer);
        d.tipo=strdup(buffer);

        fscanf(fp,"%d%d%d%d%d%d",&d.modifiers.hp,&d.modifiers.mp,&d.modifiers.atk,&d.modifiers.def,&d.modifiers.mag,&d.modifiers.spr);

        tab->inventory[i]=d;
        tab->nInv++;
    }

    return;
}

obj_t* ricerca_nome(char* str, tabInv tab){
    int i;
    for(i=0;i<tab.nInv;i++){
        if(!strcmp(str,tab.inventory[i].nome))
            return &tab.inventory[i];
    }
    return NULL;
}
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
/*Stampe*/
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
void stampa_stats(stat_t* s, FILE* fp, int type){   //0: pg, 1: obj
    //TO-DO: statistiche nel formato statbase(+modifiers)
    if(type==0)
        fprintf(fp,"HP:%d   MP:%d   ATK:%d   DEF:%d   MAG:%d   SPR:%d\n",s->hp,s->mp,s->atk,s->def,s->mag,s->spr);
    else
        fprintf(fp,"HP:%s%d   MP:%s%d   ATK:%s%d   DEF:%s%d   MAG:%s%d   SPR:%s%d\n",(s->hp>0)?"+":"",s->hp,(s->mp>0)?"+":"",s->mp,(s->atk>0)?"+":"",s->atk,(s->def>0)?"+":"",s->def,(s->mag>0)?"+":"",s->mag,(s->spr>0)?"+":"",s->spr);
}

void stampa_equip(equip_t* e, FILE* fp){
    int i;
    for(i=0;i<8;i++){
        if(e->vect_equip[i]!=NULL){
            printf("Oggetto %d: ",i);
            fprintf(fp,"%s\n",e->vect_equip[i]->nome);     //Non stampo tutte le stat per chiarezza ma basterebbe fare stampa_object(vect_equip[i])
        }
    }
}
void stampa_inventory(tabInv t, FILE* fp){
    int i;
    for(i=0;i<t.nInv;i++)
        stampa_object(&t.inventory[i], fp);
}

void stampa_object(obj_t* o, FILE* fp){
    fprintf(fp,"%s %s\n",o->nome,o->tipo);
    stampa_stats(&(o->modifiers),fp,1);
}
