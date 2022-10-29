#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_PAROLA 26
#define N 20
#define MAX_NP 100

#define filein "testo.txt"
#define filesq "sequenze.txt"

int cercaParola(char seq[MAX_PAROLA], char parole[MAX_NP][MAX_PAROLA], int np);
int leggiParole(FILE *fp, char parole[][MAX_PAROLA]);
int leggiParola(FILE *fp, char parola[MAX_PAROLA]);

int main() {
  int i, n, np;
  char seq[MAX_PAROLA];
  char parole[MAX_NP][MAX_PAROLA];
  FILE *fsq, *fin;

  fin = fopen(filein, "r");
  if (fin == NULL)
    exit(-1);

  np = leggiParole(fin,parole);

  fclose(fin);

  fsq = fopen(filesq, "r");
  if (fsq == NULL)
    exit(-1);

  fscanf(fsq, "%d", &n);

  for (i = 0; i < n; i++) {
    fscanf(fsq, "%s", seq);
    printf("cerco: %s\n", seq);
    if (cercaParola(seq,parole,np)==0) {
      printf("sequenza non trovata\n");
    }
  }

  fclose(fsq);

  return 0;
}

int stristr(char *s1, char *s2) {
    int i = 0, j = 0;

    while(s1[i] != '\0'  && s2[j] != '\0') {
      if(tolower(s1[i]) == tolower(s2[j])) {
        j++ ;
      } else {
        j = 0 ;
      }
      i++;
    }
    return (s2[j] == '\0') ;
}

int cercaParola(char seq[MAX_PAROLA], char parole[MAX_NP][MAX_PAROLA], int np) {
  int i, conta;

  for (i=conta=0; i<np; i++) {
    if (stristr(parole[i], seq)) {
      printf("\t%s %d\n", parole[i], i+1);
      conta++;
    }
  }

  return conta;
}

int leggiParole(FILE *fp, char parole[MAX_NP][MAX_PAROLA]) {
  int i, fine=0;
  for (i=0; i<MAX_NP && !fine; i++) {
    if (leggiParola(fp,parole[i])<=0) {
      fine = 1;
      i--; // fatto perche' i verra' incrementato
    }
  }
  return i;
}

int leggiParola(FILE *fp, char parola[MAX_PAROLA]) {
  int i;
  // cerca primo carattere alfanumerico
  do {
    fscanf(fp, "%c", &parola[0]);
  } while (!feof(fp) && !isalnum(parola[0]));

  if (feof(fp)) return 0;

  // cerca primo carattere non alfanumerico
  i=0;
  do {
    fscanf(fp, "%c", &parola[++i]);
  } while (!feof(fp) && isalnum(parola[i]));
  // aggiungi fine riga
  parola[i] = '\0';
  //  printf("PAROLA: %s\n", parola);
  return i;
}

