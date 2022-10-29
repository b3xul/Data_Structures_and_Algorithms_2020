#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

#include "obj.h"

typedef struct invArray_s invArray_t;

invArray_t* inventario_init();
void inventario_leggi(invArray_t* tab, FILE* fp);
obj_t* inventario_ricerca_nome(char* str, invArray_t* tab);
void inventario_stampa(invArray_t* t, FILE* fp);

/*ricerca_indice, stampa indice se equip contiene un vettore di indici, altrimenti uso direttamente puntatori*/

#endif // INVENTARIO_H_INCLUDED
