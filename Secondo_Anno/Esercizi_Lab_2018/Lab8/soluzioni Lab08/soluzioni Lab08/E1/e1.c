#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct att_ {
  int s, f;
} att;

int dA(att a) {
  return a.f - a.s;
}

att *attLeggi(FILE *in, int *n) {
  int i;
  att *v;
  fscanf(in, "%d\n", n);
  v = calloc(*n, sizeof(att));
  for (i=0; i<*n; i++)
    fscanf(in, "%d %d\n", &v[i].s, &v[i].f);
  return v;
}

int overlapA(int n, att *v, int *sol, int pos) {
  int i;

  for (i=0; i<pos; i++) {
    if (sol[i] != 0) {
      if (v[i].s < v[pos].f && v[pos].s < v[i].f)
        return 1;
    }
  }
  return 0;
}

void attSelR(int pos, int n, att *v, int *sol, int *bestsol,  int currDurata, int *bestDurata) {
  int i;
  if (pos >= n) {
    if (*bestDurata < currDurata) {
      *bestDurata = currDurata;
      for (i=0; i<n; i++)
        bestsol[i] = sol[i];
    }
    return;
  }

  sol[pos] = 0;
  attSelR(pos+1, n, v, sol, bestsol, currDurata, bestDurata);
  if (!overlapA(n, v, sol, pos)) {
    sol[pos] = 1;
    attSelR(pos+1, n, v, sol, bestsol,  currDurata+dA(v[pos]), bestDurata);
  }

  return;
}

void attSel(int n, att *v) {
  int *sol = calloc(n, sizeof(int));
  int *bestsol = calloc(n, sizeof(int));
  int duration = 0, i;

  attSelR(0, n, v, sol, bestsol, 0, &duration);

  printf("Soluzione a durata complessiva massima %d\n", duration);
  for (i=0; i<n; i++)
    if (bestsol[i])
      printf(" (%d,%d)", v[i].s, v[i].f);
  printf("\n");

  free(sol);
  free(bestsol);

  return;
}

int main(int argc, char **argv) {
  int n;
  FILE *in;
  att *v;

  in = fopen("att1.txt", "r");
  if (in == NULL)
    exit(-1);

  v = attLeggi(in, &n);
  attSel(n, v);

  fclose(in);
  return 0;
}
