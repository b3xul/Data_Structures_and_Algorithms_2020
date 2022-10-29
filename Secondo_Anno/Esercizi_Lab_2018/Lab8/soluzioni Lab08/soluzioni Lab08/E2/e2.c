#include<stdlib.h>
#include<stdio.h>

typedef struct tile_ {
	char col[2];
	int val[2];
} tile;

typedef struct mossa_ {
	int tile;
	int rot;
} mossa;

tile *leggiTiles(char *filename, int *nTiles) {
  int i;
  FILE *in;
  tile *vTiles;

  if (filename == NULL)
    return NULL;
  in = fopen(filename, "r");
  if (in == NULL)
    return NULL;

  fscanf(in, "%d\n", nTiles);
  vTiles = calloc(*nTiles, sizeof(tile));
  for (i=0; i<*nTiles; i++)
    fscanf(in, "%c %d %c %d\n", &vTiles[i].col[0], &vTiles[i].val[0], &vTiles[i].col[1], &vTiles[i].val[1]);
  return vTiles;
}

mossa **leggiBoard(char *filename, int *R, int *C, int *mark, int nTiles) {
  int i, j;
  FILE *in;
  mossa **board;

  if (filename == NULL)
    return NULL;
  in = fopen(filename, "r");
  if (in == NULL)
    return NULL;

  fscanf(in, "%d %d\n", R, C);
  board = calloc(*R, sizeof(mossa*));
  for (i=0; i<*R; i++) {
    board[i] = calloc(*C, sizeof(mossa));
    for (j=0; j<*C; j++) {
      fscanf(in, "%d/%d", &board[i][j].tile, &board[i][j].rot);
      /* Se c'e' la tessera */
      if (board[i][j].tile >= 0 && board[i][j].tile < nTiles) {
        /* Controllo se e' gia' usata */
        if (mark[board[i][j].tile])
          return NULL; /* Tessera usata due o più volte */
        else
          mark[board[i][j].tile] = 1; /* Marcala come usata */
      }
	}
  }
  return board;
}

int score(mossa **board, tile *vTiles, int R, int C, int nTiles) {
  int sum = 0, part = 0, i, j;
  char first = '\0';

  for (i=0; i<R; i++) { /* Per tutte le righe (check in orizzontale)  */
    part = 0;
    first = '\0';
	for (j=0; j<C; j++) { /* Per tutte le colonne  */
  	  if (board[i][j].tile < 0 || board[i][j].tile >= nTiles) /* Consistenza */
        return -1;
      if (j == 0) {
        /* Memorizza il colore della prima cella incontrata come riferimento */
        first = vTiles[board[i][j].tile].col[(0+board[i][j].rot)%2];
        part = vTiles[board[i][j].tile].val[(0+board[i][j].rot)%2];
      } else {
          if (vTiles[board[i][j].tile].col[(0+board[i][j].rot)%2] == first)
            /* Se la sequenza di colori non è interrotta, incrementa il parziale */
            part += vTiles[board[i][j].tile].val[(0+board[i][j].rot)%2];
          else
		    break;
        }
    }
	if (j == C){
      /* Se la sequenza copre l'intera riga, aggiorna il punteggio */
      sum += part;
    }
  }

  for (i=0;i<C;i++) { 	/* Per tutte le colonne (check in verticale) */
    part = 0;
	first = '\0';
	for (j=0; j<R; j++) { /* Per tutte le righe  */
      if (board[j][i].tile < 0 || board[j][i].tile >= nTiles)/* Consistenza */
        return -1;
  	  if (j == 0) {
        /* Memorizza il colore della prima cella incontrata come riferimento */
		first = vTiles[board[j][i].tile].col[(1+board[j][i].rot)%2];
		part = vTiles[board[j][i].tile].val[(1+board[j][i].rot)%2];
      } else {
   		  if (vTiles[board[j][i].tile].col[(1+board[j][i].rot)%2] == first)
          /* Se la sequenza di colori non è interrotta, incrementa il parziale */
            part += vTiles[board[j][i].tile].val[(1+board[j][i].rot)%2];
          else
            break;
        }
      }
      if (j == R)
        sum += part;
  }
  return sum;
}

void completaR(int pos, mossa **board, tile *vTiles, int R, int C, int nTiles, int *mark, int *bestScore, mossa **bestBoard) {
  int i, j, r, c, currScore;

  if (pos >= (R*C)) { /* Terminazione e check */
	currScore = score(board, vTiles, R, C, nTiles);
    if (currScore > *bestScore) {
      *bestScore = currScore;
      for (i=0; i<R; i++)
        for(j=0;j<C;j++)
          bestBoard[i][j] = board[i][j];
    }
    return;
  }

  r = pos / C;
  c = pos % C;

  if (board[r][c].tile == -1) /* Cella vuota nella board di gioco, prova tutte le tessere disponibili */
    for (i=0; i<nTiles; i++) {
      if (mark[i]) /* Se già usate, procedi */
        continue;
      mark[i] = 1; /* marca la tessera come usata */
      board[r][c].tile = i; /* piazza la tessera sulla board di gioco */
      board[r][c].rot = 0; /* Tessera nella direzione 'originale' */
      completaR(pos+1, board, vTiles, R, C, nTiles, mark, bestScore, bestBoard); /* ricorri sulla prossima */
      board[r][c].rot = 1; /* Tessera nella direzione 'ruotata' */
      completaR(pos+1, board, vTiles, R, C, nTiles, mark, bestScore, bestBoard); /* ricorri sulla prossima */
      /* Backtrack */
      board[r][c].tile = -1;
      mark[i] = 0;
	}
  else /* Cella piena, ricorri sulla successiva */
    completaR(pos+1, board, vTiles, R, C, nTiles, mark, bestScore, bestBoard);
}

void completa(mossa **board, tile *vTiles, int R, int C, int nTiles, int *mark) {
  int bestScore = -1, i, j;
  mossa **bestBoard;

  bestBoard = calloc(R, sizeof(mossa*));
  for (i=0; i<R; i++)
    bestBoard[i] = calloc(C, sizeof(mossa));

  completaR(0, board, vTiles, R, C, nTiles, mark, &bestScore, bestBoard);

  printf ("Soluzione ottima: %d\n", bestScore);
  for (i=0; i<R; i++) {
    for(j=0;j<C;j++)
        printf("%d/%d ", bestBoard[i][j].tile, bestBoard[i][j].rot);
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char **argv) {
  int nTiles = 0, R = 0, C = 0, *mark = calloc(nTiles, sizeof(int));
  tile *vTiles;
  mossa **board;

  vTiles = leggiTiles(argv[1], &nTiles);
  if (vTiles == NULL)
    return -1;

  mark = calloc(nTiles, sizeof(int));
  board = leggiBoard(argv[2], &R, &C, mark, nTiles);
  if (board == NULL)
    return -1;

  completa(board, vTiles, R, C, nTiles, mark);

  return 0;
}
