#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>

#define SIZE 16
#define INPUT 0

/*
intero 1 su 32 bit (4 byte)

LITTLE ENDIAN: byte meno significativo a indirizzo piu' piccolo

       higher memory
          ----->
    +----+----+----+----+
    |0x01|0x00|0x00|0x00|
    +----+----+----+----+
    x
    |
   &x

BIG ENDIAN: byte piu' significativo a indirizzo piu' piccolo

    +----+----+----+----+
    |0x00|0x00|0x00|0x01|
    +----+----+----+----+
    x
    |
   &x

*/

/* sceglie la funzione di codifica da usare */
#define stampaCodifica stampaCodifica1
/* sceglie la funzione per separare i bit */
#define separaBit separaBit3

void stampaCodifica1 (void *p, int size, int bigEndian);
void stampaCodifica2 (void *p, int size, int bigEndian);
void stampaMemoria (void *p, int size, int bigEndian);
int checkBigEndian(void);

int main(int argc, char *argv[]) {

  float af;
  double ad;
  long double ald;

  int bigEndian = checkBigEndian();
  printf ("Il sistema e': %s ENDIAN\n", bigEndian ? "BIG":"LITTLE");

  printf("Dimensioni\n af = %d\n ad = %d\nald = %d\n",
	 (int)sizeof(af), (int)sizeof(ad), (int)sizeof(ald));

  printf("Inserire un valore (compatibile con float, double e long double): ");
  scanf("%f", &af);
  printf("Ho letto: %f\n", af);

  ad = (double)af;
  ald = (long double)af;

  printf("\nstampa della codifica float:\n");
  /* stampaMemoria e' ridondante (non richiesta ma utile per 'vedere' i bit) */
  stampaMemoria((void *)&af,sizeof(af),bigEndian);
  stampaCodifica((void *)&af,sizeof(af),bigEndian);

  printf("\nstampa della codifica double:\n");
  /* stampaMemoria e' ridondante (non richiesta ma utile per 'vedere' i bit) */
  stampaMemoria((void *)&ad,sizeof(ad),bigEndian);
  stampaCodifica((void *)&ad,sizeof(ad),bigEndian);

  printf("\nstampa della codifica long double:\n");
  /* stampaMemoria e' ridondante (non richiesta ma utile per 'vedere' i bit) */
  stampaMemoria((void *)&ald,sizeof(ald),bigEndian);
  stampaCodifica((void *)&ald,sizeof(ald),bigEndian);

  return 0;
}

int checkBigEndian(void) {
  int test = 1; /* solo il byte meno significativo !=0, gli altri tutti ==0 */
  char *pchar = (char *)&test; /* punta al byte di indirizzo più piccolo */
  /* guarda il byte di indirizzo più piccolo: se ==0 Big Endian */
  return (*pchar == 0); /* sintassi di tipo puntatore */
  /* return (pchar[0] == 0); */ /*  sintassi alternativa a vettore */
}

void stampaMemoria (void *p, int size, int bigEndian) {
  int i, j;

  /* unsigned per vedere i byte come numeri da 0 a 255 (FF) */
  /* puntatore usato come vettore di unsigned char */
  unsigned char *pchar = (unsigned char *)p;

  printf("stampo i byte in esadecimale (indirizzo: contenuto)\n");
  for (i=0; i<size; i++) {
    printf("%p: %02x\n", &pchar[i], pchar[i]); /* %02x per scrivere sempre 2 cifre */
  }

  printf("stampo i byte dal piu' (sinistra) al meno significativo (destra):\n");
  for (i=0; i<size; i++) {
    j = bigEndian ? i : size-1-i;
    printf("%02x", pchar[j]); /* %02x per scrivere sempre 2 cifre */
  }
  printf("\n");
}

/* riconosce i bit dal meno significativo e li accumula nel */
/* vettore di char (0/1) a partire dalla casella l; */
void separaBit1(unsigned char byte, char *bits, int l) {
  int i;
  for (i=0; i<8; i++, byte /= 2) {
    bits[l+i] = byte%2; /* pari: 0, dispari: 1 */
  }
}

/* riconosce i bit dal meno significativo e li accumula nel
   vettore di char (0/1) a partire dalla casella l;
   variante con >> (shift) per /2 e AND bit a bit per leggere bit meno signiifcativo */
void separaBit2(unsigned char byte, char *bits, int l) {
  int i;

  /* divide byte per 2 mediante shift di 1 posizione a destra */
  for (i=0; i<8; i++, byte = byte>>1) {
    /* AND bit a bit com maschera 00000001, isola bit meno significativo   */
    bits[l+i] = byte & 0x01;
  }
}

/* riconosce i bit dal meno significativo e li accumula nel
   vettore di char (0/1) a partire dalla casella l;
   variante che non sposta i bit in "byte", ma li "guarda" usando un filtro:
   una maschera di bit da mettere in AND per evidenziare il bit scelto */
void separaBit3(unsigned char byte, char *bits, int l) {
  int i;
  unsigned char mask;
  /* divide byte per 2 mediante shift di 1 posizione a destra */
  for (i=0,mask=0x01; i<8; i++, mask=mask<<1) {
    /* AND bit a bit com maschera, isola bit selezionato */
    bits[l+i] = byte & mask ? 1 : 0;
  }
}


int nBitEsponente(int size) {
  switch (size) {
  case 4: return 8;   /* float */
  case 8: return 11;  /* double */
  default: return 15; /* long double */
  }
  return 0; /* errore */
}

int dimensioneConPadding (int size, int bigEndian) {
  /* se long double e little endian */
  /* verifica eventuale padding (allineamento) e diminuisce size */
  if (size>8 && !bigEndian) {
    int size1;
    /* mette in a e b due numeri che differiscano solo nel segno */
    long double a = 1.0, b = -a;
    unsigned char *pa=(unsigned char *)&a, *pb=(unsigned char *)&b; /* puntatori ai byte di a e b */
    /* assume padding a indirizzi alti e cerca byte con bit di segno */
    for (size1=0; size1<size && pa[size1]==pb[size1]; size1++);
    if (size1<size) {
      printf("Padding di %d byte\n", size-size1-1);
      size = size1+1;
      printf("Dimensioni tenendo conto del padding: %d\n", size);
    }
  }
  return size;
}

void stampaCodifica1 (void *p, int size, int bigEndian) {
  int i, nExpBits, nBits;
  unsigned char *pchar = p;
  char bits[128]; /* non serve unsigned perche puo' valere solo 0/1 */

  size = dimensioneConPadding (size, bigEndian);

  /* scarica su bits i bit dal meno significativo */
  for (i=0; i<size; i++) {
    separaBit(pchar[i], bits, i*8);
  }

  int j;
      for(i=0;i<size;i++)
        for(j=0;j<8;j++)
            printf("%d",bits[i*8+j]);

  nBits = size*8;
  nExpBits = nBitEsponente(size);

  printf("\nbit di segno : %d\n", (int)bits[nBits-1]);
  printf("esponente    : ");
  for (i=nBits-2; i>nBits-2-nExpBits; i--)
    printf("%d", (int)bits[i]);
  printf("\nmantissa     : ");
  for (i=nBits-2-nExpBits; i>=0; i--)
    printf("%d", (int)bits[i]);
  printf("\n");

}

int estraiBit(unsigned char *bytes, int iBit) {
  int iByte = iBit/8; /* indice di byte = indice di bit/8 */

  unsigned char mask = 0x01 << (iBit%8); /* metti 1 nella posizione desiderata nel byte */
  int bit = ((bytes[iByte] & mask) == 0) ? 0 : 1;

  return bit;
}

/* variante che non usa il vettore di bit come appoggio */
void stampaCodifica2 (void *p, int size, int bigEndian) {
  int i, nExpBits, nBits;
  unsigned char *pchar = p;

  size = dimensioneConPadding (size, bigEndian);

  nBits = size*8;
  nExpBits = nBitEsponente(size);

  printf("bit di segno : %d\n", estraiBit(pchar,nBits-1));
  printf("esponente    : ");
  for (i=nBits-2; i>nBits-2-nExpBits; i--)
    printf("%d", estraiBit(pchar,i));
  printf("\nmantissa     : ");
  for (i=nBits-2-nExpBits; i>=0; i--)
    printf("%d", estraiBit(pchar,i));
  printf("\n");

}
