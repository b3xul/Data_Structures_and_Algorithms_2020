#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_PAROLA 26
#define N 20

#define filein "testo.txt"
#define filesq "sequenze.txt"

int cercaParola(char seq[MAX_PAROLA]);
int leggiParola(FILE *fp, char parola[MAX_PAROLA]);

int main() {
  int i, n;
  char seq[MAX_PAROLA];
  FILE *fsq;

  fsq = fopen(filesq, "r");
  if (fsq == NULL)
    exit(-1);

  fscanf(fsq, "%d", &n);

  for (i = 0; i < n; i++) {
    fscanf(fsq, "%s", seq);
    printf("cerco: %s\n", seq);
    if (cercaParola(seq)==0) {
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

int cercaParola(char seq[MAX_PAROLA]) {
  FILE *fp;
  char parola[MAX_PAROLA];
  int i, conta;

  fp = fopen(filein, "r");
  if (fp == NULL) {
    printf("Errore apertura file delle parole\n");
    exit(-1);
  }

  for (i=1,conta=0; leggiParola(fp,parola)>0; i++) {
    if (stristr(parola, seq)) {
      printf("\t%s %d\n", parola, i);
      conta++;
    }
  }

  fclose(fp);

  return conta;
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

