#ifndef INVARRAY_H_DEFINED
#define INVARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

typedef struct invArray_s *invArray_t;

invArray_t invArray_init();
void invArray_read(char *filename, invArray_t invArray);
void invArray_print(FILE *fp, invArray_t invArray);
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index);
inv_t *invArray_getByIndex(invArray_t invArray, int index);
int invArray_searchByName(invArray_t invArray, char *name);

#endif
