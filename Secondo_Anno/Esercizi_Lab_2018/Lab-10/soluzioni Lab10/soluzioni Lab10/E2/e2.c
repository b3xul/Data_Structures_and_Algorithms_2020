/*
Soluzione Greedy proposta con tre criteri diversi di ordinamanto dei dati.
A seconda del gruppo di esercizi (letti da file) la soluzione puo' esistere o no.
L'ottimo NON e' garantito.
Modificando le costanti DMAX e PMAX, si puo' passare da casi di soluzioni valide a
soluzioni non esistenti.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "elementi.txt"

#define NDIAG 3   /* numero di diagonali nel programma */
#define MAXE 5    /* numero massimo di elementi per diagonale */
#define MAXL 100  /* massima lunghazza stringa */
#define DMAX 11   /* difficolta' massima diagomale */
#define PMAX 33   /* difficolta' massima programma */
#define VALMED (((float)DMAX)/MAXE)

typedef struct elemento_s {
  char nome[MAXL];
  int tipo;
  int in, out;
  int finale;
  int prec;
  int diff;
  float val;
  float val_rel;
  int preso;
} elemento_t;

typedef struct diagonale_s {
  int elementi[MAXE];
  int ne;
  int diff;
  float val;
} diagonale_t;

typedef struct diagonali_s {
  diagonale_t vd[NDIAG];
  int diff;
} diagonali_t;

typedef struct elementi_s {
  elemento_t *ve;
  int ne;
} elementi_t;

typedef enum {valore_c, valore_relativo_c, valore_medio_c} criterio_t;

int criterio_scelto;

elementi_t *leggiElementi(void) {
  int i;
  FILE *in = fopen(FILENAME, "r");
  elementi_t *E = malloc(1 * sizeof(*E));
  if (E == NULL) return NULL;
  fscanf(in, "%d", &E->ne);
  E->ve = calloc(E->ne, sizeof(elemento_t));
  if (E->ve == NULL) return NULL;
  for(i=0;i<E->ne;i++) {
    fscanf(in, "%s %d %d %d %d %d %f %d\n",
           E->ve[i].nome, &E->ve[i].tipo, &E->ve[i].in, &E->ve[i].out,
           &E->ve[i].finale, &E->ve[i].prec, &E->ve[i].val, &E->ve[i].diff);
    E->ve[i].val_rel = E->ve[i].val / (float) E->ve[i].diff;
  }
  return E;
}

int elementoMigliore (elemento_t *e1, elemento_t *e2) {
  switch (criterio_scelto) {
  case valore_c: return e1->val > e2->val;
  case valore_relativo_c: return e1->val_rel > e2->val_rel;
  case valore_medio_c: return abs(e1->val-VALMED) < abs(e2->val-VALMED);
  default: return 0;
  }
}

/* cerca l'elemento con valore massimo, tra qualli che rispettano i vincoli */
int nextBest(elementi_t *E, int first, int direzione, int diff, int diff_p, int acrob,
             int cambiadir) {
  int i, iBest=-1;

  for(i=0; i<E->ne; i++) {
    if (!E->ve[i].preso && (E->ve[i].in == direzione) && !(first && E->ve[i].prec) &&
        (diff + E->ve[i].diff <= DMAX) && (diff_p + E->ve[i].diff <= PMAX)) {
      if (acrob==0 || E->ve[i].tipo==acrob || (acrob==3 && E->ve[i].tipo>0)) {
        if (cambiadir && E->ve[i].out != direzione) return i;
        /*       if (iBest<0 || abs(E->ve[i].val-VALMED) < abs(E->ve[iBest].val-VALMED)) */
        if (iBest<0 || elementoMigliore(&(E->ve[i]),&(E->ve[iBest])))
          iBest = i;
      }
    }
  }
  if (iBest>=0)
    E->ve[iBest].preso = 1;

  return iBest;
}

int verificaAcrobatici(diagonale_t *diag, elementi_t *el, int i, int acrob) {
  /* se trovato l'elemento acrobatico (unico) cercato, non cercarlo piu' */
  int curr = diag->elementi[i];
  if ((acrob == 1 || acrob == 2) && el->ve[curr].tipo == acrob)
    return 0;
  /* verifica sequenza */
  else if (acrob == 3 && i>0 && el->ve[curr].tipo != 0) {
    /* elemento acrobatico trovato dalla seconda posizione in poi */
    int prev = diag->elementi[i-1];
    /* se precedente acrobatico : disabilita */
    if (el->ve[prev].tipo != 0)
      return 0;
  }
  return acrob; /* non trovato ritorna acrob come ottenuto in ingresso */
}

/* obiattivo: completare una diagonale (diag) con elementi presi da el
   diff_iniziale; serve per verificare il vincolo sulla difficolta' massima del programma
   acrob: eventuale vincolo/richiesta su elementi acrobatici */
int diagonale(diagonale_t *diag, elementi_t *el, int diff_iniziale, int acrob) {
  int i, next;
  int diff=0;
  int direzione = 1;

  diag->ne=0;
  diag->val=0.0;
  for(i=0; i<el->ne; i++) {
    el->ve[i].preso = 0;
  }
  for (i=0; i<MAXE; i++) {
    /* primo giro (eventualmente cerca un esercizio acrobatico (acrob = 1, 2, o 3) */
    next = nextBest(el, i==0, direzione, diff, diff+diff_iniziale,acrob,0);
    if (acrob && next<0) {
      /* cercato elemento acrobatico e non trovato: ritenta
         cerca non acrobatico e cambia direzione */
      next = nextBest(el, i==0, direzione, diff, diff+diff_iniziale,0,1);
    }
    if (next<0) break; /* uscita non strutturata - nessuna ulteriore scelta possibile */
    direzione = el->ve[next].out;
    diff += el->ve[next].diff;
    diag->elementi[i] = next;
    diag->ne++;
    diag->val += el->ve[next].val;
    acrob = verificaAcrobatici(diag,el,i,acrob);
  }
  diag->diff = diff;
  /* almeno un elemento e richiesta elementi acrobatici soddisfatta */
  return (diag->ne>0 && acrob==0);
}

int checkBonus(diagonali_t *prog, elementi_t *E) {
  int i, j, bonus = -1;
  /* una qualunque diagonale puo' avere il bonus. Eventualmente andranno permutate per
     avere il bonus nell'ultima diagonale */

  for (i=0; i<NDIAG; i++) {
    j=prog->vd[i].ne-1;
    if (E->ve[j].tipo > 0 && E->ve[prog->vd[i].elementi[j]].diff > 7) {
      if (bonus == -1 || (prog->vd[bonus].val < prog->vd[i].val))
        bonus = i;
    }
  }
  return bonus;
}

void greedy(elementi_t *E) {
  int i, j, bonus = -1;
  float val = 0.0;
  int diff_tot = 0;
  diagonali_t prog; /* struct contenente un vettore di 3 diagonali */
  int acrob=0;
  int valido=1;

  /* Costruzione del programma una diagonale alla volta */
  /* richieste:
     prima diagonale: elemento acrobatico avanti (1)
     seconda diagonale: elemento acrobatico indietro (2)
     terza diagonale: due elementi acrobatici in sequenza (3)\
   */
  for(i=0; valido && i<NDIAG; i++) {
    /* DIAGONALE i */
    acrob++; /* acrob = 3 per sequenza */
    valido &= diagonale(&prog.vd[i],E,diff_tot,acrob);
    if (valido) {
      diff_tot += prog.vd[i].diff;
      val += prog.vd[i].val;
    }
  }

  if (valido) {
    bonus = checkBonus(&prog,E);
    if (bonus>=0) {
      val += 0.5 * prog.vd[bonus].val;
    }
    printf("TOT = %f\n", val);
    for(i=0;i<NDIAG;i++) {
      printf("DIAG %d > %.3f %s\n", i, prog.vd[i].val, ((bonus == i) ? "BONUS" : ""));
      for(j=0;j<prog.vd[i].ne;j++) printf("%s ", E->ve[prog.vd[i].elementi[j]].nome);
      printf("\n");
    }
  } else {
    printf("Programma non valido\n");
  }
}


int main(void) {
  elementi_t *E = leggiElementi();

  printf("\nSoluzione Greedy basata su valore\n");
  criterio_scelto = valore_c;
  greedy(E);

  printf("\nSoluzione Greedy basata su valore relativo\n");
  criterio_scelto = valore_relativo_c;
  greedy(E);

  printf("\nSoluzione Greedy basata su valore medio\n");
  criterio_scelto = valore_medio_c;
  greedy(E);

  return 0;
}
