#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#define LEN 21
#define vCount 5

/* Versioni alternative per verificare se un carattere sia una vocale.
Per selezionare una versione modificare opportunamente la #define */

#define vocale vocaleVersione1

/* strategia con vettore di vocali */
int vocaleVersione1(char c) {
  char vocali[vCount] = {'a', 'e', 'i', 'o', 'u'};
  int i;
  c = tolower(c);
  for(i=0;i<vCount;i++)
    if (c == vocali[i])
      return 1;
  return 0;
}

/* strategia con if */
int vocaleVersione2(char c) {
  c = tolower(c);
  if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u')
    return 1;
  return 0;
}

/* strategia con espressione logica */
int vocaleVersione2bis(char c) {
  c = tolower(c);
  return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u');
}

/* strategia con switch-case */
int vocaleVersione3(char c) {
  int ris;

  switch (tolower(c)) {
  case 'a': case 'e': case 'i': case 'o': case 'u': ris = 1;
    break;
  default: ris = 0;
  }
  return ris;
}

int conta(char str[LEN], int n) {
  int i, j, len = strlen(str), cnt = 0, tot = 0;
  for(i=0;i<=len-n;i++) {
    cnt = 0;
    for(j=i;j<i+n;j++) {
      if (vocale(str[j]))
        cnt++;
    }
    if (cnt == 2) {
      tot++;
    }
  }
  return tot;
}

int main(int argc, char *argv[]) {
  FILE *in = NULL;
  char str[LEN];
  int i, n, N, totale, parziale;

  printf("Inserire nome del file: ");
  scanf("%s", str);
  in = fopen(str, "r");
  if (in == NULL)
    return 1;

  do {
    printf("Inserire valore di n: ");
    scanf("%d", &n);
    if (n <= 0 || n >= LEN) {
      printf("Il valore letto: %d non e' ammissibile\n", n);
    }
  } while (n <= 0 || n >= LEN);

  totale = 0;
  fscanf(in, "%d\n", &N);
  for(i=0;i<N;i++) {
    fscanf(in, "%s", str);
    printf("%s\n", str);
    parziale = conta(str,n);
    totale += parziale;
    printf("Numero di sottostringhe valide di lunghezza %d: %d\n", n, parziale);
  }
  printf("Numero complessivo di sottostringhe valide di lunghezza %d: %d\n", n, totale);
  return 0;
}
