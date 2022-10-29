#include <stdio.h>
#include <stdlib.h>
#define N 4
#define FILENAME "hard_test_set.txt"

int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec);
int verifica(int *sol, int k);

int main(void){
  int  i, s, k, numGemme[N], dispGemme[N], maxlun, bestlun, numtestset;
  char gemme[N] = {'Z', 'R', 'T', 'S'};
  int *sol;
  FILE *in = fopen(FILENAME, "r");
  if (in == NULL)
    return 0;

  fscanf(in, "%d", &numtestset);
  for (s=0; s<numtestset; s++) {
    printf("Test set #%d\n", s+1);
    maxlun = 0;
    for (i=0; i<N; i++) {
      fscanf(in, "%d", &numGemme[i]);
      maxlun += numGemme[i];
    }
    sol = malloc((maxlun) * sizeof(int));

    for (k=maxlun; k>=1; k--) {
      for (i=0; i<N; i++)
        dispGemme[i]=numGemme[i];
      if (disp_ripet(0, dispGemme, sol, N, k, -1)) {
        bestlun = k;
        break;
      }
    }
    printf("Una soluzione a lunghezza massima %d e' ",bestlun);
    for (i=0; i<bestlun; i++)
      printf("%c", gemme[sol[i]]);
    printf("\n");

    free(sol);
  }
  fclose(in);
  return 0;
}


int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec) {
  int i;
  if (pos >= k) {
    return 1;
  }

  for (i = 0; i < n; i++){
    if (dispGemme[i]>0) {
      if (prec != -1) {
        if (((sol[prec]==0) || (sol[prec]==2)) && (i!=0) && (i!=1))
          continue;
        if (((sol[prec]==3) || (sol[prec]==1)) && (i!=2) && (i!=3))
          continue;
      }
      dispGemme[i]--;
      sol[pos] = i;
      if (disp_ripet(pos+1, dispGemme, sol, n, k, pos))
        return 1;
      dispGemme[i]++;
    }
  }
  return 0;
}
