#ifndef PG_H_DEFINED
#define PG_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

#define EQUIP_SLOT 8

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

int leggiPg(FILE *fp, pg_t *pg);
linkPg newNodoPg(pg_t pg, linkPg next);
void inserisciInListaPg(tabPg_t *tabPg, pg_t pg);
tabPg_t *leggiTabPg(char *filename);
void stampaPg(FILE *fp, pg_t pg);
void stampaTabPg(FILE *fp, tabPg_t *tabPg);
int ricercaCodice(tabPg_t *tabPg, char* cod, pg_t *pg);
int ricercaCodiceRef(tabPg_t *tabPg, char* cod, pg_t **pg);
void aggiungi(tabPg_t *tabPg);
void liberaEquip(tabEquip_t *eq);
void liberaPg(pg_t pg);
void modificaTabEquip(tabEquip_t *equip, tabInv_t *tabInv);
void aggiornaPgStatEquip(pg_t *pg);
void aggiornaPgEquip(pg_t *pg, tabInv_t *tabInv);
void elimina(tabPg_t *tabPg_t, char* cod);

#endif
