#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"

typedef struct nodoPg_s {
  pg_t pg;
  struct nodoPg_s *next;
} nodoPg_t, *linkPg;

struct pgList_s {
  linkPg head, tail;
  int nPg;
};

static linkPg newNodoPg(pg_t pg, linkPg next);

static linkPg newNodoPg(pg_t pg, linkPg next) {
  linkPg n = calloc(1, sizeof(*n));
  if (n == NULL)
    return NULL;
  n->pg = pg;
  n->next = next;
  return n;
}

pgList_t pgList_init() {
  pgList_t pgList = calloc(1, sizeof(*pgList));
  return pgList;
}

void pgList_insert(pgList_t pgList, pg_t pg) {
  linkPg toAdd;
  toAdd = newNodoPg(pg, NULL);
  if (toAdd == NULL || pgList == NULL)
    return;
  if(pgList->head == NULL)
    pgList->head = pgList->tail = toAdd;
  else {
    pgList->tail->next = toAdd;
    pgList->tail = toAdd;
  }
}

void pgList_read(char *filename, pgList_t pgList) {
  pg_t pg;
  FILE *fp = fopen(filename, "r");
  if (pgList == NULL)
    return;
  if (fp == NULL)
    return;

  while((pg_read(fp, &pg)) != 0) {
    pgList_insert(pgList, pg);
    pgList->nPg++;
  }

  fclose(fp);
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
  linkPg iter = NULL;
  if (pgList == NULL)
    return;
  for(iter=pgList->head; iter!=NULL; iter=iter->next)
    pg_print(fp, &iter->pg, invArray);
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
  linkPg iter = NULL;
  if (pgList == NULL)
    return NULL;
  for(iter = pgList->head; iter != NULL; iter=iter->next) {
    if (strcmp(iter->pg.cod, cod) == 0) {
      return (&iter->pg);
    }
  }
  return NULL;
}

void pgList_add(pgList_t pgList){
  pg_t pg;

  printf("Cod Nome Classe HP MP ATK DEF MAG SPR: ");
  if (pg_read(stdin, &pg) != 0) {
    /* Eventuale invocazione di ricerca per check duplicati */
    pgList_insert(pgList, pg);
  }
}

void pgList_remove(pgList_t pgList_t, char* cod){
  linkPg iter, prev;
  for(iter = pgList_t->head, prev = NULL; iter != NULL; prev = iter, iter=iter->next) {
    if (strcmp(iter->pg.cod, cod) == 0) {
      if (iter == pgList_t->head && iter == pgList_t->tail) {
        pgList_t->head = pgList_t->tail = NULL;
      } else if (iter == pgList_t->head) {
        pgList_t->head = iter->next;
      } else if (iter == pgList_t->tail) {
        pgList_t->tail = prev;
        prev->next = NULL;
      } else {
        prev->next = iter->next;
      }
      pg_clean(&iter->pg);
      free(iter);
      break;
    }
  }
}

void pgList_free(pgList_t pgList) {
  linkPg iter, next;
  for(iter = pgList->head; iter != NULL; iter=next) {
    next = iter->next;
    pg_clean(&iter->pg);
    free(iter);
  }
}
