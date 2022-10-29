#ifndef EQUIPMENT_H_INCLUDED
#define EQUIPMENT_H_INCLUDED

#include "inventario.h"

typedef struct equip_s equip_t;

void equip(equip_t* field_equip, stat_t* field_stats, char* object_name, invArray_t* tab_inv);
void unequip(equip_t* field_equip, stat_t* field_stats, char* object_name, invArray_t* tab_inv);

void stampa_equip(equip_t* e, FILE* fp);
#endif // EQUIPMENT_H_INCLUDED
