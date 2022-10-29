#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#define LEN 100

int regexpCmp(char *s, char *regexp);
int regexpLen(char *regexp);
char *cercaRegexp(char *s, char *regexp);
int regexpCmpChar(char c, char *regexp, int *np);

int main(int argc, char **argv) {
  char *src=argv[1], *regexp=argv[2], *exp;
  int len, trovato=0;

  len = regexpLen(regexp);
  printf("src = %s\n", src);
  printf("regexp len (%s) = %d\n", regexp, len);

  do {
    exp = cercaRegexp(src, regexp);
    if (exp) {
      printf("%.*s\n", len, exp);
      /* salta parola trovata. Cercane un'altra (con eventuali sovrapposizioni)*/
      src = exp + 1;
      trovato++;
    }
  } while (exp!=NULL);

  printf("Trovati %d match\n", trovato);

  return 0;
}

int regexpLen(char *regexp) {
  int i, len, salta;

  for (i=len=0; regexp[i]!='\0'; len++,i+=salta) {
    /* non confronta ma salta un elemento in regexp */
    regexpCmpChar(' ',&regexp[i],&salta);
  }
  return len;
}

int regexpCmpChar(char c, char *regexp, int *np) {
  int res, n;
  switch(regexp[0]) {
  case '.':
    res = 1; /* qualunque carattere va bene */
    n = 1;
    break;
  case '\\':
    /* si assume regexp corretta */
    res = regexp[1]=='a' ? islower(c) : isupper(c);
    n = 2;
    break;
  case '[':
    /* principio quantificatori: assumi falso (cambia  assunzione con ^
       cerca un carattere uguale: se esiste cambia assunzione */
    res = 0;
    for(n=1; regexp[n]!=']'; n++) {
      if (regexp[n] == '^') {
        res = 1; /* cambia verdetto */
      }
      else if (regexp[n]==c)
        res = !res;
    }
    n++; /* non si e' ancora contata la ']' */
  break;
  default:
    n = 1;
    res = c==regexp[0];
  }

  *np = n;    /* ritorna caratteri usati in regexp */
  return res; /* ritorna risultato vero/falso */
}

int regexpCmp(char *s, char *regexp) {
  int i, ir, salta;

  for (i=ir=0; regexp[ir]!='\0'; i++, ir+=salta) {
    /* non confronta ma salta un elemento in regexp */
    if (!regexpCmpChar(s[i],&regexp[ir],&salta))
      return 0; /* trovata una differenza */
  }
  return 1;
}


char *cercaRegexp(char *src, char *regexp) {
  int lenSrc, lenR, i;

  lenSrc = strlen(src);
  lenR = regexpLen(regexp);

  for (i=0; i<=lenSrc-lenR; i++) {
    if (regexpCmp(&src[i],regexp))
      return (&src[i]);
  }
  return NULL;
}


