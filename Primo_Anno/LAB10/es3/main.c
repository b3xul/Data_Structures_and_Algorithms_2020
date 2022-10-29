#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float distanza(int,int,int,int);

int main(int argc,char* argv[])
{
    if(argc!=2){
        printf("Errore nel numero di argomenti!\n");
        return -1;
    }
    int v1[4]; //ascisse//
    int v2[4]; //ordinate//
    float v3[4]; //distanze//
    float lunghezza=0;
    float min;
    int i;

    for(i=0;i<4;i++){
    printf("Inserisci le coordinate del punto %d: ",i+1);
    scanf("%d%d",&v1[i],&v2[i]);
    printf("\n");
    }

    for(i=0;i<3;i++){
    v3[i]=distanza(v1[i],v1[i+1],v2[i],v2[i+1]);
    }
    v3[i]=distanza(v1[i],v1[0],v2[i],v2[0]);

    if(strcmp(argv[1],"-m")==0){
        for(i=0;i<4;i++){
            lunghezza=v3[i]+lunghezza;
        }
        printf("Il percorso da te scelto e' lungo %f\n",lunghezza);
    }
    if(strcmp(argv[1],"-a")==0){
        min=v3[0];
        for(i=1;i<4;i++){
            if(v3[i]<min){
                min=v3[i];
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

