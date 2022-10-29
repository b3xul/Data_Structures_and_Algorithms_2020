#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_MATCH 10
#define MAX_PAROLA 26
#define MAX_RIGA 201
#define MAX_INC 6
#define N 20

#define filein "testo.txt"
#define filesq "sequenze.txt"

typedef struct match_ {
  char str[MAX_PAROLA];
  int pos;
} match_t;

typedef struct indice_ {
  char incipit[MAX_INC];
  int lung_inc;
  int n_match;
  match_t match[MAX_MATCH];
} indice_t;

int leggiSequenze(indice_t indice[N]);
int processaRiga(char riga[MAX_RIGA], indice_t indice[N], int n, int wordCount);
void stampaMatch(indice_t indice[N], int n);

int main() {
  indice_t indice[N];
  int n, posParola = 0;
  char riga[MAX_RIGA];
  FILE *fin;

  n = leggiSequenze(indice);

  fin = fopen(filein, "r");
  if (fin == NULL)
    exit(-1);

  while(fgets(riga, MAX_RIGA, fin) != NULL){
    posParola = processaRiga(riga, indice, n, posParola);
  }

  fclose(fin);

  stampaMatch(indice, n);

  return 0;
}

int leggiSequenze(indice_t indice[N]) {
  FILE *fp;
  int i, n;

  fp = fopen(filesq, "r");
  if (fp == NULL) {
    printf("Errore apertura file di sequenze\n");
    exit(-1);
  }

  if (fscanf(fp, "%d", &n) != 1) {
    printf("Errore in lettura del numeri di sequenze\n");
    exit(1);
  }

  for (i = 0; i < n; i++) {
    fscanf(fp, "%s", indice[i].incipit);
    indice[i].lung_inc = strlen(indice[i].incipit);
    indice[i].n_match = 0;
  }
  fclose(fp);
  return n;
}
int trovaParola(char riga[], int lun, int i, char parolaCorr[MAX_PAROLA]) {
  int lungParola=0;

  while((lungParola+i) < lun && lungParola < MAX_PAROLA && isalnum(riga[(lungParola+i)])) {
    parolaCorr[lungParola] = riga[i+lungParola];
    lungParola++;
  }
  parolaCorr[lungParola] = '\0';
  return lungParola;
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

void cercaSeq(indice_t indice[N], int n, char parolaCorr[MAX_PAROLA], int posParola) {
  int i, continua=1;
  for(i=0;i<n && continua;i++) {
    if (stristr(parolaCorr, indice[i].incipit)) {
		  if(indice[i].n_match < MAX_MATCH) {
            strcpy(indice[i].match[indice[i].n_match].str, parolaCorr);
            indice[i].match[indice[i].n_match++].pos = posParola;
            continua =0;
          }
        }
      }
  return;
}

int processaRiga(char riga[MAX_RIGA], indice_t indice[N], int n, int posParola) {
  int i, lun = strlen(riga), lungParola;
  char parolaCorr[MAX_PAROLA] = {'\0'};

  // Per ogni carattere di riga
  for (i=0; i<lun; i++) {

    // se alla posizione corrente inizia una stringa alfanumerica
    if (isalnum(riga[i])) {
      posParola++;
      lungParola = trovaParola(riga, lun, i, parolaCorr);
      cercaSeq(indice, n, parolaCorr, posParola);
      i += lungParola-1;
    }
  }
  return posParola;
}

void stampaMatch(indice_t indice[N], int n) {
  int i, j;
  for(i=0;i<n;i++) {
    if (indice[i].n_match != 0){
      printf("%s\n", indice[i].incipit);
      for(j=0;j<indice[i].n_match;j++) {
        printf("\t%s %d\n", indice[i].match[j].str, indice[i].match[j].pos);
      }
    }
  }
}
