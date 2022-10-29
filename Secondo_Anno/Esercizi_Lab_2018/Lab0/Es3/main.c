#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxN 3000

void ruota(int v[maxN], int N, int P, int dir);
void ruotaVettore1(int V[maxN], int N, int P, int dir);
void ruotaVettore2(int V[maxN], int N, int P, int dir);
void ruotaVettore3(int V[maxN], int N, int P, int dir);
void ruotaVettore4(int V[maxN], int N, int P, int dir);
void swap(int* a,int* b);

int main()
{
     clock_t start, end;
     double cpu_time_used;

    int i,N=maxN,P,dir;
    int v[maxN];
    start = clock();

//    scanf("%d",&N);
//    for(i=0;i<N;i++)
//        scanf("%d",&v[i]);
    for(i=0;i<maxN;i++){
        v[i]=2*i;
    }
//    while(P!=0){
//        scanf("%d",&P);
//        scanf("%d",&dir);
//        P=P%N;
        P=3;
        dir=1;
        ruotaVettore4(v,N,P,dir);
//    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Used: %f s",cpu_time_used);
    return 0;
}

void ruota(int v[maxN], int N, int P, int dir){
    int i,j,k,tmp;

    for(i=0;i<P;i++){
        for(j=N-1;j>=0;j--){
            if(dir==1){
                if(j==N-1)
                    tmp=v[j];
                else if(j==0){
                    v[j+1]=v[j];
                    v[j]=tmp;
                }
                else
                    v[j+1]=v[j];
            }
            else if(dir==-1){
                k=N-1-j;
                if(k==0)
                    tmp=v[k];
                else if(k==N-1){
                    v[k-1]=v[k];
                    v[k]=tmp;
                }
                else
                    v[k-1]=v[k];
            }
        }
    }
    for(i=0;i<N;i++)
        printf("%d ",v[i]);
    printf("\n");
}

void ruotaVettore1(int V[maxN], int N, int P, int dir) {
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
    for(i=0;i<N;i++)
        printf("%d ",V[i]);
    printf("\n");
}

void ruotaVettore2(int V[maxN], int N, int P,int dir) {
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
  for(i=0;i<N;i++)
        printf("%d ",V[i]);
    printf("\n");
}


void ruotaVettore3(int V[maxN], int N, int P, int dir) {
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
      for(i=0;i<N;i++)
        printf("%d ",V[i]);
    printf("\n");
}

void ruotaVettore4(int V[maxN], int N, int P, int dir) {
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
      for(i=0;i<N;i++)
        printf("%d ",V[i]);
    printf("\n");
}
