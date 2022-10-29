#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int *leggiFile(FILE *in, int *n) {
  int i, *val;
  fscanf(in, "%d\n", n);
  val = calloc((*n+1), sizeof(int));
  val[0] = 0;
  for (i=1; i<=*n; i++)
    fscanf(in, "%d \n", &val[i]);
  return val;
}

int max(int x, int y){
  if (x>=y)
    return x;
  return y;
}

int solveR(int *val, int *opt, int n, int k) {
  if (k==0)
    return 0;
  if (k==1)
    return val[1];

  return max(solveR(val, opt, n, k-1), solveR(val, opt, n, k-2) + val[k]);
}
void solve(int *val, int n) {
  int *opt;
  opt = calloc((n+1),sizeof(int));
  printf("Recursive solution: maximum population covered %d\n", solveR(val, opt, n, n));
}

void displaySol(int *opt, int *val, int n){
  int i, *sol;

  sol = calloc((n+1),sizeof(int));
  sol[1]=1;
  i=n;
  while (i>=2) {
    if (opt[i] == opt[i-1]){
      sol[i] = 0;
      i--;
    }
    else if (opt[i] == opt[i-2] + val[i]) {
      sol[i] = 1;
      sol[i-1] = 0;
      i -=2;
    }
  }

  for (i=1; i<=n; i++)
    if (sol[i])
      printf("%d ", val[i]);
  printf("\n");
}

void solveDP(int *val, int n) {
  int i, *opt;
  opt = calloc((n+1),sizeof(int));

  opt[1] = val[1];

  for (i=2; i<=n; i++) {
    if (opt[i-1] > opt[i-2]+val[i]) {
      opt[i] = opt[i-1];
    }
    else {
      opt[i] = opt[i-2] + val[i];
    }
  }


  printf("Dynamic programming  solution: maximum population covered %d\n", opt[n]);

  displaySol(opt, val, n);
}

int main(int argc, char **argv) {
  int i, n, *val;
  FILE *in;

  in = fopen("val3.txt", "r");
  if (in == NULL)
    exit(-1);

  val = leggiFile(in, &n);

  printf("n=%d\n", n);
  for (i=1; i<=n; i++)
    printf("%d ", val[i]);
  printf("\n");

  solve(val, n);
  solveDP(val, n);

  fclose(in);
  return 0;
}

