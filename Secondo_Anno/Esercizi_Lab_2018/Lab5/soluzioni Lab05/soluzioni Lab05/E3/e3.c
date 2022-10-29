#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DBG 1

#define STR      31
#define N_SCELTE 10
#define FILE_IN  "log.txt"

typedef enum chiaveOrdinamento_e {NESSUNO, DATA, CODICE, PARTENZA, ARRIVO} chiaveOrdinamento;

typedef struct {
  int a;
  int m;
  int g;
} data_t;

typedef struct {
  int h;
  int m;
  int s;
} ora_t;

typedef struct {
  /* modifica rispetto all.es. 5 del Lab04*/
  char *codice;
  char *partenza;
  char *destinazione;
  char *data_str;
  char *orap_str;
  char *orad_str;
  /* fine modifica */
  int ritardo;
  data_t data;
  ora_t p, d;
} voce_t;

typedef struct tabella_ {
  int n_voci;
  /* modifica rispetto all.es. 5 del Lab04*/
  voce_t *log;
  voce_t **logC, **logD, **logP, **logA;
  /* fine modifica */
} tabella_t;


enum { falso, vero };

typedef int bool;

tabella_t *leggiTabella();
void liberaTabella(tabella_t *tab);
int comparaData(data_t d1, data_t d2);
void stampa(tabella_t *tab, chiaveOrdinamento k, char* file); /*char* file = NULL per stampare sullo stdout */
void stampaMenu(char *scelte[], int *selezione);
void stampaEntry(voce_t riga, FILE *fp);
void ordinaStabile(voce_t **v, int n_voci, chiaveOrdinamento k);
void ricercaPartenzaDicotomica(tabella_t *tab, char* partenza, int nCharConfronto);
bool ricercaCodiceDicotomica(tabella_t *tab, char* codice, int *indice);

int main(int argc, char** argv) {

  char *scelte[] = {
    "Uscita",
    /* modifica rispetto all.es. 5 del Lab04*/
    "Leggi file",
    /* fine modifica */
    "Stampa a video",
    "Stampa su file",
    "Ordina per data",
    "Ordina per codice",
    "Ordina per stazione di partenza",
    "Ordina per stazione di arrivo",
    "Ricerca per codice",
    "Ricerca per stazione di partenza"
  };

  tabella_t *tab;
  char codiceRicerca[STR], partenzaRicerca[STR];
  int selezione, nCharConfronto;
  bool fineProgramma;
  char nomeFile[STR];
  int indice = -1, trovato = 0;

  tab = leggiTabella(FILE_IN);
#if DBG
  stampa(tab, CODICE, NULL);
#endif
  fineProgramma = falso;

  do {
    stampaMenu(scelte, &selezione);
    switch(selezione) {

    case 0: {
      fineProgramma = vero;
    }
    break;

		case 1: {
      printf("Inserire nome file\n");
      scanf("%s",nomeFile);
			liberaTabella(tab);
			tab = leggiTabella(nomeFile);
		}
		break;

    case 2: {
      stampa(tab, CODICE, NULL);
    }
    break;

    case 3: {
      printf("Inserire nome file\n");
      scanf("%s",nomeFile);
      stampa(tab, CODICE, nomeFile);
    }
    break;

    case 4: {
      printf("Elenco ordinato per data\n");
      stampa(tab, DATA, NULL);
    }
    break;

    case 5: {
      printf("Elenco ordinato per codice\n");
      stampa(tab, CODICE, NULL);
    }
    break;

    case 6: {
      printf("Elenco ordinato per partenza\n");
      stampa(tab, PARTENZA, NULL);
    }
    break;

    case 7: {
      printf("Elenco ordinato per arrivo\n");
      stampa(tab, ARRIVO, NULL);
    }
    break;

    case 8: {
      printf("Inserire codice: ");
      scanf("%s", codiceRicerca);
      indice = -1;
      trovato = 0;
      trovato = ricercaCodiceDicotomica(tab, codiceRicerca, &indice);
      if (trovato) stampaEntry(*(tab->logC[indice]), stdout);
    }
    break;

    case 9: {
      printf("Inserire stazione di partenza: ");
      scanf("%s%n", partenzaRicerca, &nCharConfronto);
      ricercaPartenzaDicotomica(tab, partenzaRicerca, nCharConfronto-1);
    }
    break;

    default: {
      printf("Scelta non valida\n");
    }
    break;
    }
  } while(!fineProgramma);


	liberaTabella(tab);
  return 0;
}

int comparaData(data_t d1, data_t d2) {
  if (d1.a != d2.a)
    return (d1.a-d2.a);
  else if (d1.m != d2.m)
    return (d1.m-d2.m);
  else if (d1.g != d2.g)
    return (d1.g-d2.g);
  else return 0;
}

int comparaOra(ora_t o1, ora_t o2) {
  if (o1.h != o2.h)
    return (o1.h-o2.h);
  else if (o1.m != o2.m)
    return (o1.m-o2.m);
  else if (o1.s != o2.s)
    return (o1.s-o2.s);
  else return 0;
}

void stampaMenu(char *scelte[], int *selezione) {
  int i=0;
  printf("\nMENU'\n");
  for(i=0; i<N_SCELTE; i++) printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}

void liberaTabella(tabella_t *tab) {
	int i;
	if (tab == NULL)
		return;
	if (tab->logA) free(tab->logA);
	if (tab->logC) free(tab->logC);
	if (tab->logD) free(tab->logD);
	if (tab->logP) free(tab->logP);
	if (tab->log) {
		for(i=0;i<tab->n_voci;i++) {
			if (tab->log[i].codice) free(tab->log[i].codice);
			if (tab->log[i].partenza) free(tab->log[i].partenza);
			if (tab->log[i].destinazione) free(tab->log[i].destinazione);
			if (tab->log[i].data_str) free(tab->log[i].data_str);
			if (tab->log[i].orap_str) free(tab->log[i].orap_str);
			if (tab->log[i].orad_str) free(tab->log[i].orad_str);
		}
		free(tab->log);
	}
	free(tab);
}


tabella_t *leggiTabella(char *file) {
  int i;
  /* modifica */
	char tmpCodice[STR], tmpPart[STR], tmpDest[STR], tmpData[STR], tmpOraP[STR], tmpOraD[STR];
  /* fine modifica */
  tabella_t *tab = calloc(1, sizeof(tabella_t));
  FILE *in = fopen(file, "r");
  if (in == NULL)
    exit(-1);

  fscanf(in, "%d", &tab->n_voci);
  /* modifica */
	tab->log = calloc(tab->n_voci, sizeof(voce_t));
	tab->logA = calloc(tab->n_voci, sizeof(voce_t*));
	tab->logC = calloc(tab->n_voci, sizeof(voce_t*));
	tab->logD = calloc(tab->n_voci, sizeof(voce_t*));
	tab->logP = calloc(tab->n_voci, sizeof(voce_t*));
  /* fine modifica */

  for (i=0; i<tab->n_voci; i++) {
    fscanf(in, "%s %s %s %s %s %s %d\n", tmpCodice, tmpPart, tmpDest, tmpData, tmpOraP, tmpOraD, &tab->log[i].ritardo);
  /* modifica */
		tab->log[i].codice = strdup(tmpCodice);
		tab->log[i].partenza = strdup(tmpPart);
		tab->log[i].destinazione = strdup(tmpDest);
		tab->log[i].data_str = strdup(tmpData);
		tab->log[i].orap_str = strdup(tmpOraP);
		tab->log[i].orad_str = strdup(tmpOraD);
  /* fine modifica */
    sscanf (tab->log[i].data_str,"%d/%d/%d", &tab->log[i].data.a,&tab->log[i].data.m,&tab->log[i].data.g);
    sscanf (tab->log[i].orap_str,"%d:%d:%d", &tab->log[i].p.h,&tab->log[i].p.m,&tab->log[i].p.s);
    sscanf (tab->log[i].orad_str,"%d:%d:%d", &tab->log[i].d.h,&tab->log[i].d.m,&tab->log[i].d.s);
  }


  for(i=0;i<tab->n_voci;i++) {
    tab->logA[i] = &tab->log[i];
    tab->logC[i] = &tab->log[i];
    tab->logD[i] = &tab->log[i];
    tab->logP[i] = &tab->log[i];
  }

  ordinaStabile(tab->logA, tab->n_voci, ARRIVO);
  ordinaStabile(tab->logC, tab->n_voci, CODICE);
  ordinaStabile(tab->logD, tab->n_voci, DATA);
  ordinaStabile(tab->logP, tab->n_voci, PARTENZA);

  return tab;
}

void stampa(tabella_t *tab, chiaveOrdinamento k, char* file) {
  FILE *fp;
  int i;
  if(file == NULL)
    fp = stdout;
  else
    fp = fopen(file,"w");

  switch(k) {
    case CODICE:
      for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logC[i]), fp);
      break;
    case DATA:
      for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logD[i]), fp);
      break;
    case ARRIVO:
      for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logA[i]), fp);
      break;
    case PARTENZA:
      for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logP[i]), fp);
      break;
    default:
      for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logC[i]), fp);
  }

  if(file!=NULL)
    fclose(fp);
}

void stampaEntry(voce_t v, FILE *fp) {
  fprintf(fp, "%s %s %s %s %s %s %d\n", v.codice, v.partenza, v.destinazione, v.data_str, v.orap_str, v.orad_str, v.ritardo);
}

int cerca(tabella_t *tab, int start, chiaveOrdinamento k) {
  int j, min = start;
  for(j=start+1; j<tab->n_voci; j++) {
    switch(k) {
    case DATA: {
      int cmp = comparaData(tab->log[min].data, tab->log[j].data);
      if (cmp == 0) if(comparaOra(tab->log[min].p, tab->log[j].p) > 0) min = j;
    }
    break;
    case CODICE: {
      if(strcmp(tab->log[min].codice, tab->log[j].codice) > 0) min = j;
    }
    break;
    case PARTENZA: {
      if(strcmp(tab->log[min].partenza, tab->log[j].partenza) > 0) min = j;
    }
    break;
    default: {
    } break;
    }
  }
  return min;
}

int confrontaVoci(voce_t *v1, voce_t *v2, chiaveOrdinamento k) {
  switch(k) {
    case DATA: {
      int cmp = comparaData(v1->data, v2->data);
      if (cmp == 0) return comparaOra(v1->p, v2->p);
      return cmp;
    }
    break;
    case CODICE: {
      return strcmp(v1->codice, v2->codice);
    }
    break;
    case PARTENZA: {
      return strcmp(v1->partenza, v2->partenza);
    }
    break;
    case ARRIVO: {
      return strcmp(v1->destinazione, v2->destinazione);
    }
    break;
    default: {
    } break;
  }
  return 0;
}

void ordinaStabile(voce_t **v, int n_voci, chiaveOrdinamento k) {
  int i, j;
  int l = 0, r = n_voci-1;
  voce_t *x;

  for(i=l+1; i<=r; i++) {
    x = v[i];
    j = i-1;
    while(j>=l && confrontaVoci(x, v[j], k) < 0) {
      v[j+1] = v[j];
      j--;
    }
    v[j+1] = x;
  }
}

bool ricercaCodiceDicotomica(tabella_t *tab, char* codice, int *indice) {
  int iniziale = 0, finale = tab->n_voci - 1, medio, cmp;

  if(finale < 0)
    return falso;

  while(iniziale <= finale) {
    medio = (iniziale + finale) / 2;
    cmp = strcmp(tab->logC[medio]->codice, codice);
    if(cmp == 0) {
      *indice = medio;
      return vero;
    }
    if(cmp < 0)
      iniziale = medio + 1;
    else
      finale = medio - 1;
  }
  return falso;
}

void ricercaPartenzaDicotomica(tabella_t *tab, char *partenza, int nCharConfronto) {
  int iniziale = 0, finale = tab->n_voci - 1, medio, i, j, cmp;
  bool trovato = falso;

  while(iniziale <= finale && !trovato) {
    medio = (iniziale + finale) / 2;
    cmp = strncmp(tab->logP[medio]->partenza, partenza, nCharConfronto);
    if(cmp == 0) {
      trovato = vero;
    } else {
      if(cmp < 0)
        iniziale = medio + 1;
      else
        finale = medio - 1;
    }
  }

  if(trovato) {
    i = medio;
    j = medio -1;
    while(i < tab->n_voci && strncmp(tab->logP[i]->partenza, partenza, nCharConfronto) == 0) {
      stampaEntry(*(tab->logP[i]), stdout);
      i++;
    }
    while(j>=0 && strncmp(tab->logP[j]->partenza, partenza, nCharConfronto) == 0) {
      stampaEntry(*(tab->logP[j]), stdout);
      j--;
    }
  } else
    printf("Voce non trovata");
}
