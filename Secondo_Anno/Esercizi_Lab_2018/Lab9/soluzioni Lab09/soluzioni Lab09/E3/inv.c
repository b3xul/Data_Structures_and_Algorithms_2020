#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

void stat_read(FILE *fp, stat_t *sp) {
  fscanf(fp, "%d %d %d %d %d %d",
         &sp->hp, &sp->mp, &sp->atk, &sp->def, &sp->mag, &sp->spr);
}

void stat_print(FILE *fp, stat_t *sp, int soglia) {
  if (soglia)
    fprintf(fp, "HP = %d, MP = %d, ATK = %d, DEF = %d, MAG = %d, SPR = %d\n",
            (sp->hp > 0 ? sp->hp : MIN_STAT), (sp->mp > 0 ? sp->mp : MIN_STAT),
            (sp->atk > 0 ? sp->atk : MIN_STAT), (sp->def > 0 ? sp->def : MIN_STAT),
            (sp->mag > 0 ? sp->mag : MIN_STAT), (sp->spr > 0 ? sp->spr : MIN_STAT));
  else
    fprintf(fp, "HP = %d, MP = %d, ATK = %d, DEF = %d, MAG = %d, SPR = %d\n",
            sp->hp, sp->mp, sp->atk, sp->def, sp->mag, sp->spr);
}

stat_t stat_add(stat_t sa, stat_t sb) {

  sa.hp += sb.hp;
  sa.mp += sb.mp;
  sa.atk += sb.atk;
  sa.def += sb.def;
  sa.mag += sb.mag;
  sa.spr += sb.spr;

  return sa;
}

void inv_read(FILE *fp, inv_t *ip) {
  fscanf(fp, "%s %s", ip->nome, ip->tipo);
  stat_read(fp, &(ip->stat));
}

void inv_print(FILE *fp, inv_t *ip) {
  fprintf(fp, "%s [%s]\n\t", ip->nome, ip->tipo);
  stat_print(fp, &(ip->stat), 0);
}

stat_t inv_getStat(inv_t *invp) {
  return invp->stat;
}

