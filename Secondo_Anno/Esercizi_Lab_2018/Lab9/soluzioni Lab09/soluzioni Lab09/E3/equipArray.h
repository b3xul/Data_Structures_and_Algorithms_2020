#ifndef EQUIPARRAY_H_DEFINED
#define EQUIPARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EQUIP_SLOT 8

#include "invArray.h"

typedef struct equipArray_s *equipArray_t; 

equipArray_t equipArray_init();
void equipArray_free(equipArray_t equipArray);
int equipArray_inUse(equipArray_t equipArray);
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray);
void equipArray_update(equipArray_t equipArray, invArray_t invArray);
int equipArray_getEquipByIndex(equipArray_t equipArray, int index);

#endif
