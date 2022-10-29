#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pg.h"

static void pg_updateStatEquip(pg_t *pgp, invArray_t invArray) {
  int i, eqIndex;
  inv_t *invp;
  stat_t equipStat;
  pgp->eq_stat = pgp->b_stat;
  for(i=0;i<EQUIP_SLOT;i++) {
    eqIndex = equipArray_getEquipByIndex(pgp->equip, i);
    if (eqIndex == -1)
      continue;
    invp = invArray_getByIndex(invArray, eqIndex);
    if (invp == NULL)
      continue;
    equipStat = inv_getStat(invp);
    pgp->eq_stat = stat_add(pgp->eq_stat, equipStat);
  }
}

int pg_read(FILE *fp, pg_t *pgp) {
  if (fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe) < 3)
    return 0;
  stat_read(fp, &(pgp->b_stat));
  pgp->eq_stat = pgp->b_stat;
  pgp->equip = equipArray_init();
  return 1;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
  if (pgp == NULL)
    return;
  fprintf(fp, "%s <> %s [%s]\n\t BASE: ", pgp->cod, pgp->nome, pgp->classe);
  stat_print(fp, &pgp->b_stat, 1);
  if (equipArray_inUse(pgp->equip) > 0) {
    fprintf(fp, "\t  +EQ: ");
    stat_print(fp, &pgp->eq_stat, 1);
    if (pgp->equip!=NULL)
      equipArray_print(fp, pgp->equip, invArray);
  }
}

void pg_clean(pg_t *pgp) {
  if (pgp->equip!=NULL)
    equipArray_free(pgp->equip);
  pgp->equip = NULL;
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
  equipArray_update(pgp->equip, invArray);
  pg_updateStatEquip(pgp, invArray);
}
