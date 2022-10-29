#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define N 4
#define DBG 1
#define FILENAME "test_set.txt"


int disp_ripet(int pos, int val, int *sol, int *numGemme, int * valGemme, int *usGemme, int *ripGemme, int maxlun, int prec, int *bestSol, int *bestval, int *bestlun, int maxrip) {
  int i, precrip=0;
  if (val > *bestval) {
    if (usGemme[0] <= usGemme[3]){
      *bestval = val;
      *bestlun = pos;
      for (i=0; i<N; i++)
        bestSol[i]= sol[i];
    }
  }
  if (pos >= maxlun) {
    return 1;
  }

  for(i=0;i<N;i++) {
    if (numGemme[i]-usGemme[i] > 0) {
      if (prec != -1) {
        if (((prec == 0) || (prec == 2)) && (i != 0 && i != 1))
          continue;
        if (((prec == 1) || (prec == 3)) && (i != 3 && i != 2))
          continue;
      }
      if (prec == i) {
        if (ripGemme[i]+1 > maxrip)
          continue;
      }

      if (prec == -1)
        ripGemme[i] = 1;
      else
        if (prec == i)
          ripGemme[i]++;
        else {
          ripGemme[i] = 1;
          precrip = ripGemme[prec];
          ripGemme[prec] = 0;
        }
      usGemme[i]++;
      sol[pos] = i;

      if (disp_ripet(pos+1, val+ valGemme[i], sol, numGemme,  valGemme, usGemme, ripGemme, maxlun, i, bestSol, bestval, bestlun, maxrip))
        return 1;

      usGemme[i]--;
      if (prec == -1)
        ripGemme[i] = 0;
      else
        if (prec == i)
          ripGemme[i]--;
        else {
          ripGemme[i] = 0;
          ripGemme[prec] = precrip;
        }
    }
  }

  return 0;
}

void solve(char *gemme, int *numGemme, int * valGemme, int maxlun, int maxrip) {
  int i, *sol = calloc(maxlun, sizeof(int)), *bestSol = calloc(maxlun, sizeof(int)), *usGemme = calloc(N, sizeof(int)), *ripGemme = calloc(N, sizeof(int)), bestval = -1, bestlun = -1;

  disp_ripet(0, 0, sol, numGemme,  valGemme, usGemme, ripGemme, maxlun, -1, bestSol, &bestval, &bestlun, maxrip);

  printf("Soluzione ottima di valore %d usando %d gemma/e\n", bestval, bestlun);
  printf("Composizione collana: ");
  for (i=0; i<bestlun; i++)
    printf("%c", gemme[bestSol[i]]);
  printf("\n");
  free(usGemme);
  free(ripGemme);
  free(bestSol);
  free(sol);
  return;
}

int main(int argc, char **argv) {
  int i, s, numtestset, maxlun, numGemme[N], valGemme[N], maxrip;
  char gemme[N] = {'Z', 'R', 'T', 'S'};

  FILE *in = fopen(FILENAME, "r");
  if (in == NULL)
    return 0;

  fscanf(in, "%d", &numtestset);
  for (s=0; s<numtestset; s++) {
    printf("Test set #%d\n", s+1);
    maxlun = 0;
    for(i=0;i<N;i++) {
      fscanf(in, "%d", &numGemme[i]);
      maxlun += numGemme[i];
    }
    for(i=0;i<N;i++) {
      fscanf(in, "%d", &valGemme[i]);
      printf("%c = %d [%d], ", gemme[i], numGemme[i], valGemme[i]);
    }
    fscanf(in, "%d", &maxrip);
    printf("TOT = %d {maxrip = %d}\n", maxlun, maxrip);
    solve(gemme, numGemme,  valGemme, maxlun, maxrip);
  }
  fclose(in);
  return 0;
}
