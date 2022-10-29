#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define DBG 0

typedef struct att_ {
  int s, f;
} att;

int min(int A, int B);
int max(int a, int b);
att *attLeggi(FILE *in, int *n);
int attDurata(att a);
int attInterseca(int n, att *v, int *sol, int pos);
void attSelPowersetR(int pos, int n, att *v, int *sol, int *bestsol, int currLen, int *bestLen);
void attSelPowerset(int n, att *v);
int incompatible(int n, att *v, int i, int j);
int attSelRDivideEtImpera(int pos, att *v, int *q);
void attSelDivideEtImpera(int n, att *v);
void displaySol(int n, att *v, int *opt, int *q);
void attSelDP(int n, att *v);
void Merge(att *A, att *B, int l, int q, int r);
void MergeSortR(att *A, att *B, int l, int r);
void MergeSort(att *A, int N);

int main(int argc, char **argv) {
  int i, n;
  FILE *in;
  att *v;

  in = fopen("att1.txt", "r");
  if (in == NULL)
    exit(-1);

  v = attLeggi(in, &n);
  printf("attivita' originali\n");
  for (i=1; i<=n; i++)
    printf("(%d %d) ", v[i].s, v[i].f);
  printf("\n\n");

  MergeSort(v, n);

  printf("attivita' ordinate per tempo di fine crescente\n");
  for (i=1; i<=n; i++)
    printf("(%d %d) ", v[i].s, v[i].f);
  printf("\n\n");

  printf("soluzione ricorsiva con powerset\n");
  attSelPowerset(n,v);


  printf("\nsoluzione ricorsiva divide et impera\n");
  attSelDivideEtImpera(n,v);

  printf("\nsoluzione con programmazione dinamica \n");
  attSelDP(n,v);

  fclose(in);
  return 0;
}

int attDurata(att a) {
  return a.f - a.s;
}

att *attLeggi(FILE *in, int *n) {
  int i;
  att *v;

  fscanf(in, "%d\n", n);
  v = calloc((*n+1), sizeof(att));

  for (i=1; i<=*n; i++)
    fscanf(in, "%d %d\n", &v[i].s, &v[i].f);
  return v;
}

int attInterseca(int n, att *v, int *sol, int pos) {
  int i;
  for (i=0; i<pos; i++) {
    if (sol[i] != 0) {
      if (v[i].s < v[pos].f && v[pos].s < v[i].f)
        return 1;
    }
  }
  return 0;
}

void attSelPowersetR(int pos, int n, att *v, int *sol, int *bestsol, int currLen, int *bestLen) {
  int i;
  if (pos > n) {
    if (*bestLen < currLen) {
      *bestLen = currLen;
      for (i=1; i<=n; i++)
        bestsol[i] = sol[i];
    }
    return;
  }

  sol[pos] = 0;
  attSelPowersetR(pos+1, n, v, sol, bestsol, currLen, bestLen);
  if (!attInterseca(n, v, sol, pos)) {
    sol[pos] = 1;
    attSelPowersetR(pos+1, n, v, sol, bestsol, currLen+attDurata(v[pos]), bestLen);
  }
}

void attSelPowerset(int n, att *v) {
  int *sol = calloc((n+1), sizeof(int));
  int *bestsol = calloc((n+1), sizeof(int));
  int len = 0, i;

  attSelPowersetR(1, n, v, sol, bestsol, 0, &len);

  for(i=1; i<=n; i++)
    if (bestsol[i])
      printf("(%d %d) ", v[i].s, v[i].f);
  printf("\nlunghezza massima %d \n", len);

  free(sol);
  free(bestsol);

  return;
}

int incompatible(int n, att *v, int i, int j) {
  if (v[i].s < v[j].f && v[j].s < v[i].f)
    return 1;
  return 0;
}

int attSelRDivideEtImpera(int pos, att *v, int *q) {
  if (pos == 0)
    return 0;
  return max(attSelRDivideEtImpera(q[pos], v, q)+attDurata(v[pos]), attSelRDivideEtImpera(pos-1, v, q));
}

void attSelDivideEtImpera(int n, att *v) {
  int i, j, ris=0, *q;

  q = calloc((n+1),sizeof(int));

  for (i=2; i<=n; i++)
    for (j=1; j<i; j++) {
      if (incompatible(n, v, i, j)==0)
        q[i] = j;
  }

#if DBG
  for (i=1; i<=n; i++)
    printf("%d ", q[i]);
  printf("\n");
#endif

  ris = attSelRDivideEtImpera(n, v, q);
  printf("lunghezza massima %d\n", ris);
}

void attSelDP(int n, att *v) {
  int i, j, *q, *opt;

  opt = calloc((n+1),sizeof(int));
  q = calloc((n+1),sizeof(int));

  for (i=2; i<=n; i++)
    for (j=1; j<i; j++) {
      if (incompatible(n, v, i, j)==0)
        q[i] = j;
  }

#if DBG
  for (i=1; i<=n; i++)
    printf("%d ", q[i]);
  printf("\n");
#endif

  opt[0] = 0;
  for (i=1; i<=n; i++) {
    opt[i] = max(attDurata(v[i])+opt[q[i]], opt[i-1]);

  }

#if DBG
  for (i=1; i<=n; i++)
    printf("%d ", opt[i]);
  printf("\n");
#endif

  displaySol(n, v, opt, q);

  printf("\nlunghezza massima %d\n", opt[n]);
  return;
}

int min(int A, int B) {
  if (A < B)
      return A;
  return B;
}

int max(int A, int B) {
  if (A>B)
    return A;
  return B;
}

void Merge(att *A, att *B, int l, int q, int r) {
  int i, j, k;
  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else if (A[i].f <= A[j].f)
      B[k] = A[i++];
    else
      B[k] = A[j++];
  for ( k = l; k <= r; k++ )
    A[k] = B[k];
  return;
}

void MergeSortR(att *A, att *B, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(att *A, int N) {
  int l=1, r=N-1;
  att *B = (att *)malloc((N+1)*sizeof(att));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }
  MergeSortR(A, B, l, r);
}


void displaySol(int pos, att *v, int *opt, int *q){

  if (pos==0)
    return;

  if (attDurata(v[pos])+opt[q[pos]] >= opt[pos-1]) {
    displaySol(q[pos], v, opt, q);
    printf("(%d %d) ", v[pos].s, v[pos].f);
  }
  else
    displaySol(pos-1, v, opt, q);

}
