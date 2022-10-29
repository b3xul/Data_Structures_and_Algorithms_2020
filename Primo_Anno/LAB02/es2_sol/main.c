#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define MAX 20

typedef enum {NO, NE, SO, SE} quadr_t;

void leggiMat(FILE *in, int mat[MAX][MAX], int r, int c) {
  int i, j;

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      fscanf(in, "%d", &mat[i][j]);
}

void stampaMat(int mat[MAX][MAX], int r, int c) {

  int i, j;
  printf("%d %d\n", r, c);
  for(i=0;i<r;i++) {
    for(j=0;j<c;j++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }
}

void qualequadrante(int quadrante[4], int i, int j, int x, int y ) {
  int k;
  for(k=0; k<4; k++)
    quadrante[k]=0;

  if (i < x && j < y)
    quadrante[0] = 1;
  if (i < x && j > y)
    quadrante[1] = 1;
  if (i > x && j < y)
    quadrante[2] = 1;
  if (i > x && j > y)
    quadrante[3] = 1;
}

void sottomatrici(int mat[MAX][MAX], int r, int c, int x, int y) {
  int i, j;
  quadr_t dir;
  int quadrante[4] = {0};
  int somma[4] = {0};

  for(i=0;i<r;i++)      //per ogni casella somma l'indice del vettore somma relativo al quadrante a cui appartiene quella casella
    if (i != x)
      for(j=0;j<c;j++)
        if (j!= y) {
          qualequadrante(quadrante, i, j, x, y);
          for (dir=NO; dir<=SE; dir++)
            if(quadrante[dir])
              somma[dir] += mat[i][j];
        }
  for (dir=NO; dir<=SE; dir++)
    switch (dir) {
      case NO: printf("NO = %d\n", somma[dir]);
      break;
      case NE: printf("NE = %d\n", somma[dir]);
      break;
      case SO: printf("SO = %d\n", somma[dir]);
      break;
      case SE: printf("SE = %d\n", somma[dir]);
      break;
 }

  return;
}

int main() {
	int r, c, x=0, y=0, mat[MAX][MAX], continua=1;
	FILE *in = fopen("l2e3.txt", "r");

	fscanf(in, "%d %d", &r, &c);
	leggiMat(in, mat, r, c);
	fclose(in);
	stampaMat(mat, r, c);

	do {
	  printf("Inserisci la coppia di coordinate\n");
	  printf("r = ");
	  scanf("%d", &x);
	  printf("c = ");
	  scanf("%d", &y);
	  if (x < 0 || y < 0 || x >= r || y >= c)
	    continua=0;
	  else
	    sottomatrici(mat, r, c, x, y);

	} while(continua);


	return 0;
}
