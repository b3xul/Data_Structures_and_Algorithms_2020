#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_STR 51
#define MIN_STAT 1
/*Stat_t e obj_t quasi_adt*/

typedef struct statistics{
    int hp; int mp; int atk; int def; int mag; int spr;
}stat_t;

typedef struct object{
    char* nome; char* tipo; stat_t modifiers;
}obj_t;

obj_t obj_leggi(FILE* fp);
stat_t obj_leggi_stats(FILE* fp);
void obj_stampa(obj_t* o, FILE* fp);
void obj_stampa_stats(stat_t* s, FILE* fp, int type);

#endif // OBJ_H_INCLUDED
