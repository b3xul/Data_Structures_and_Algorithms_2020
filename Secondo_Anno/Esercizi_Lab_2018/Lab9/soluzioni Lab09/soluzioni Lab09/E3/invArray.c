#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "invArray.h"

struct invArray_s {
  inv_t *vettInv;
  int nInv;
  int maxInv;
};

invArray_t invArray_init() {
  invArray_t invArray = calloc(1, sizeof(*invArray));
  return invArray;
}

void invArray_read(char *filename, invArray_t invArray) {
  int i;
  FILE *fp = fopen(filename, "r");
  if (invArray == NULL)
    return;
  if (fp == NULL)
    return;
  fscanf(fp, "%d", &invArray->nInv);
  invArray->vettInv = calloc(invArray->nInv, sizeof(inv_t));
  for(i=0;i<invArray->nInv;i++) {
    inv_read(fp, &invArray->vettInv[i]);
  }
  fclose(fp);
  return;
}

void invArray_print(FILE *fp, invArray_t invArray) {
  int i;
  if (invArray == NULL)
    return;
  for(i=0;i<invArray->nInv;i++)
    inv_print(fp, &invArray->vettInv[i]);
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
  if (invArray == NULL)
    return;
  inv_print(fp, &invArray->vettInv[index]);
}

int invArray_searchByName(invArray_t invArray, char *name) {
  int i;
  if (invArray == NULL || name == NULL)
    return -1;
  for(i=0;i<invArray->nInv;i++) {
    if (strcmp(invArray->vettInv[i].nome, name) == 0)
      return i;
  }
  return -1;
}

inv_t *invArray_getByIndex(invArray_t invArray, int index) {
  if (invArray == NULL)
    return NULL;
  if (invArray->vettInv == NULL)
    return NULL;
  if (index < 0 || index >= invArray->nInv)
    return NULL;
  return &invArray->vettInv[index];
}
