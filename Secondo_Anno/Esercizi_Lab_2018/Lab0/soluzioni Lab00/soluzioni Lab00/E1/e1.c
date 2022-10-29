#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define MAXN 30


void stampaIntervalloVettore(int v[MAXN], int r, int l) {
  int i;
  for(i=r; i<=l; i++) printf("%d ", v[i]);
  printf("\n");
}

int cerca1(int v[MAXN], int n) {
    //Complessità quadratica. partire da lunghezza massima=n e man mano scendo cercando tutte le sequenze che soddisfano
    //il criterio (tra 2 zeri, non contiene nessuno zero). Le sequenze sono tutte quelle che partono da 0...n-lunghezza sequenza.
    //Se una sequenza soddisfa il criterio è automaticamente quella ottima, per cui non devo più controllare lunghezze minori.
  int lung, j, k;
  int daStampare, trovato;

  trovato = 0;
  for(lung=n; !trovato && lung>0; lung--) { /* per ogni lunghezza decrescente dei sottovettori non minore della massima sinora trovata*/
    for(j=0; j<=n-lung; j++) { /* per ogni possibile indice di inizio di un sottovettore */
      daStampare = 1;
      for(k=j; daStampare && k<j+lung; k++) { /* verifica di validita' del sottovettore */
        if (v[k] == 0) {
          daStampare = 0; /* sottovettore non valido */
        }
      }
      if (daStampare) {
        trovato = 1; /* imposta il flag che non lascera' iterare su una lunghezza minore */
        printf("sottovettore massimo: ");
        stampaIntervalloVettore(v,j,j+lung-1);
        j = k+1; /* saltiamo il sottointervallo appena controllato */
      }
    }
  }
  return 0;
}

int cerca2(int v[MAXN], int n) {
  int maxl=0, i, i0=-1;

  //Complessità lineare
  /*PRIMA trova la lunghezza dei sottovettori di lunghezza massima */
  for(i=0; i<=n; i++) {
    if (i<n && v[i]!=0 && (i==0 || v[i-1]==0)) {    //N.B. V[i-1] non viene acceduta se i==0 perchè il C finisce l'OR se la prima condizione è già verificata
      /* indice di inizio del sottovettore */
      i0 = i;
    }
    else if (i>0 && (i==n || v[i]==0) && v[i-1]!=0) {
      /* il sottovettore e' terminato, ne calcolo la lunghezza e la confronto con il massimo temporaneo, eventualmente aggiornandolo */
      if (i-i0 > maxl) {
        maxl = i-i0;
      }
    }
  }
  /*POI conoscendo la lunghezza massima, stampa i corrispondenti sottovettori (eventualmente più di uno) */
  for(i=0; i<=n; i++) {
    if (i<n && v[i]!=0 && (i==0 || v[i-1]==0)) {
      /* indice di inizio del sottovettore */
      i0 = i;
    }
    else if (i>0 && (i==n || v[i]==0) && v[i-1]!=0) {
      /* il sottovettore e' terminato, se e' di lunghezza massima lo stampo */
      if (i-i0 == maxl) {
        printf("sottovettore massimo: ");
        stampaIntervalloVettore(v,i0,i0+maxl-1);
      }
    }
  }

  return 0;
}

int cerca3(int v[MAXN], int n) {
  int maxl=0, nmax=0, i, i0=-1;
  int massimi_i0[MAXN]; //In realtà MAXN/2 al massimo

  /* identifica i sottovettori di lunghezza massima */
  for(i=0; i<=n; i++) {
    if (i<n && v[i]!=0 && (i==0 || v[i-1]==0)) {
      /* indice di inizio del sottovettore */
      i0 = i;
    }
    else if (i>0 && (i==n || v[i]==0) && v[i-1]!=0) {
      /* il sottovettore e' terminato, ne calcolo la lunghezza e la confronto con il massimo temporaneo,
        eventualmente aggiornando il massimo, il vettore massimi_i0 e il suo indice nmax */
      if (i-i0 > maxl) {
        maxl = i-i0;
        massimi_i0[0] = i0;
        nmax=1;
      }
      else if (i-i0 == maxl) {
        /* il sottovettore trovato e' di lunghezza massima. Accumulo in massimi_i0 il suo indice di partenza */
        massimi_i0[nmax++] = i0;
      }
    }
  }
  /* stampa i sottovettori a massima lunghezza  (eventualmente più di uno)  */
  for(i=0; i<nmax; i++) {
    printf("sottovettore massimo: ");
    stampaIntervalloVettore(v,massimi_i0[i],massimi_i0[i]+maxl-1);
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int vett[MAXN] = {0,0,3,4,5,0,0,1,3,4,0,1,0,9,4,2,0};
  int i, n, selettore = 1;

  if (argc>1) {
    selettore = atoi(argv[1]);
    if (selettore<1 || selettore>3) selettore = 1;
  }

  printf("Inserire numero di elementi (intervallo 1..%d)\n", MAXN);
  printf("(fuori intervallo per accettare valori preimpostati): ");
  scanf("%d", &n);

  if (n>0 && n<=MAXN) {
    for(i=0; i<n; i++) scanf("%d", &vett[i]);
  }
  else {
    n = 17;
  }

  printf("Il vettore e':\n");
  stampaIntervalloVettore(vett,0,n-1);

  switch (selettore) {
  case 1: cerca1(vett, n);
          break;
  case 2: cerca2(vett, n);
          break;
  case 3: cerca3(vett, n);
          break;
  default: printf("errore: selettore errato\n");
  }

  return 0;
}
