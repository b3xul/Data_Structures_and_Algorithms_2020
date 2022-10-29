#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define R 20
#define C 20
#define LEN 50

void giornate(int mat[R][C], int n, int m);
int cercaMax(int punti[R], int n);

int main(int argc, char **argv) {

  FILE *in = NULL;
  int i, j, n, m, dim, mat[R][C];
  char filename[LEN];

  printf("Inserire nome del file: ");
  scanf("%s", filename);
  in = fopen(filename, "r");
  if (in == NULL)
    return;

  fscanf(in, "%d %d", &n, &m);
  for(i=0;i<n;i++) {
    for(j=0;j<m;j++) {
      fscanf(in, "%d", &mat[i][j]);
    }
  }

  giornate(mat, n, m);

  return 0;
}

void giornate(int mat[R][C], int n, int m) {
  int i, j, punti[R] = {0};
  /* Per ogni giornata */
  for(i=0;i<m;i++) {
	/* Per ogni squadra */
	for(j=0;j<n;j++) {
	  punti[j] += mat[j][i];
    }
	printf("La squadra capolista e' [%d]\n", cercaMax(punti, n));
  }
  return;
}

int cercaMax(int punti[R], int n) {
  int max = -1, i, maxi = -1;
  for(i=0;i<n;i++) {
    if (max < punti[i]) {
	  max = punti[i];
      maxi = i;
    }
  }
  return maxi;
}
