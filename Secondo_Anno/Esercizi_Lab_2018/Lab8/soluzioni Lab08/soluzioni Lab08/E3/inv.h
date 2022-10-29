#ifndef INV_H_DEFINED
#define INV_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 100
#define MIN_STAT 1

typedef struct stat_s {
  int hp, mp, atk, def, mag, spr;
} stat_t;

typedef struct inv_s {
  char *nome;
  char *tipo;
  stat_t stat;
} inv_t;

typedef struct tabInv_s {
  inv_t *vettInv;
  int nInv;
} tabInv_t;

int leggiStat(FILE *fp, stat_t *stat);
void stampaStat(FILE *fp, stat_t s, int soglia);
void leggiInv(FILE *fp, inv_t *inv);
tabInv_t *leggiTabInventario(char *filename);
void stampaInv(FILE *fp, inv_t inv);
void stampaTabInv(FILE *fp, tabInv_t *tabInv);

#endif
