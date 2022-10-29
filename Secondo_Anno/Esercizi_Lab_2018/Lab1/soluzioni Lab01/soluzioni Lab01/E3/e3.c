#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 30
#define LEN 21

typedef struct {
	int r, c;
} matmaxN;

matmaxN leggiMatrice(char *file, int mat[][maxN]);
void ruotaVettore1(int V[maxN], int dir, int N, int P);
void ruotaVettore2(int V[maxN], int dir, int N, int P);
void ruotaVettore3(int V[maxN], int dir, int N, int P);
void ruotaVettore4(int V[maxN], int dir, int N, int P);
void ruotaMatrice(int mat[][maxN], char r_o_c, int target, int maxN1, int maxN2, int P, char direzione[maxN], int strategia);
void stampaMatrice(FILE *out, int mat[][maxN], int nr, int nc);

int main(int argc, char **argv) {
  matmaxN mmaxN;
  int mat[maxN][maxN], r, c, continua = 1, target = 0, pos = 1, strategia = 1;
  char cmd[256], selettore[LEN], filename[LEN], direzione[LEN], r_o_c;

  if (argc>1) {
    strategia = atoi(argv[1]);
    if (strategia<1 || strategia>4)
      strategia = 1;
  }

  printf("Inserire nome del file: ");
  scanf("%s", filename);

  mmaxN = leggiMatrice(filename, mat);
  r = mmaxN.r;
  c = mmaxN.c;

  do {
		stampaMatrice(stdout, mat, r, c);
		printf("Comando > ");
		fgets(cmd, 255, stdin);
		sscanf(cmd, "%s %d %s %d", selettore, &target, direzione, &pos);

		if (pos > 0) {
			if (strcmp(selettore,"riga")==0) {
					if (target <= 0 || target > r) {
						printf("Errore selezione riga\n");
						return 1;
					}
					r_o_c = 'r';
					ruotaMatrice(mat, r_o_c, target, r, c, pos, direzione, strategia);
			 } else if (strcmp(selettore,"colonna")==0) {
					if (target <= 0 || target > c) {
						printf("Errore selezione colonna\n");
						return 1;
					}
					r_o_c = 'c';
					ruotaMatrice(mat, r_o_c, target, r, c, pos, direzione, strategia);
			 } else if (strcmp(selettore,"fine")==0) {
					continua=0;
			 } else {
					printf("riga|colonna|fine [target] [pos] [dir]\n");
			 }
		}
  } while (continua);
  return 0;
}

void ruotaMatrice(int mat[][maxN], char r_o_c, int target, int maxN1, int maxN2, int P, char direzione[], int strategia) {
  int vet[maxN], i, dir = 0;
  if ((strcmp(direzione, "destra")== 0) || (strcmp(direzione, "giu")== 0))
    dir = -1;
  else if ((strcmp(direzione, "sinistra")== 0) || (strcmp(direzione, "su")== 0))
    dir = 1;
  if ((dir !=1) && (dir !=-1)){
    printf("errore direzione\n");
    return;
  }
  if (r_o_c == 'r')
    switch (strategia) {
      case 1: ruotaVettore1(mat[target-1], dir, maxN2, P);
              break;
      case 2: ruotaVettore2(mat[target-1], dir, maxN2, P);
              break;
      case 3: ruotaVettore3(mat[target-1], dir, maxN2, P);
              break;
      case 4: ruotaVettore4(mat[target-1], dir, maxN2, P);
              break;
      default: printf("errore: strategia errata\n");
    }
  else if (r_o_c == 'c') {
    for (i=0; i<maxN1; i++)
      vet[i] = mat[i][target-1];
    switch (strategia) {
      case 1: ruotaVettore1(vet, -dir, maxN1, P);
              break;
      case 2: ruotaVettore2(vet, -dir, maxN1, P);
              break;
      case 3: ruotaVettore3(vet, -dir, maxN1, P);
              break;
      case 4: ruotaVettore4(vet, -dir, maxN1, P);
              break;
      default: printf("errore: strategia errata\n");
    }
    for (i=0; i<maxN1; i++)
      mat[i][target-1] = vet[i];
  }
}

matmaxN leggiMatrice(char *file, int mat[][maxN]) {
  int i, j;
  matmaxN md;
  FILE *in = fopen(file, "r");
  if (in == NULL)
    exit(-1);
  fscanf(in, "%d %d", &md.r, &md.c);
  for(i=0; i<md.r; i++)
    for(j=0;j<md.c;j++)
	  	fscanf(in, "%d", &mat[i][j]);
  fclose(in);
  return md;
}

void stampaMatrice(FILE *out, int mat[][maxN], int nr, int nc) {
  int i, j;
  for (i=0; i<nr; i++) {
    for(j=0; j<nc; j++)
      fprintf(out, "%d ", mat[i][j]);
		fprintf(out, "\n");
  }
  fprintf(out, "\n");
  return;
}

void ruotaVettore1(int V[maxN], int dir, int N, int P) {
  int tmp, i, j;

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
