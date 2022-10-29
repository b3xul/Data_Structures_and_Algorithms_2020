#include "equipment.h"

typedef struct equip_s{
    obj_t* vect_equip[8];
    int n_equip;
}equip_t;

/*EQUIP*/
void equip(equip_t* field_equip, stat_t* field_stats, char* object_name, invArray_t* tab_inv){
    obj_t* obj_p=ricerca_nome(object_name,tab_inv);
    if(obj_p==NULL){
        printf("Nome_oggetto non trovato\n");
        return;
    }

    int n;
    n=field_equip->n_equip;

    if(n>=8){
        printf("Raggiunto numero massimo di oggetti equipaggiabili.\n");
        return;
    }
    field_equip->vect_equip[n]=obj_p;
    field_equip->n_equip++;

    field_stats->hp+=obj_p->modifiers.hp;
    if(field_stats->hp<1)
        field_stats->hp=1;
    field_stats->mp+=obj_p->modifiers.mp;
    if(field_stats->mp<1)
        field_stats->mp=1;
    field_stats->atk+=obj_p->modifiers.atk;
    if(field_stats->atk<1)
        field_stats->atk=1;
    field_stats->def+=obj_p->modifiers.def;
    if(field_stats->def<1)
        field_stats->def=1;
    field_stats->mag+=obj_p->modifiers.mag;
    if(field_stats->mag<1)
        field_stats->mag=1;
    field_stats->spr+=obj_p->modifiers.spr;
    if(field_stats->spr<1)
        field_stats->spr=1;
    //field_equip.vect_equip[pg_link.player.equip.n_equip++]=obj_p;
}

void unequip(equip_t* field_equip, stat_t* field_stats, char* object_name, invArray_t* tab_inv){
    obj_t* obj_p=ricerca_nome(object_name,tab_inv);
    if(obj_p==NULL){
        printf("Nome_oggetto non trovato\n");
        return;
    }
    int i;
    for(i=0;i<field_equip->n_equip;i++){
        if(field_equip->vect_equip[i]==obj_p){
            field_equip->vect_equip[i]=NULL;
            field_equip->n_equip--;

            field_stats->hp-=obj_p->modifiers.hp;
            if(field_stats->hp<1)
                field_stats->hp=1;
            field_stats->mp-=obj_p->modifiers.mp;
            if(field_stats->mp<1)
                field_stats->mp=1;
            field_stats->atk-=obj_p->modifiers.atk;
            if(field_stats->atk<1)
                field_stats->atk=1;
            field_stats->def-=obj_p->modifiers.def;
            if(field_stats->def<1)
                field_stats->def=1;
            field_stats->mag-=obj_p->modifiers.mag;
            if(field_stats->mag<1)
                field_stats->mag=1;
            field_stats->spr-=obj_p->modifiers.spr;
            if(field_stats->spr<1)
                field_stats->spr=1;
            break;
        }
    }
}

void stampa_equip(equip_t* e, FILE* fp){
    int i;
    for(i=0;i<8;i++){
        if(e->vect_equip[i]!=NULL){
            printf("Oggetto %d: ",i);
            fprintf(fp,"%s\n",e->vect_equip[i]->nome);     //Non stampo tutte le stat per chiarezza ma basterebbe fare obj_stampa(vect_equip[i])
        }
    }
}
