#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

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

void leggi_file_obj(tabInv* tab, FILE* fp);
obj_t* ricerca_nome(char* str, tabInv tab);
void stampa_inventory(tabInv t, FILE* fp);
void stampa_object(obj_t* o, FILE* fp);
void stampa_stats(stat_t* s, FILE* fp, int type);

#endif // INVENTARIO_H_INCLUDED
