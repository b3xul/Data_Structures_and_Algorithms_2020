#include<stdlib.h>
#include<stdio.h>

#define R 50
#define C 50

void leggiMatrice(int mat[][C], int *nr, int *nc);
void stampaMatrice(int mat[][C], int nr, int nc);
int riconosciRegione(int mat[][C], int nr, int nc, int r, int c, int *b, int *h);

int main(int argc, char **argv) {
  int M[R][C], nr, nc, i, j, b, h;
  int rettHx = -1, rettHy = -1, rettAx = -1, rettAy = -1, rettBx = -1, rettBy = -1;
  int rettHb = 0, rettHh = 0, rettAb = 0, rettAh = 0, rettBb = 0, rettBh = 0;;

  leggiMatrice(M, &nr, &nc);
  stampaMatrice(M, nr, nc);

  for (i=0; i<nr; i++) {
    for(j=0;j<nc;j++) {
      b = 0;
      h = 0;
      if (riconosciRegione(M, nr, nc, i, j, &b, &h)) {
        /* Aggiorna (eventualmente) le regioni con massima base, massima area e massima altezza per poi stamparle a termine scansione */
        if (rettBx == -1 || rettBb < b) {
            rettBx = i;
            rettBy = j;
            rettBb = b;
            rettBh = h;
        }
        if (rettAx == -1 || rettAb*rettAh < b*h) {
            rettAx = i;
            rettAy = j;
            rettAb = b;
            rettAh = h;
        }
        if (rettHx == -1 || rettHb < h) {
            rettHx = i;
            rettHy = j;
            rettHb = b;
            rettHh = h;
        }
      }
    }
  }
  printf("Max Base: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", rettBx, rettBy, rettBb, rettBh, rettBb*rettBh);
  printf("Max Area: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", rettAx, rettAy, rettAb, rettAh, rettAb*rettAh);
  printf("Max Altezza: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", rettHx, rettHy, rettHb, rettHh, rettHb*rettHh);

  return 0;
}

void leggiMatrice(int mat[][C], int *nrp, int *ncp) {
  int i, j;
  FILE *in = fopen("mat.txt", "r");
  if (in == NULL)
    exit(-1);
  fscanf(in, "%d %d", nrp, ncp);
  for (i=0; i<*nrp; i++)
    for (j=0; j<*ncp; j++)
      fscanf(in, "%d", &mat[i][j]);
  fclose(in);
  return;
}

void stampaMatrice(int mat[][C], int nr, int nc) {
  int i, j;
  for (i=0; i<nr; i++) {
    for (j=0; j<nc; j++)
      printf("%d ", mat[i][j]);
	printf("\n");
  }
  return;
}

int riconosciRegione(int mat[][C], int nr, int nc, int r, int c, int *pb, int *ph) {
  int x, y, b, h;
  if (mat[r][c] != 1)
    return 0;
  x = r;
  y = c;
  while (y<nc && mat[x][y] == 1)
    y++;
  b = y - c;
  y = c;
  while (x<nr && mat[x][y] == 1)
    x++;
  h = x - r;
  for (x=0; x<h; x++)
    for (y=0; y<b; y++)
      mat[r+x][c+y] = 2;
  *pb = b;
  *ph = h;
  return 1;
}
