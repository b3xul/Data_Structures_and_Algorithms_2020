#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"

struct equipArray_s {
  int vettEquip[EQUIP_SLOT];
  int inUso;
};

equipArray_t equipArray_init() {
  int i;
  equipArray_t equipArray = calloc(1, sizeof(*equipArray));
  if (equipArray != NULL) {
    for(i=0;i<EQUIP_SLOT;i++) equipArray->vettEquip[i] = -1;
  }
  return equipArray;
}

void equipArray_free(equipArray_t equipArray) {
  if (equipArray != NULL)
    free(equipArray);
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
  int i;
  if (equipArray == NULL || invArray == NULL)
    return;
  if (equipArray->inUso > 0) {
    for(i=0;i<EQUIP_SLOT;i++) {
      if (equipArray->vettEquip[i] != -1) {
        invArray_printByIndex(fp, invArray, equipArray->vettEquip[i]);
      }
    }
  }
}

int equipArray_inUse(equipArray_t equipArray) {
  if (equipArray == NULL)
    return 0;
  return equipArray->inUso;
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray)  {
  int i, eq, operazione = -1;
  char nomeEq[LEN];
  printf("Che operazione vuoi svolgere?\n");
  if (equipArray->inUso > 0) printf("\t0 - Rimozione\n");
  if (equipArray->inUso < EQUIP_SLOT) printf("\t1 - Aggiunta\n");
  scanf("%d", &operazione);
  if (operazione == 0 && equipArray->inUso <= 0)
    return;
  if (operazione == 1 && equipArray->inUso >= EQUIP_SLOT)
    return;
  if (operazione != 0 && operazione != 1)
    return;

  printf("Inserire nome dell'equipaggiamento: ");
  scanf("%s", nomeEq);
  eq = invArray_searchByName(invArray, nomeEq);
  if (eq == -1) return;

  switch(operazione) {
    case 0: {
      for(i=0;i<EQUIP_SLOT;i++) {
        if (equipArray->vettEquip[i] == -1)
          continue;
        if (equipArray->vettEquip[i] == eq) {
          equipArray->inUso--;
          equipArray->vettEquip[i] = -1;
          break;
        }
      }
    } break;
    case 1: {
      for(i=0;i<EQUIP_SLOT;i++) {
        if (equipArray->vettEquip[i] == -1) {
          equipArray->vettEquip[i] = eq;
          equipArray->inUso++;
          break;
        }
      }
    }
    default:
      break;
  }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
  if (equipArray == NULL)
    return -1;
  if (equipArray->vettEquip == NULL)
    return -1;
  if (index < 0 || index >= EQUIP_SLOT)
    return -1;
  return equipArray->vettEquip[index];
}
