#ifndef PGLIST_H_DEFINED
#define PGLIST_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pg.h"

typedef struct pgList_s *pgList_t;

pgList_t pgList_init();
void pgList_insert(pgList_t pgList, pg_t pg); 
void pgList_read(char *filename, pgList_t pgList);
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray);
void pgList_add(pgList_t pgList);
void pgList_remove(pgList_t pgList, char* cod);
void pgList_free(pgList_t pgList);
pg_t *pgList_searchByCode(pgList_t pgList, char* cod);

#endif
