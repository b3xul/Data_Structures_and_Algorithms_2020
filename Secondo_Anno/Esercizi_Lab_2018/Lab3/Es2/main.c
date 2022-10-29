#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int checkBigEndian(void);
void stampaMemoria(void* var, int size, int bigEndian);
int nBitEsponente(int size);
void stampaCodifica(void* var, int size, int bigEndian);
int* separa(unsigned char byte);

int main()
{
    float af;
    double ad;
    long double ald;
    int float_size;
    int double_size;
    int long_double_size;

    int bigEndian=checkBigEndian();
    printf("Il sistema e' %sEndian\n",(bigEndian)?"Big":"Little");

    float_size=sizeof(af);
    double_size=sizeof(ad);
    long_double_size=sizeof(ald);

    printf("Dimensione float=%d bytes (%d bit)\n",float_size,float_size*8);
    printf("Dimensione double=%d bytes (%d bit)\n",double_size,double_size*8);
    printf("Dimensione long double=%d bytes (%d bit)\n",long_double_size,long_double_size*8);

    printf("Inserire un numero reale: ");
    scanf("%f",&af);
    ad=(double)af;
    ald=(long double)af;


    printf("af: %f \n",af);
    printf("ad: %lf \n",ad);
    printf("ald: %Lf \n",ald);

    printf("Stampa della codifica float:\n");
    stampaMemoria(&af,float_size,bigEndian);
    stampaCodifica(&af,float_size,bigEndian);

    printf("\nStampa della codifica double:\n");
    stampaMemoria(&ad,double_size,bigEndian);
    stampaCodifica(&ad,double_size,bigEndian);

    printf("\nStampa della codifica long double:\n");
    stampaMemoria(&ald,long_double_size,bigEndian);
    stampaCodifica(&ald,long_double_size,bigEndian);

    /*void* var=(long double*)&ald;
    int var_size=sizeof(*var);
    long double coso=*((long double*)(var));
    printf("Contenuto var=%Lf,Dimensione var:MAIN=%d bytes\n",coso,var_size);*/

    return 0;
}

int checkBigEndian(void){
    int n=42;
    int int_size=sizeof(n);
    int i;

    printf("Dimensione int=%d bytes\n",int_size);
    unsigned char* c=(unsigned char*)&n;

    printf("Indirizzo:contenuto (contenuto in hex)\n");
    for(i=0 ; i<int_size ; i++,c++)      /*Per riuscire a sfruttare l'aritmetica dei puntatori devo usare char* (sizeof(char)=1 per cui n_p+1=n_p+1 effettivamente)*/
        printf("%p:%d (%02x)\n",c,*c,*c);

    /*  BigEndian=MSB sull'indirizzo più basso
        LittleEndian=LSB sull'indirizzo più basso->basta fare un intero di un solo Byte e vedere se il byte a indirizzo minore contiene zero:
        se contiene zero allora è BigEndian, altrimenti è LittleEndian*/
    c=(unsigned char*)&n;
    /*return ((*c)==0)?1:0;*/
    return (*c==0);
}

void stampaMemoria(void* var, int size, int bigEndian){
    int i,j;
    unsigned char* c=(unsigned char*)var;

    printf("Indirizzo:contenuto (contenuto in hex)\n");
    for(i=0 ; i<size ; i++)
        printf("%p:%d (%02x)\n",&(c[i]),c[i],c[i]);       /*Notazione vettoriale standard! Non serve *(c[i])!*/

    printf("Stampo i byte dal piu' significativo (sinistra) al meno significativo (destra):\n");
    for(i=0 ; i<size ; i++){
        if(!bigEndian)
            j=size-i-1;       /*Se bigEndian invertire ordine dei bytes (stampo da sinistra a destra da più significativo a meno)*/
        printf("%02x",*(c+j));
    }
    printf("\n");
}

int nBitEsponente(int size) {
  switch (size) {
      case 4: return 8;   /* float */
      case 8: return 11;  /* double */
      default: return 15; /* long double */
  }
  return -1; /* errore */
}

void stampaCodifica(void* var, int size, int bigEndian){
    int i,j,k;
    int** bits;  /*Vettore di size vettori contenenti i numeri binari corrispondenti ai size bytes*/
    unsigned char* c=(unsigned char*)var;

    bits=(int**)malloc(size*sizeof(int*));  /*size puntatori a interi (size vettori di interi)*/

    for(i=0,j=0,k=0 ; i<size&&k<size ; i++,j++){
        if(!bigEndian)
            j=size-i-1;       /*Se bigEndian invertire ordine dei bytes (stampo da sinistra a destra da più significativo a meno)*/
        bits[k++]=separa(*(c+j));    /*Ogni vettore di interi contiene 8 interi (0 o 1)=byte corrispondente*/
    }
    for(i=0;i<size;i++)
        for(j=0;j<8;j++)
            printf("%d",bits[i][j]);

    printf("\n----\nbit di segno : %d\n", bits[0][0]);
    printf("esponente    : ");
    /*for(i=0;i<nBitEsponente(size);i++){
        printf("%d",**(bits+i));
    }*/
    for(k=0;k<nBitEsponente(size)+1;k++){
        printf("%d",bits[k/8][k%8]);
    }
    printf("\nmantissa     : ");
    for(k=nBitEsponente(size);k<size*8;k++){
        printf("%d",bits[k/8][k%8]);
    }
    printf("\n");
}

int* separa(unsigned char byte){
    int i;
    int* bits=(int*)malloc(8*sizeof(int));

    for (i=0; i<8; i++, byte /= 2) {
        bits[i] = byte%2; /* pari: 0, dispari: 1 */
    }

    return bits;
}
void separaBit2(unsigned char byte, char *bits, int l) {
  int i;

  /* divide byte per 2 mediante shift di 1 posizione a destra */
  for (i=0; i<8; i++, byte = byte>>1) {
    /* AND bit a bit com maschera 00000001, isola bit meno significativo   */
    bits[l+i] = byte & 0x01;
  }
}
