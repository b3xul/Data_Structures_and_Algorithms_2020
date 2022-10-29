#include<stdlib.h>
#include<string.h>
#include<stdio.h>


typedef struct arco_ {
	int u;
	int v;
} arco;

int powerset_comb_sempl(int start, int pos, int *sol, int k, arco *a, int N, int E, int count);

arco *leggiFile(char *nomeFile, int *N, int *E) {
  int i;
  arco *a;
  FILE *in = fopen(nomeFile, "r");
  if (in == NULL)
    exit(-1);

  fscanf(in, "%d %d", N, E);
  a = (arco *)calloc(*E, sizeof(arco));
  if (a == NULL)
    exit(-1);

  for (i=0; i<*E; i++)
    fscanf(in, "%d %d", &a[i].u, &a[i].v);
  return a;
}

int check(int *sol, int k, arco *a, int E) {
  int i, j, arcocnt = 0;
  int *arcocheck = calloc(E, sizeof(int));

  /*Per ogni vertice della soluzione, confrontalo con tutti gli archi, e verifica che almeno uno dei 2 vertici dell'arco appartenga alla soluzione*/
  for (i=0; i<k; i++) {
    for (j=0; j<E; j++) {
      if (a[j].u == sol[i] || a[j].v == sol[i]) {
        if (arcocheck[j] == 0)
          arcocnt++;
        arcocheck[j] = 1;
      }
    }
  }
  free(arcocheck);
  return (arcocnt == E);    //Tutti gli archi sono rappresentati nella soluzione
}

int main() {
  int N, E, *sol, k, cnt, tot=0;
  arco *a = leggiFile("grafo.txt", &N, &E);

  sol = calloc(N,sizeof(int));

  printf("Vertex cover\n");
  for(k = 1; k <= N; k++) {
    printf("di dimensione %d\n", k);
    cnt = powerset_comb_sempl(0, 0, sol, k, a, N, E, 0);
    if (cnt==0)
      printf("nessuna soluzione \n");
    tot +=cnt;
  }
  printf ("numero di soluzioni: %d \n", tot);

  free(sol);
  free(a);

  return 0;
}

int powerset_comb_sempl(int start, int pos, int *sol, int k, arco *a, int N, int E, int count) {
  int i;
  if (pos >= k) {
    if (check(sol, k, a, E)) {
      for(i=0;i<k;i++)
        printf("%d ", sol[i]);
      printf("\n");
      return count+1;
    }
    return count;
  }
  for (i=start; i<N; i++) {
    sol[pos] = i;
    count = powerset_comb_sempl(i+1, pos+1, sol, k, a, N, E, count);
  }
  return count;
}

