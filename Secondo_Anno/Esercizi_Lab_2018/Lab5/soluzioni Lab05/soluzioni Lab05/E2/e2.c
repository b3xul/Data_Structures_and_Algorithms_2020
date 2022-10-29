#include <stdlib.h>
#include <stdio.h>

int **malloc2dR(int *nr, int *nc, FILE *fp) {
  int i, j, **mat;
  fscanf(fp, "%d %d", nr, nc);
  mat = (int**) calloc(*nr, sizeof(int*));
  for (i=0; i<*nr; i++) {
    mat[i] = (int*) calloc(*nc, sizeof(int));
    for (j=0; j<*nc; j++)
      fscanf(fp, "%d", &mat[i][j]);
  }
  return mat;
}

void malloc2dP(int ***mat, int *nr, int *nc, FILE *fp) {
  int i, j;
  fscanf(fp, "%d %d", nr, nc);
  *mat = (int**) calloc(*nr, sizeof(int*));
  for (i=0; i<*nr; i++) {
    (*mat)[i] = (int*) calloc(*nc, sizeof(int));
    for (j=0; j<*nc; j++)
      fscanf(fp, "%d", &(*mat)[i][j]);
  }
}

void separa(int **mat, int nr, int nc, int **w, int **b, int *nw, int *nb) {
  int i, j, wcnt = 0, bcnt = 0, sq = nr*nc;
  *nw = sq/2;
  *nb = sq/2 + sq%2;
  *w = (int*) calloc(*nw, sizeof(int));
  *b = (int*) calloc(*nb, sizeof(int));
  for(i=0;i<nr;i++) {
    for(j=0;j<nc;j++) {
      if ((i+j)%2) {
        (*w)[wcnt++] = mat[i][j];
      } else
        (*b)[bcnt++] = mat[i][j];
    }
  }
}

void stampa(int *vett, int n) {
  int i;
	for(i=0;i<n;i++)
      printf("%d ", vett[i]);
  printf("\n");
}

int main(int argc, char **argv) {
  int **mat, *w, *b, nr, nc, nw, nb;
  FILE *fp = fopen("mat1.txt", "r");
  if (fp == NULL)
    return -1;
  mat = malloc2dR(&nr, &nc, fp);
  /* malloc2dP(&mat, &nr, &nc, fp); */
  fclose(fp);

  separa(mat, nr, nc, &w, &b, &nw, &nb);
  printf("Celle bianche\n");
  stampa(w, nw);
  printf("Celle nere\n");
  stampa(b, nb);

  free(w);
  free(b);

  return 0;
}
