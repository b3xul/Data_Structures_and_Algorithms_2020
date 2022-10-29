#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 256

typedef struct amico_ {
	int nCanz;
	char **titolo;
} amico;

amico *leggiFile(char *nomeFile, int *na) {
  int i, j;
  char titoloTmp[MAX];
  amico *a;
  FILE *in = fopen(nomeFile, "r");
  if (in == NULL)
    exit(-1);

  fscanf(in, "%d", na);
  a = calloc(*na, sizeof(amico));
  if (a == NULL)
    exit(-1);

  for (i=0; i<*na; i++) {
    fscanf(in, "%d", &a[i].nCanz);
	a[i].titolo = calloc(a[i].nCanz, sizeof(char*));
    for (j=0; j<a[i].nCanz; j++) {
      fscanf(in, "%s", titoloTmp);
      a[i].titolo[j] = strdup(titoloTmp);
    }
  }
  return a;
}

void princ_molt(int pos, amico *a, int *sol, int na, int *cnt) {
  int i;

  if (pos == na) {
    printf("Playlist #%d\n", ++(*cnt));
    for (i=0; i<pos; i++)
       printf(" * %s\n", a[i].titolo[sol[i]]);
    printf("\n");
    return;
  }

  for(i=0;i<a[pos].nCanz;i++) {
	sol[pos] = i;
	princ_molt(pos+1, a, sol, na, cnt);
  }
}

void playlist(amico *a, int na) {
  int *sol, cnt = 0;
  sol = calloc(na, sizeof(int));
  princ_molt(0, a,  sol, na, &cnt);
  free(sol);
}

void libera (amico *a, int na) {
  int i;
  for (i=0; i<na; i++)
    free(a[i].titolo);
  free(a);
}
int main() {
  int na = -1;
  amico *a = leggiFile("brani.txt", &na);
  playlist(a, na);
  libera(a, na);
  return 0;
}
