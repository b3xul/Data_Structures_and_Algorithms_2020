#include <stdio.h>
#include <stdlib.h>
#define N 4
#define FILENAME "very_very_easy_test_set.txt"

int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec);
int verifica(int *sol, int *dispGemme, int k);

int main(void){
  int  i, s, k, *sol, numGemme[N], dispGemme[N], maxlun, bestlun, numtestset;
  char gemme[N] = {'Z', 'R', 'T', 'S'};
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

    for (k=1; k<=maxlun; k++) {
      for (i=0; i<N; i++)
        dispGemme[i]=numGemme[i];
      if (disp_ripet(0, dispGemme, sol, N, k, -1)) {
        bestlun = k;
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

/* soluzione senza pruning: tute le verifiche (molteplicità gemme e regole di composizione) fatte nella condizione di terminazione */
int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec) {
  int i;
  if (pos >= k) {
    if (verifica(sol, dispGemme, k))
      return 1;
    return 0;
  }

  for (i = 0; i < n; i++){
    sol[pos] = i;
    if (disp_ripet(pos+1, dispGemme, sol, n, k, pos))
      return 1;
  }
  return 0;
}

int verifica(int *sol, int *dispGemme, int k) {
  int i, usGemme[N] = {0};

  for(i=0; i<k; i++) {
    usGemme[sol[i]]++;
    if (usGemme[sol[i]] > dispGemme[sol[i]])
      return 0;
    if (i!=0) {
      if (((sol[i-1]==0) || (sol[i-1]==2)) && (sol[i]!=0) && (sol[i]!=1))
        return 0;
      if (((sol[i-1]==3) || (sol[i-1]==1)) && (sol[i]!=3) && (sol[i]!=2))
        return 0;
    }
  }
  return 1;
}

