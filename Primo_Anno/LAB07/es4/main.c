#include <stdio.h>
#include <stdlib.h>
#define N 5

float avgVect(int [],int);
int upperLimit(int [],int,float);

int main()
{
    int v[N];
    int i;
    float Media;
    int Alti;

    printf("Inserisci dei valori: ");
    for(i=0;i<N;i++){
        scanf("%d",&v[i]);
    }

    Media=avgVect(v,N);
    Alti=upperLimit(v,N,Media);

    printf("%f\n",Media);
    printf("%d",Alti);

    return 0;
}

float avgVect(int v[],int n){
    float c=0;
    int i;

    for(i=0;i<n;i++){
        c=(float)v[i]+c;
    }
    c=c/n;

    return c;
}

int upperLimit(int v[],int n,float c){
    int i,d=0;
    for(i=0;i<n;i++){
        if(v[i]>c){
            d++;
        }
    }
    return d;
}
