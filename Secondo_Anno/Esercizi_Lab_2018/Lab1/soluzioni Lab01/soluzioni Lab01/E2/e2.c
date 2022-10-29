#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXD 30
#define WORD 50
#define RIGA 201
#define FDIZ "dizionario.txt"
#define FIN  "sorgente.txt"
#define FOUT "ricodificato.txt"

typedef struct {
  char parola[WORD];
  char token[WORD];
} entry;

int caricaDizionario(entry diz[], char fileDiz[]);
void processaRiga(char riga[], entry diz[], int nd, FILE *fout);
int confronta(char riga[], int inizio, char parola[], int l);
int confrontaPunt(char riga[], int inizio, char parola[], int l);

int main(void) {
  FILE *fin, *fout;
  entry diz[MAXD];
  int nd;
  char riga[RIGA];

  nd = caricaDizionario(diz, FDIZ);
  fin = fopen(FIN, "r");
  fout = fopen(FOUT, "w");

  if (fin==NULL || fout==NULL ) exit(-1);

  while(fgets(riga, RIGA, fin) != NULL){
    processaRiga(riga, diz, nd, fout);
  }

  fclose(fin);
  fclose(fout);
  return 0;
}

int caricaDizionario(entry diz[], char *fileDiz) {
  int nd, i;
  FILE *in = fopen(fileDiz, "r");
  if (in == NULL)  return 0;

  fscanf(in, "%d", &nd);
  for (i=0; i<nd; i++)
    fscanf(in, "%s %s", diz[i].token, diz[i].parola);
  fclose(in);
  return nd;
}

int confronta(char riga[], int inizio, char parola[], int l) {
  int j;

  for (j=0; j<l; j++) {
    if (riga[inizio+j] != parola[j])
      return 0;
  }
  return 1;
}

int confrontaPunt(char riga[], int inizio, char parola[], int l) {
  return (strncmp(riga+inizio,parola,l)==0);
}

void processaRiga(char riga[], entry diz[], int nd, FILE *fout) {
  int i, j, len, match;

  /* Per ogni carattere di riga */
  for (i=0; riga[i]!='\0'; i++) {
    match = 0;
    /* ... valuta se inizia un match con una parola del dizionario */
    for (j=0; j<nd; j++) {
      len = strlen(diz[j].parola);
      if (confronta(riga,i,diz[j].parola,len)) {
        match = 1; /* Se c'e' match ferma la ricerca */
  			break;
      }
    }
    /* Se ha trovato match ... */
    if (match) {
      /* ... metti token sostitutivo su file di output e avanza il punto di inizio di lend lettere (-1 per compensare l'incremento a seguire del for) */
      fprintf(fout, "%s", diz[j].token);
      i += (len-1);
    } else
      /* ... altrimenti scrivi il solo carattere corrente che non ha permesso di trovare match (il passo di incremento lo fara' il for) */
        fprintf(fout, "%c", riga[i]);
  }
}

