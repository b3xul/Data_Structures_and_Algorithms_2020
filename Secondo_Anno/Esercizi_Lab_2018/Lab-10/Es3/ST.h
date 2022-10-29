#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"

typedef struct SymbolTable* ST;

ST ST_init(int maxN);
void ST_insert(ST st, Item x);
int ST_search(ST st, Item x);
Item ST_search_by_index(ST st, int index);
int ST_count(ST st);
void ST_store(ST st, Item x);
void ST_store_by_index(ST st, int index);
void ST_free(ST st);
#endif // ST_H_INCLUDED
