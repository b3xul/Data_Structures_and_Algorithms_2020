#include "equipment.h"

struct equip_s{
    obj_t* vect_equip[EQUIP_SLOTS];
    int n_equip;
};  /*Non serve dire anche qua che si parla di equip_t*/

/*EQUIP*/

equip_t* equip_init(){
    int i;
    equip_t* d=(equip_t*)malloc(sizeof(equip_t));

    d->n_equip=0;

    for(i=0;i<EQUIP_SLOTS;i++)
        d->vect_equip[i]=NULL;

    return d;
}

void equip(equip_t* field_equip, stat_t* field_stats, char* object_name, invArray_t* tab_inv){
    obj_t* obj_p=inventario_ricerca_nome(object_name,tab_inv);
    if(obj_p==NULL){
        printf("Nome oggetto non trovato\n");
        return;
    }
    else
        obj_stampa(obj_p,stdout);

    int n;
    n=field_equip->n_equip;

    if(n>=EQUIP_SLOTS){
        printf("Raggiunto numero massimo di oggetti equipaggiabili.\n");
        return;
    }
    field_equip->vect_equip[n]=obj_p;
    field_equip->n_equip++;

    /*Si potrebbe fare stat_add(field_stats,obj_p->modifiers)*/
    field_stats->hp+=obj_p->modifiers.hp;
    field_stats->hp=(field_stats->hp >= MIN_STAT) ? field_stats->hp : MIN_STAT;

    field_stats->mp+=obj_p->modifiers.mp;
    field_stats->mp=(field_stats->mp >= MIN_STAT) ? field_stats->mp : MIN_STAT;

    field_stats->atk+=obj_p->modifiers.atk;
    field_stats->atk=(field_stats->atk >= MIN_STAT) ? field_stats->atk : MIN_STAT;

    field_stats->def+=obj_p->modifiers.def;
    field_stats->def=(field_stats->def >= MIN_STAT) ? field_stats->def : MIN_STAT;

    field_stats->mag+=obj_p->modifiers.mag;
    field_stats->mag=(field_stats->mag >= MIN_STAT) ? field_stats->mag : MIN_STAT;

    field_stats->spr+=obj_p->modifiers.spr;
    field_stats->spr=(field_stats->spr >= MIN_STAT) ? field_stats->spr : MIN_STAT;
    //field_equip.vect_equip[pg_link.player.equip.n_equip++]=obj_p;
}

void unequip(equip_t* field_equip, stat_t* field_stats, char* object_name, invArray_t* tab_inv){
    obj_t* obj_p=inventario_ricerca_nome(object_name,tab_inv);
    if(obj_p==NULL){
        printf("Nome_oggetto non trovato\n");
        return;
    }
    else
        obj_stampa(obj_p,stdout);

    int i;
    for(i=0;i<field_equip->n_equip;i++){
        if(field_equip->vect_equip[i]==obj_p){
            field_equip->vect_equip[i]=NULL;
            field_equip->n_equip--;

            field_stats->hp-=obj_p->modifiers.hp;
            field_stats->hp=(field_stats->hp >= MIN_STAT) ? field_stats->hp : MIN_STAT;

            field_stats->mp-=obj_p->modifiers.mp;
            field_stats->mp=(field_stats->mp >= MIN_STAT) ? field_stats->mp : MIN_STAT;

            field_stats->atk-=obj_p->modifiers.atk;
            field_stats->atk=(field_stats->atk >= MIN_STAT) ? field_stats->atk : MIN_STAT;

            field_stats->def-=obj_p->modifiers.def;
            field_stats->def=(field_stats->def >= MIN_STAT) ? field_stats->def : MIN_STAT;

            field_stats->mag-=obj_p->modifiers.mag;
            field_stats->mag=(field_stats->mag >= MIN_STAT) ? field_stats->mag : MIN_STAT;

            field_stats->spr-=obj_p->modifiers.spr;
            field_stats->spr=(field_stats->spr >= MIN_STAT) ? field_stats->spr : MIN_STAT;
            break;
        }
    }
}

void stampa_equip(equip_t** e, FILE* fp){
    int i;
    for(i=0;i<EQUIP_SLOTS;i++){
        if((*e)->vect_equip[i]!=NULL){
            printf("Oggetto %d: ",i);
            fprintf(fp,"%s\n",(*e)->vect_equip[i]->nome);     //Non stampo tutte le stat per chiarezza ma basterebbe fare obj_stampa(vect_equip[i])
        }
    }
}
