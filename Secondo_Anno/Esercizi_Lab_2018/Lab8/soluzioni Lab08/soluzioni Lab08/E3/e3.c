#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"
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
                if(ricercaCodiceRef(tabPg, codiceRicerca, &ppg) != 0)
                  aggiornaPgEquip(ppg, tabInv);
			} break;

			default:{
				printf("Scelta non valida\n");
			} break;
		}
	} while(!fineProgramma);

  return 0;
}
