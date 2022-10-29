#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

int leggiStat(FILE *fp, stat_t *stat) {
  if (stat == NULL)
    return 0;
  return (fscanf(fp, "%d %d %d %d %d %d", &stat->hp, &stat->mp, &stat->atk, &stat->def, &stat->mag, &stat->spr) == 6);
}

void leggiInv(FILE *fp, inv_t *inv) {
  char nomeTmp[LEN], tipoTmp[LEN];
  if (inv == NULL)
    return;


  fscanf(fp, "%s %s", nomeTmp, tipoTmp);
  inv->nome = strdup(nomeTmp);
  inv->tipo = strdup(tipoTmp);
  leggiStat(fp, &(inv->stat));
}

tabInv_t *leggiTabInventario(char *filename) {
  int i;
  tabInv_t *inv = calloc(1, sizeof(tabInv_t));
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    return NULL;
  fscanf(fp, "%d", &inv->nInv);
  inv->vettInv = calloc(inv->nInv, sizeof(inv_t));
  for (i=0; i<inv->nInv; i++)
  	leggiInv(fp, &inv->vettInv[i]);
  fclose(fp);
  return inv;
}

void stampaStat(FILE *fp, stat_t s, int soglia) {
  if (soglia)
	fprintf(fp, "HP = %d, MP = %d, ATK = %d, DEF = %d, MAG = %d, SPR = %d\n", (s.hp > 0 ? s.hp : MIN_STAT), (s.mp > 0 ? s.mp : MIN_STAT), (s.atk > 0 ? s.atk : MIN_STAT), (s.def > 0 ? s.def : MIN_STAT), (s.mag > 0 ? s.mag : MIN_STAT), (s.spr > 0 ? s.spr : MIN_STAT));
  else
    fprintf(fp, "HP = %d, MP = %d, ATK = %d, DEF = %d, MAG = %d, SPR = %d\n", s.hp, s.mp, s.atk, s.def, s.mag, s.spr);
}

void stampaInv(FILE *fp, inv_t inv) {
  fprintf(fp, "%s [%s]\n\t", inv.nome, inv.tipo);
  stampaStat(fp, inv.stat, 0);
}

void stampaTabInv(FILE *fp, tabInv_t *tabInv) {
  int i;
  if (tabInv == NULL)
    return;
  for (i=0; i<tabInv->nInv; i++)
    stampaInv(fp, tabInv->vettInv[i]);
}
