#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"
#include "invArray.h"
#include "pg.h"

#define N_SCELTE 7
#define DBG 0

enum { falso, vero };
typedef int bool;

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

  pgList_t pgList = pgList_init();
  invArray_t invArray = invArray_init();
  pg_t *pgp;


  pgList_read("pg.txt", pgList);
#if DBG
  pgList_print(stdout, pgList);
#endif /* DBG */

  invArray_read("inventario.txt", invArray);
#if DBG
  invArray_print(stdout, invArray);
#endif /* DBG */

  fineProgramma = falso;

  do {
    stampaMenu(scelte, &selezione);
    switch(selezione){

    case 0: {
      fineProgramma = vero;
    } break;

    case 1: {
      pgList_print(stdout, pgList, invArray);
    } break;

    case 2: {
      invArray_print(stdout, invArray);
    } break;

    case 3: {
      printf("Inserire codice personaggio: ");
      scanf("%s", codiceRicerca);
      pgp = pgList_searchByCode(pgList, codiceRicerca);
      if (pgp!=NULL) {
        pg_print(stdout, pgp, invArray);
      }
    } break;

    case 4: {
      pgList_add(pgList);
    } break;

    case 5: {
      printf("Inserire codice personaggio: ");
      scanf("%s", codiceRicerca);
      pgList_remove(pgList, codiceRicerca);
    } break;

    case 6: {
      printf("Inserire codice personaggio: ");
      scanf("%s", codiceRicerca);
      pgp = pgList_searchByCode(pgList, codiceRicerca);
      if (pgp!=NULL) {
        pg_updateEquip(pgp, invArray);
      }
    } break;

    default:{
      printf("Scelta non valida\n");
    } break;
    }
  } while(!fineProgramma);

  pgList_free(pgList);

  return 0;
}
