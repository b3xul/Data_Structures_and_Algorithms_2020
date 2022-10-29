#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pg.h"

int leggiPg(FILE *fp, pg_t *pg) {
  char classeTmp[LEN], nomeTmp[LEN], codTmp[LEN];
  if (pg == NULL)
    return 0;
  if (fscanf(fp, "%s %s %s", codTmp, nomeTmp, classeTmp) == 3){
    pg->cod = strdup(codTmp);
    pg->nome = strdup(nomeTmp);
    pg->classe = strdup(classeTmp);
	  if (!leggiStat(fp, &(pg->b_stat))) return 0;
    pg->eq_stat = pg->b_stat;

    pg->equip = calloc(1, sizeof(tabEquip_t));
    pg->equip->vettEquip = calloc(EQUIP_SLOT, sizeof(inv_t*));

    return 1;
  }

  return 0;
}

linkPg newNodoPg(pg_t pg, linkPg next) {
  linkPg n = calloc(1, sizeof(*n));
  if (n == NULL)
    return NULL;
  n->pg = pg;
  n->next = next;
  return n;
}

void inserisciInListaPg(tabPg_t *tabPg, pg_t pg) {
  linkPg toAdd;
  toAdd = newNodoPg(pg, NULL);
  if (toAdd == NULL || tabPg == NULL)
    return;
  if(tabPg->head == NULL)
    tabPg->head = tabPg->tail = toAdd;
  else {
    tabPg->tail->next = toAdd;
    tabPg->tail = toAdd;
  }
}


tabPg_t *leggiTabPg(char *filename) {
  tabPg_t *tabPg = calloc(1, sizeof(tabPg_t));
  pg_t pgtmp;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    return NULL;

  while(leggiPg(fp, &pgtmp) != 0) {
    inserisciInListaPg(tabPg, pgtmp);
    tabPg->nPg++;
  }

  fclose(fp);
  return tabPg;
}

void stampaPg(FILE *fp, pg_t pg) {
  int i;
  fprintf(fp, "%s <> %s [%s]\n\t BASE: ", pg.cod, pg.nome, pg.classe);
  stampaStat(fp, pg.b_stat, 1);
  if (pg.equip->inUso > 0) {
    fprintf(fp, "\t  +EQ: ");
    stampaStat(fp, pg.eq_stat, 1);
    for (i=0; i<EQUIP_SLOT; i++)
      if (pg.equip->vettEquip[i] != NULL)
        stampaInv(fp, *(pg.equip->vettEquip[i]));
  }
}

void stampaTabPg(FILE *fp, tabPg_t *tabPg) {
  linkPg x = NULL;
  if (tabPg == NULL)
    return;
  for(x=tabPg->head; x!=NULL; x=x->next)
    stampaPg(fp, x->pg);
}

int ricercaCodice(tabPg_t *tabPg, char* cod, pg_t *pg){
  linkPg x = NULL;
  if (tabPg == NULL)
    return 0;
  for(x = tabPg->head; x != NULL; x=x->next)
    if (strcmp(x->pg.cod, cod) == 0) {
      *pg = x->pg;
      return 1;
    }
  return 0;
}

int ricercaCodiceRef(tabPg_t *tabPg, char* cod, pg_t **pg){
  linkPg x = NULL;
  if (tabPg == NULL)
    return 0;
  for (x = tabPg->head; x != NULL; x=x->next)
    if (strcmp(x->pg.cod, cod) == 0) {
      *pg = &(x->pg);
      return 1;
    }
  return 0;
}

void aggiungi(tabPg_t *tabPg){
  pg_t pg;

  printf("Cod Nome Classe HP MP ATK DEF MAG SPR: ");
  if (leggiPg(stdin, &pg)) {
    /* Eventuale invocazione qui di ricercaCodice() per check duplicati */
    inserisciInListaPg(tabPg, pg);
  }
}

void liberaEquip(tabEquip_t *eq) {
  if (eq == NULL)
    return;
  free(eq->vettEquip);
  free(eq);
}

void liberaPg(pg_t pg) {
  if (pg.cod)
    free(pg.cod);
  if (pg.nome)
    free(pg.nome);
  if (pg.classe)
    free(pg.classe);
  if (pg.equip)
    liberaEquip(pg.equip);
}

void modificaTabEquip(tabEquip_t *equip, tabInv_t *tabInv) {
  int i, j, operazione = -1;
  char nomeEq[LEN];
  printf("Che operazione vuoi svolgere?\n");
  if (equip->inUso > 0)
    printf("\t0 - Rimozione\n");
  if (equip->inUso < EQUIP_SLOT)
    printf("\t1 - Aggiunta\n");
  scanf("%d", &operazione);
  if (operazione == 0 && equip->inUso <= 0)
    return;
  if (operazione == 1 && equip->inUso >= EQUIP_SLOT)
    return;
  if (operazione != 0 && operazione != 1)
    return;

  printf("Inserire nome dell'equipaggiamento: ");
  scanf("%s", nomeEq);
  switch(operazione) {
    case 0: {
      for(i=0;i<EQUIP_SLOT;i++) {
        if (equip->vettEquip[i] == NULL)
          continue;
        if (strcmp(equip->vettEquip[i]->nome, nomeEq) == 0) {
          equip->inUso--;
          equip->vettEquip[i] = NULL;
          break;
        }
      }
    } break;
    case 1: {
      for(i=0;i<tabInv->nInv;i++) {
        if (strcmp(tabInv->vettInv[i].nome, nomeEq) == 0) {
          for(j=0;j<EQUIP_SLOT;j++) {
            if (equip->vettEquip[j] == NULL) {
              equip->vettEquip[j] = &(tabInv->vettInv[i]);
              equip->inUso++;
              break;
            }
          }
          break;
        }
      }
    } break;
    default:
      break;
  }

}

void aggiornaPgStatEquip(pg_t *pg) {
  int i;
  pg->eq_stat = pg->b_stat;
  for (i=0; i<EQUIP_SLOT; i++) {
    if (pg->equip->vettEquip[i] == NULL)
      continue;
    pg->eq_stat.hp += pg->equip->vettEquip[i]->stat.hp;
    pg->eq_stat.mp += pg->equip->vettEquip[i]->stat.mp;
    pg->eq_stat.atk += pg->equip->vettEquip[i]->stat.atk;
    pg->eq_stat.def += pg->equip->vettEquip[i]->stat.def;
    pg->eq_stat.mag += pg->equip->vettEquip[i]->stat.mag;
    pg->eq_stat.spr += pg->equip->vettEquip[i]->stat.spr;
  }
}

void aggiornaPgEquip(pg_t *pg, tabInv_t *tabInv) {
  modificaTabEquip(pg->equip, tabInv);
  aggiornaPgStatEquip(pg);
}

void elimina(tabPg_t *tabPg_t, char* cod){
  linkPg x, p;
  for(x = tabPg_t->head, p = NULL; x != NULL; p = x, x=x->next) {
    if (strcmp(x->pg.cod, cod) == 0) {
	    if (x == tabPg_t->head && x == tabPg_t->tail) {
		    tabPg_t->head = tabPg_t->tail = NULL;
	    } else if (x == tabPg_t->head) {
		    tabPg_t->head = x->next;
	    } else if (x == tabPg_t->tail) {
		    tabPg_t->tail = p;
		    p->next = NULL;
	    } else {
	      p->next = x->next;
	    }
	    liberaPg(x->pg);
	    free(x);
      break;
    }
  }
}

