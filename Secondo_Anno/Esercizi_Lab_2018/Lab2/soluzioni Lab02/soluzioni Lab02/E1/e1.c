#include<stdlib.h>
#include<stdio.h>

#define R 50
#define C 50

typedef struct {int r; int c;} dim;
typedef struct {int b; int h; int x; int y; } rett;


dim leggiMatrice(int mat[][C]);
void stampaMatrice(int mat[][C], dim dimensioni);
rett riconosciRegione(int mat[][C], dim dimensioni, int r, int c);

int main(int argc, char **argv) {
  int M[R][C], i, j;
  dim dimensioni;
  rett rettangolo, rettH, rettB, rettA;
  rettH.x = rettH.y = rettA.x = rettA.y = rettB.x = rettB.y = -1;

  dimensioni = leggiMatrice(M);
  stampaMatrice(M, dimensioni);

  for (i=0; i<dimensioni.r; i++) {
    for(j=0;j<dimensioni.c;j++) {
      rettangolo.b = 0;
      rettangolo.h = 0;
      rettangolo = riconosciRegione(M, dimensioni, i, j);
      if (rettangolo.b!=0 && rettangolo.h!=0) {
        /* Aggiorna (eventualmente) le regioni "migliori" per poi stampare a termine scansione */
        if (rettB.x == -1 || rettB.b < rettangolo.b) rettB = rettangolo;
        if (rettA.x == -1 || (rettA.b * rettA.h) < (rettangolo.b * rettangolo.h)) rettA = rettangolo;
        if (rettH.x == -1 || rettH.h < rettangolo.h) rettH = rettangolo;
      }
    }
  }
  printf("Max Base: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", rettB.x, rettB.y, rettB.b, rettB.h, rettB.b*rettB.h);
  printf("Max Area: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", rettA.x, rettA.y, rettA.b, rettA.h, rettA.b*rettA.h);
  printf("Max Altezza: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", rettH.x, rettH.y, rettH.b, rettH.h, rettH.b*rettH.h);

  return 0;
}

dim leggiMatrice(int mat[][C]) {
  int i, j, nr, nc;
  dim dimensioni;
  FILE *in = fopen("mappa.txt", "r");
  if (in == NULL)
    exit(-1);

  fscanf(in, "%d %d", &nr, &nc);
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
      fscanf(in, "%d", &mat[i][j]);
  dimensioni.r = nr;
  dimensioni.c = nc;
  fclose(in);
  return dimensioni;
}

void stampaMatrice(int mat[][C], dim dimensioni) {
  int i, j;
  for (i=0; i<dimensioni.r; i++) {
    for (j=0; j<dimensioni.c; j++)
      printf("%d ", mat[i][j]);
	printf("\n");
  }
  return;
}

rett riconosciRegione(int mat[][C], dim dimensioni, int r, int c) {
  int x, y, b=0, h=0;
  rett rettangolo;

  if (mat[r][c] != 1 || (r>0 && (mat[r-1][c] == 1)) || (c>0 && (mat[r][c-1] == 1))) {
    rettangolo.b = b;
    rettangolo.h = h;
    return rettangolo;
  }
  /* si tratta di angolo in alto a sinistra di un rettangolo */
  x = r;
  y = c;
  while (y<dimensioni.c && mat[x][y] == 1)
    y++;
  b = y - c;
  y = c;
  while (x<dimensioni.r && mat[x][y] == 1)
    x++;
  h = x - r;

  rettangolo.b = b;
  rettangolo.h = h;
  rettangolo.x = r;
  rettangolo.y = c;

  return rettangolo;
}
