#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 100
#define MIN_STAT 1
#define EQUIP_SLOT 8
#define N_SCELTE 7
#define DBG 0

enum { falso, vero };
typedef int bool;

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

typedef struct tabEquip_s {
  inv_t **vettEquip;
  int inUso;
} tabEquip_t;

typedef struct pg_s {
  char *cod;
  char *nome;
  char *classe;
  stat_t b_stat, eq_stat;
  tabEquip_t *equip;
} pg_t;

typedef struct nodoPg_s* linkPg;
typedef struct nodoPg_s {
  pg_t pg;
  linkPg next;
} nodoPg_t;

typedef struct tabPg_s {
  linkPg head, tail;
	int nPg;
} tabPg_t;

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
  for(i=0;i<inv->nInv;i++)
	leggiInv(fp, &inv->vettInv[i]);
  fclose(fp);
  return inv;
}

int leggiPg(FILE *fp, pg_t *pg) {
  char classeTmp[LEN], nomeTmp[LEN], codTmp[LEN];
  if (pg == NULL)
    return 0;

  if (fscanf(fp, "%s %s %s", codTmp, nomeTmp, classeTmp) == 3){
    pg->cod = strdup(codTmp);
    pg->nome = strdup(nomeTmp);
    pg->classe = strdup(classeTmp);
    if (!leggiStat(fp, &(pg->b_stat)))
      return 0;
    pg->eq_stat = pg->b_stat;
    pg->equip = calloc(1, sizeof(tabEquip_t));
    pg->equip->vettEquip = calloc(EQUIP_SLOT, sizeof(inv_t*));
    return 1;
  }
  return 0;
}

linkPg newNodoPg(pg_t pg, linkPg next) {
  linkPg x = calloc(1, sizeof(*x));
  if (x == NULL)
    return NULL;
  x->pg = pg;
  x->next = next;
  return x;
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
  for(i=0;i<tabInv->nInv;i++)
    stampaInv(fp, tabInv->vettInv[i]);
}

void stampaPg(FILE *fp, pg_t pg) {
#if DBG
    int i;
#endif
  fprintf(fp, "%s <> %s [%s]\n\t BASE: ", pg.cod, pg.nome, pg.classe);
  stampaStat(fp, pg.b_stat, 1);
  if (pg.equip->inUso > 0) {
    fprintf(fp, "\t  +EQ: ");
    stampaStat(fp, pg.eq_stat, 1);
#if DBG
  for(i=0;i<EQUIP_SLOT;i++)
    if (pg.equip->vettEquip[i] != NULL)
      stampaInv(fp, *(pg.equip->vettEquip[i]));
#endif /* DBG */
  }
}

void stampaTabPg(FILE *fp, tabPg_t *tabPg) {
  linkPg x = NULL;
  if (tabPg == NULL)
    return;
  for (x=tabPg->head; x!=NULL; x=x->next)
    stampaPg(fp, x->pg);
}

int ricercaCodice(tabPg_t *tabPg, char* cod, pg_t *pg){
  linkPg x = NULL;
  if (tabPg == NULL)
    return 0;
  for (x = tabPg->head; x != NULL; x=x->next) {
    if (strcmp(x->pg.cod, cod) == 0) {
      *pg = x->pg;
      return 1;
    }
  }
  return 0;
}

int ricercaCodiceRef(tabPg_t *tabPg, char* cod, pg_t **pg){
  linkPg x = NULL;
  if (tabPg == NULL)
    return 0;
  for(x = tabPg->head; x != NULL; x=x->next) {
    if (strcmp(x->pg.cod, cod) == 0) {
      *pg = &(x->pg);
      return 1;
    }
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

void freeEquip(tabEquip_t *eq) {
  if (eq == NULL)
    return;
  free(eq->vettEquip);
  free(eq);
}

void freePg(pg_t pg) {
  if (pg.cod)
    free(pg.cod);
  if (pg.nome)
    free(pg.nome);
  if (pg.classe)
    free(pg.classe);
  if (pg.equip)
    freeEquip(pg.equip);
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
      for (i=0; i<EQUIP_SLOT; i++) {
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
      for (i=0; i<tabInv->nInv; i++) {
        if (strcmp(tabInv->vettInv[i].nome, nomeEq) == 0) {
          for (j=0; j<EQUIP_SLOT; j++) {
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
  for(i=0;i<EQUIP_SLOT;i++) {
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
	    freePg(x->pg);
	    free(x);
      break;
    }
  }
}


void stampaMenu(char *scelte[], int *selezione){
  int i=0;
  printf("\nMENU'\n");
  for(i=0;i<N_SCELTE;i++)
    printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}

int main(int argc, char **argv) {
  char *scelte[] = {
		"Uscita",
		"Stampa personaggi",
		"Stampa inventario",
		"Cerca personaggio",
		"Aggiungi personaggio",
		"Elimina personaggio",
        "Modifica equip"
	};

  char codiceRicerca[LEN];
  int selezione;
  bool fineProgramma;
  tabInv_t *tabInv;
  tabPg_t *tabPg;
  pg_t pg, *ppg;

  tabInv = leggiTabInventario("inventario.txt");
  if (tabInv == NULL)
	return 0;
#if DBG
	stampaTabInv(stdout, tabInv);
#endif /* DBG */

  tabPg = leggiTabPg("pg.txt");
  if (tabPg == NULL)
	return 0;
#if DBG
	stampaTabPg(stdout, tabPg);
#endif /* DBG */

  fineProgramma = falso;

  do {
		stampaMenu(scelte, &selezione);
		switch(selezione){

			case 0: {
				fineProgramma = vero;
		  } break;

			case 1: {
				stampaTabPg(stdout, tabPg);
			} break;

			case 2: {
				stampaTabInv(stdout, tabInv);
			} break;

			case 3: {
				printf("Inserire codice personaggio: ");
				scanf("%s", codiceRicerca);
                if(ricercaCodice(tabPg, codiceRicerca, &pg) != 0)
                  stampaPg(stdout, pg);
			} break;

			case 4: {
				aggiungi(tabPg);
			} break;

			case 5: {
				printf("Inserire codice personaggio: ");
				scanf("%s", codiceRicerca);
				elimina(tabPg, codiceRicerca);
			} break;

		  case 6: {
				printf("Inserire codice personaggio: ");
				scanf("%s", codiceRicerca);
                if (ricercaCodiceRef(tabPg, codiceRicerca, &ppg) != 0)
                  aggiornaPgEquip(ppg, tabInv);
			} break;

			default:{
				printf("Scelta non valida\n");
			} break;
		}
	} while(!fineProgramma);

  return 0;
}
