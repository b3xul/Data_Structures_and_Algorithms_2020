#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define maxN 30
#define maxS 100


void ruotaVettore1(int V[maxN], int dir, int N, int P) {
  int tmp, i, j;

  if (P < 0)
    return;

  if (dir == 1) { /* direzione  SX */
    for (i=0; i<P; i++) {
      tmp = V[0];
      for (j=0; j<N-1; j++)
        V[j] = V[(j+1)];
      V[N-1] = tmp;
    }
  } else {  /* direzione  DX */
      for(i=0; i<P; i++) {
        tmp = V[N-1];
      for(j=N-1; j>0; j--)
        V[j] = V[j-1];
      V[0] = tmp;
    }
  }
}

void ruotaVettore2(int V[maxN], int dir, int N, int P) {
  int tmpVet[maxN], i;

  if (dir == 1) { /* direzione  SX */
    /* salva le P celle iniziali di V in tmpVet */
    for (i=0; i<P; i++) {
      tmpVet[i] = V[i];
    }
    /* sposta V a partire dalla posizione P di P posizioni a sinistra */
    for (i=0; i<N-P; i++) {
      V[i] = V[i+P];
    }
      /* ricopia dati salvati in tmpVet nelle restanti posizioni di V */
    for (i=0; i<P; i++) {
      V[N-P+i] = tmpVet[i];
    }
  } else {  /* direzione  DX */
    /* duale: salva le P celle finali di V in tmpVet */
    for (i=0; i<P; i++) {
      tmpVet[i] = V[N-P+i];
    }
    /* sposta V a partire dalla posizione N-P-1 di P posizioni a destra */
    for (i=N-1; i>=P; i--) {
      V[i] = V[i-P];
    }
      /* ricopia dati salvati in tmpVet nelle restanti posizioni di V */
    for (i=0; i<P; i++) {
      V[i] = tmpVet[i];
    }
  }
}

void ruotaVettore3(int V[maxN], int dir, int N, int P) {
  int tmpVet[maxN], i, t0, t1, dest, src;

  if (dir == 1) { /* direzione  SX */
    t0 = 0; t1 = N-P; /* l'intervallo di V da salvare inizia in t0 e sara' salvato a partire da t1 */
    dest = 0; /* quando sposti inizia da qui */
  }
  else {
    t0 = N-P; t1 = 0; /* l'intervallo da salvare inizia in t0 e sara' salvato a partire da t1 */
    dest = N-1; /* quando sposti inizia da qui */
  }
  /* salva intervallo su vettore temporaneo */
  for (i=0; i<P; i++) {
    tmpVet[i] = V[t0+i];
  }
  /* sposta */

  for (i=0; i<N-P; i++) {
    src = dest+P*dir;
    V[dest] = V[src];
    dest = dest + dir;
  }

  /* ricopia a partire da t1 l'intervallo salvato nel vettore temporaneo */
  for (i=0; i<P; i++) {
    V[t1+i] = tmpVet[i];
  }
}

void ruotaVettore4(int V[maxN], int dir, int N, int P) {
  int tmpVet[maxN], i;

  if (dir == -1) {
    /* scambia direzione: P spostamenti a DX sono equivalenti a N-P a SX */
    P = N-P;
  }
  /* salvo i primi P elementi di V nel vettore temporaneo */
  for (i=0; i<P; i++) {
    tmpVet[i] = V[i];
  }
  /* sposta di P posizioni a sinistra */
  for (i=0; i<N-P; i++) {
    V[i] = V[i+P];
  }
  /* ricopia a partire da N-P+i  l'intervallo salvato nel vettore temporaneo */
  for (i=0; i<P; i++) {
    V[N-P+i] = tmpVet[i];
  }
}

void stampaVettore(int V[maxN], int N) {
  int i;
  for(i=0;i<N;i++) printf("%d ", V[i]);
  printf("\n");
}

int main(int argc, char *argv[]) {
  int N, i, P, dir, fine=0, vett[maxN] = {0,1,2,3,4,5,6,7,8,9};
  int selettore = 1;

  if (argc>1) {
    selettore = atoi(argv[1]);
    if (selettore<1 || selettore>4)
      selettore = 1;
  }

  printf("Inserire numero di elementi (intervallo 1..%d)\n", maxN);
  printf("(fuori intervallo per accettare valori preimpostati): ");
  scanf("%d", &N);
  if (N > 0 && N <= maxN) {
    for(i=0; i<N; i++)
      scanf("%d", &vett[i]);
  }
  else {
    N = 10;
  }

  stampaVettore(vett, N);
  do {
    printf("Comando (P dir) (0 dir per terminare)> ");
    fine = scanf(" %d %d", &P, &dir) != 2;
    if (P<=0)
      fine = 1;
    P = P%N; /* se P>N il numero di rotazioni e' comunque P%N */
    if (!fine && (dir == 1 || dir == -1)) {
      switch (selettore) {
      case 1: ruotaVettore1(vett, dir, N, P);
              break;
      case 2: ruotaVettore2(vett, dir, N, P);
              break;
      case 3: ruotaVettore3(vett, dir, N, P);
              break;
      case 4: ruotaVettore4(vett, dir, N, P);
              break;
      default: printf("errore: selettore errato\n");
      }
      stampaVettore(vett, N);
    }
  } while (!fine);

  return 0;
}
