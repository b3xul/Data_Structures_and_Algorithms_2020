/*
   Versione con Item tipo composto contenente riferimenti a strinche dinamiche (di proprietà).
   L'item e' una struct contenente puntatori a stringhe allocate.
   Viene allocato dinamicamente e vi si accede unicamente tramite puntatore.
   ATTENZIONE: vi sono trasferimenti di ownership!
   La funzione leggiItem alloca un Item e ne trasferisce il possesso al programma chiamante.
   La funzione insertOrdinato trasferisce alla lista la proprieta' dell'item ricevuto.
   Le funzioni di eliminazione ritornano l'item al programma chiamante, cui ne viene
   trasferita la proprieta' (e la responsabilita' di deallocazione.
   Si evita il problema della gestione di Item vuoto (tramite ItemSetVoid e ItemCheckVoid),
   trasferemdo il problema a puntatori NULL.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN1 50
#define LEN2 15
#define N_SCELTE 8
#define DBG 1

typedef struct data_s {
  int gg, mm, aaaa;
} data_t ;

typedef struct indirizzo_s {
  char *citta, *via;
  int cap;
} indirizzo_t;

typedef struct {
  char *codice;
  char *nome, *cognome;
  char *ddn_str;
  data_t data;
  indirizzo_t indirizzo;
} Item;

typedef struct nodo_s *link;

typedef struct nodo_s {
  Item *val;
  link next;
} nodo_t;

enum { falso, vero };
typedef int bool;

Item *ItemNew(char *codice, char *nome, char *cognome,
              char *citta, char *via, data_t data, int cap);
void ItemFree(Item *itp);
Item *leggiItem(FILE *fp);
void stampaItem(Item *itp, FILE *fp);
int comparaData(data_t d1, data_t d2);
int stampaMenu(char *scelte[]);
void stampaAnagrafica(link head, char *file); /* char* file = NULL per stampare sullo stdout */
link caricaAnagrafica(link head, char *file);
void freeAnagrafica(link head);
data_t scomponiData(char strData[]);
link aggiungi(link head);
link insertOrdinato(link h, Item *val);
Item *ricercaCodice(link head, char *codice);
Item *elimina(link *head, char* codice);
Item *eliminaTraDate(link *head, data_t d1, data_t d2);

int main(int argc, char **argv) {

  char *scelte[] = {
    "Uscita",
    "Carica da file",
    "Aggiungi persona (tastiera)",
	"Stampa a video",
	"Stampa su file",
    "Ricerca per codice",
    "Elimina dato codice",
    "Elimina tra date"
	};

  char codiceRicerca[LEN1], nomeFile[25], d_str1[LEN1], d_str2[LEN1];
  data_t d1, d2;
  link head = NULL;
  bool fineProgramma = falso;
  int selezione;
  Item *itp;

  do {
    selezione = stampaMenu(scelte);
    switch(selezione){

    case 0: {
      fineProgramma = vero;
    } break;

    case 1: {
      printf("Inserire nome file\n");
      scanf("%s",nomeFile);
      head = caricaAnagrafica(head, nomeFile);
    } break;

    case 2: {
      head = aggiungi(head);
    } break;

    case 3: {
      stampaAnagrafica(head, NULL);
    } break;

    case 4: {
      printf("Inserire nome file\n");
      scanf("%s",nomeFile);
      stampaAnagrafica(head, nomeFile);
    } break;

    case 5: {
      printf("Inserire codice: ");
      scanf("%s", codiceRicerca);
      itp = ricercaCodice(head, codiceRicerca);
      if (itp != NULL) {
        stampaItem(itp, stdout);
      } else {
        fprintf(stdout, "Codice non trovato\n");
      }
    } break;

    case 6: {
      printf("Inserire codice: ");
      scanf("%s", codiceRicerca);
      itp = elimina(&head, codiceRicerca);
      if (itp != NULL) {
        stampaItem(itp, stdout);
	    ItemFree(itp);
      } else {
        fprintf(stdout, "Codice non trovato\n");
      }
    } break;

    case 7: {
      printf("Inserire data 1: ");
      scanf("%s", d_str1);
      printf("Inserire data 2: ");
      scanf("%s", d_str2);
      d1 = scomponiData(d_str1);
      d2 = scomponiData(d_str2);
      if (comparaData(d1, d2) > 0) {
        data_t tmp;
        tmp = d1;
        d1 = d2;
        d2 = tmp;
      }
      do {
        itp = eliminaTraDate(&head, d1, d2);
        if (itp!=NULL) {
          stampaItem(itp, stdout);
          ItemFree(itp);
        } else {
          printf("Fine operazione di cancellazione\n");
          break;
        }
      } while(vero);
    } break;

    default:{
      printf("Scelta non valida\n");
    } break;
    }
  } while(!fineProgramma);

  freeAnagrafica(head);
  head = NULL;
  return 0;
}

int stampaMenu(char *scelte[]){
  int i=0, selezione;
  printf("\nMENU'\n");
	for(i=0;i<N_SCELTE;i++) printf("%2d > %s\n",i,scelte[i]);
  scanf("%d",&selezione);
  return selezione;
}

int comparaData(data_t d1, data_t d2) {
  if (d1.aaaa != d2.aaaa)
    return (d1.aaaa-d2.aaaa);
  else if (d1.mm != d2.mm)
    return (d1.mm-d2.mm);
  else if (d1.gg != d2.gg)
    return (d1.gg-d2.gg);
  else return 0;
}

Item *ItemNew(char *codice, char *nome, char *cognome,
              char *citta, char *via, data_t data, int cap) {
  Item *itp;

  itp = malloc(sizeof(Item));
  if (itp==NULL) return NULL;

  itp->codice = strdup(codice);
  itp->cognome = strdup(cognome);
  itp->nome = strdup(nome);
  itp->data = data;
  itp->indirizzo.citta = strdup(citta);
  itp->indirizzo.via = strdup(via);
  itp->indirizzo.cap = cap;

  return itp;
}

void ItemFree(Item *itp) {
  if (itp == NULL) return;

  if (itp->codice!=NULL) free(itp->codice);
  if (itp->cognome!=NULL) free(itp->cognome);
  if (itp->nome!=NULL) free(itp->nome);
  if (itp->indirizzo.via!=NULL) free(itp->indirizzo.via);
  if (itp->indirizzo.citta!=NULL) free(itp->indirizzo.citta);
  free (itp);
}

Item *leggiItem(FILE *fp) {
  char codiceTmp[LEN1], nomeTmp[LEN1], cognomeTmp[LEN1], cittaTmp[LEN1], viaTmp[LEN1], dataTmp[LEN1];
  int cap;
  Item *itp=NULL;

  if (fscanf(fp, "%s %s %s %s %s %s %d", codiceTmp, nomeTmp, cognomeTmp, dataTmp, viaTmp, cittaTmp, &cap) == 7) {
    itp = ItemNew(codiceTmp, nomeTmp, cognomeTmp, cittaTmp, viaTmp,
                  scomponiData(dataTmp), cap);
  }
  return itp;
}

link newNode(Item *val, link next) {
  link x = malloc(sizeof(*x));
  if (x == NULL)
    return NULL;
  x->val = val;
  x->next = next;
  return x;
}

link insertOrdinato(link h, Item *val) {
  link p = NULL, x = NULL;

  if(h == NULL || comparaData(h->val->data,val->data) > 0)
    return newNode(val, h);
  for (x=h->next, p=h; x!=NULL && comparaData(val->data, x->val->data) > 0; p=x, x=x->next);
  p->next = newNode(val, x);
  return h;
}

link aggiungi(link head){
  Item *itp;
  printf("Cod Nome Cogn Data[gg/mm/aaaa] Via Citta Cap: ");
  itp = leggiItem(stdin);
  if (itp!=NULL)
    head = insertOrdinato(head, itp);
  return head;
}

link caricaAnagrafica(link head, char *file) {
  FILE *fp;
  Item *itp;
  int n;

  fp = fopen(file, "r");

  if(fp == NULL) {
    printf("Errore nell'apertura del file\n ");
    exit(-1);
  }

  fscanf(fp, "%d", &n);

  while ((itp = leggiItem(fp))!=NULL) {
    head = insertOrdinato(head, itp);
  }
  fclose(fp);
  return head;
}

data_t scomponiData(char strData[]) {
  data_t data;
  sscanf(strData, "%d/%d/%d", &data.gg, &data.mm, &data.aaaa);
  return data;
}

void stampaIndirizzo(indirizzo_t ind, FILE *fp) {
  fprintf(fp, "\t%s %s %05d\n", ind.via, ind.citta, ind.cap);
}

void stampaItem(Item *itp, FILE *fp) {
  fprintf(fp, "%s, %s %s, %d/%d/%d\n",
	  itp->codice, itp->cognome, itp->nome,
          itp->data.gg, itp->data.mm, itp->data.aaaa);
  stampaIndirizzo(itp->indirizzo, fp);
}

void stampaAnagrafica(link head, char* file) {
  link x = NULL;
  FILE *fp;
  if(file == NULL)
      fp = stdout;
  else
      fp = fopen(file,"w");

  for(x = head; x != NULL; x=x->next) {
    stampaItem(x->val, fp);
  }

  if(file!=NULL)
    fclose(fp);
}

Item *ricercaCodice(link head, char *codice) {
  link x;
  for(x = head; x != NULL; x=x->next) {
    if (strcmp(x->val->codice, codice) == 0) {
      return x->val;
    }
  }
  return NULL;
}

Item *elimina(link *head, char *codice){
  link x, p;
  Item *itp = NULL;
  for(x = *head, p = NULL; x != NULL; p = x, x=x->next) {
    if (strcmp(x->val->codice, codice) == 0) {
      if (p == NULL) {
        *head = x->next;
      } else {
        p->next = x->next;
      }
      itp = x->val;
      free(x);
      break;
    }
  }
  return itp;
}

Item *eliminaTraDate(link *head, data_t d1, data_t d2) {
  link x, p;
  Item *itp = NULL;
  for(x = *head, p = NULL; x != NULL && comparaData(d2, x->val->data) >= 0;
      p = x, x=x->next) {
    if (comparaData(d1, x->val->data) <= 0) {
      if (p == NULL) {
        *head = x->next;
      } else {
        p->next = x->next;
      }
      itp = x->val;
      free(x);
      break;
    }
  }
  return itp;
}

void freeAnagrafica(link head) {
  link x, t;

  for(x = head; x != NULL; x=t) {
    t = x->next;
    ItemFree(x->val);
    free(x);
  }
}
