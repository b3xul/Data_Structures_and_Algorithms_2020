#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Nota bene: in questo caso potresti usare un vettore di struct in modo da sfruttare la presenza della struct, così posso passare la struct alla funzione che la richiama tutta insieme invece di campo per campo, ma devo ricordarmi di usare l'* perche' e' un vettore!//
struct coordinate{
        int x[4];
        int y[4];
};
typedef struct coordinate punto;

float distanza(int, int, int, int);

int main(int argc, char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"Errore nel numero di argomenti.\n");
        return -1;
    }

    int i;
    punto p;
    float d[4];
    float lunghezza=0;
    float min;

    for(i=0;i<4;i++){
        printf("Inserisci le coordinate del punto %d: \n",i+1);
        scanf("%d%d",&p.x[i],&p.y[i]);
    }

    for(i=0;i<3;i++){
    d[i]=distanza(p.x[i],p.x[i+1],p.y[i],p.y[i+1]);
    }
    d[i]=distanza(p.x[i],p.x[0],p.y[i],p.y[0]);

    if(strcmp(argv[1],"-m")==0){
        for(i=0;i<4;i++){
            lunghezza=d[i]+lunghezza;
        }
        printf("Il percorso da te scelto e' lungo %f\n",lunghezza);
    }
    if(strcmp(argv[1],"-a")==0){
        min=d[0];
        for(i=1;i<4;i++){
            if(d[i]<min){
                min=d[i];
            }
        }
        printf("La minima distanza tra i punti scelti e' %f\n",min);
    }
    return 0;
}

float distanza(int x1, int x2, int y1, int y2){
    int ascissa;
    int ordinata;
    float res;

    ascissa=x1-x2;
    ordinata=y1-y2;
    res=(float)sqrt(ascissa*ascissa+ordinata*ordinata);
    return res;
}
