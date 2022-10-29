#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

#define MAX_STR 51
#include "obj.h"

typedef struct invArray_s invArray_t;

invArray_t* tab_inv_init();
void leggi_file_obj(invArray_t* tab, FILE* fp);
obj_t* ricerca_nome(char* str, invArray_t* tab);
void stampa_inventory(invArray_t* t, FILE* fp);

#endif // INVENTARIO_H_INCLUDED
