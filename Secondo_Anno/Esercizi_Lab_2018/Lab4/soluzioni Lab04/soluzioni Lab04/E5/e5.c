#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 26
#define DBG 1

#define MAXR     1000
#define STR      31
#define N_SCELTE 9
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
  char codice[STR];
  char partenza[STR];
  char destinazione[STR];
  char data_str[STR];
  char orap_str[STR];
  char orad_str[STR];
  int ritardo;
  data_t data;
  ora_t p, d;
} voce_t;

typedef struct tabella_ {
  int n_voci;
  voce_t log[MAXR];
  voce_t *logC[MAXR], *logD[MAXR], *logP[MAXR], *logA[MAXR];
} tabella_t;

typedef int bool;

tabella_t leggiTabella();
int comparaData(data_t d1, data_t d2);
void stampa(tabella_t tab, chiaveOrdinamento k, char* file); /*char* file = NULL per stampare sullo stdout */
void stampaMenu(char *scelte[], int *selezione);
void stampaEntry(voce_t riga, FILE *fp);
void ordinaStabile(voce_t **v, int n_voci, chiaveOrdinamento k);
void ricercaPartenzaDicotomica(tabella_t tab, char* partenza, int nCharConfronto);
bool ricercaCodiceDicotomica(tabella_t tab, char* codice, int *indice);

int main(int argc, char** argv) {

  char *scelte[] = {
    "Uscita",
    "Stampa a video",
    "Stampa su file",
    "Ordina per data",
    "Ordina per codice",
    "Ordina per stazione di partenza",
    "Ordina per stazione di arrivo",
    "Ricerca per codice",
    "Ricerca per stazione di partenza"
  };

  tabella_t tab;
  char codiceRicerca[LEN], partenzaRicerca[LEN];
  int selezione, nCharConfronto;
  bool fineProgramma;
  char nomeFile[25];
  int indice = -1, trovato = 0;

  tab = leggiTabella();
#if DBG
  stampa(tab, CODICE, NULL);
#endif
  fineProgramma = 0;

  do {
    stampaMenu(scelte, &selezione);
    switch(selezione) {

    case 0: {
      fineProgramma = 1;
    }
    break;

    case 1: {
      stampa(tab, CODICE, NULL);
    }
    break;

    case 2: {
      printf("Inserire nome file\n");
      scanf("%s",nomeFile);
      stampa(tab, CODICE, nomeFile);
    }
    break;

    case 3: {
      printf("Elenco ordinato per data\n");
      stampa(tab, DATA, NULL);
    }
    break;

    case 4: {
      printf("Elenco ordinato per codice\n");
      stampa(tab, CODICE, NULL);
    }
    break;

    case 5: {
      printf("Elenco ordinato per partenza\n");
      stampa(tab, PARTENZA, NULL);
    }
    break;

    case 6: {
      printf("Elenco ordinato per arrivo\n");
      stampa(tab, ARRIVO, NULL);
    }
    break;

    case 7: {
      printf("Inserire codice: ");
      scanf("%s", codiceRicerca);
      indice = -1;
      trovato = 0;
      trovato = ricercaCodiceDicotomica(tab, codiceRicerca, &indice);
      if (trovato) stampaEntry(*(tab.logC[indice]), stdout);
    }
    break;

    case 8: {
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


tabella_t leggiTabella() {
  int i;
  tabella_t tab;
  FILE *in = fopen(FILE_IN, "r");
  if (in == NULL)
    exit(-1);

  fscanf(in, "%d", &tab.n_voci);
  for (i=0; i<tab.n_voci; i++) {
    fscanf(in, "%s %s %s %s %s %s %d\n", tab.log[i].codice, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].data_str, tab.log[i].orap_str, tab.log[i].orad_str, &tab.log[i].ritardo);
    sscanf (tab.log[i].data_str,"%d/%d/%d", &tab.log[i].data.a,&tab.log[i].data.m,&tab.log[i].data.g);
    sscanf (tab.log[i].orap_str,"%d:%d:%d", &tab.log[i].p.h,&tab.log[i].p.m,&tab.log[i].p.s);
    sscanf (tab.log[i].orad_str,"%d:%d:%d", &tab.log[i].d.h,&tab.log[i].d.m,&tab.log[i].d.s);
  }


  for(i=0;i<tab.n_voci;i++) {
    tab.logA[i] = &tab.log[i];
    tab.logC[i] = &tab.log[i];
    tab.logD[i] = &tab.log[i];
    tab.logP[i] = &tab.log[i];
  }

  ordinaStabile(tab.logA, tab.n_voci, ARRIVO);
  ordinaStabile(tab.logC, tab.n_voci, CODICE);
  ordinaStabile(tab.logD, tab.n_voci, DATA);
  ordinaStabile(tab.logP, tab.n_voci, PARTENZA);

  return tab;
}

void stampa(tabella_t tab, chiaveOrdinamento k, char* file) {
  FILE *fp;
  int i;
  if(file == NULL)
    fp = stdout;
  else
    fp = fopen(file,"w");

  switch(k) {
    case CODICE:
      for(i=0; i<tab.n_voci; i++) stampaEntry(*(tab.logC[i]), fp);
      break;
    case DATA:
      for(i=0; i<tab.n_voci; i++) stampaEntry(*(tab.logD[i]), fp);
      break;
    case ARRIVO:
      for(i=0; i<tab.n_voci; i++) stampaEntry(*(tab.logA[i]), fp);
      break;
    case PARTENZA:
      for(i=0; i<tab.n_voci; i++) stampaEntry(*(tab.logP[i]), fp);
      break;
    default:
      for(i=0; i<tab.n_voci; i++) stampaEntry(*(tab.logC[i]), fp);
  }

  if(file!=NULL)
    fclose(fp);
}

void stampaEntry(voce_t v, FILE *fp) {
  fprintf(fp, "%s %s %s %s %s %s %d\n", v.codice, v.partenza, v.destinazione, v.data_str, v.orap_str, v.orad_str, v.ritardo);
}

int cerca(tabella_t tab, int start, chiaveOrdinamento k) {
  int j, min = start;
  for(j=start+1; j<tab.n_voci; j++) {
    switch(k) {
    case DATA: {
      int cmp = comparaData(tab.log[min].data, tab.log[j].data);
      if (cmp == 0) if(comparaOra(tab.log[min].p, tab.log[j].p) > 0) min = j;
    }
    break;
    case CODICE: {
      if(strcmp(tab.log[min].codice, tab.log[j].codice) > 0) min = j;
    }
    break;
    case PARTENZA: {
      if(strcmp(tab.log[min].partenza, tab.log[j].partenza) > 0) min = j;
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

bool ricercaCodiceDicotomica(tabella_t tab, char* codice, int *indice) {
  int iniziale = 0, finale = tab.n_voci - 1, medio, cmp;

  if(finale < 0)
    return 0;

  while(iniziale <= finale) {
    medio = (iniziale + finale) / 2;
    cmp = strcmp(tab.logC[medio]->codice, codice);
    if(cmp == 0) {
      *indice = medio;
      return 1;
    }
    if(cmp < 0)
      iniziale = medio + 1;
    else
      finale = medio - 1;
  }
  return 0;
}

void ricercaPartenzaDicotomica(tabella_t tab, char *partenza, int nCharConfronto) {
  int iniziale = 0, finale = tab.n_voci - 1, medio, i, j, cmp;
  bool trovato = 0;

  while(iniziale <= finale && !trovato) {
    medio = (iniziale + finale) / 2;
    cmp = strncmp(tab.logP[medio]->partenza, partenza, nCharConfronto);
    if(cmp == 0) {
      trovato = 1;
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
    while(i < tab.n_voci && strncmp(tab.logP[i]->partenza, partenza, nCharConfronto) == 0) {
      stampaEntry(*(tab.logP[i]), stdout);
      i++;
    }
    while(j>=0 && strncmp(tab.logP[j]->partenza, partenza, nCharConfronto) == 0) {
      stampaEntry(*(tab.logP[j]), stdout);
      j--;
    }
  } else
    printf("Voce non trovata");
}
