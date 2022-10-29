#include <stdio.h>
#include <stdlib.h>
#define MAXD 30

int leggi(int v[]);
int mediaMobile(int V[], int n, int k, float M[]);

int main()
{
    int v[MAXD]={0};
    int i,n,k,tot;
    float M[MAXD];

    printf("Inserisci vettore di interi (max 30), zero per terminare: ");
    n=leggi(v);

    printf("Inserisci ampiezza della finestra: ");
    scanf("%d",&k);

    tot=mediaMobile(v,n,k,M);

    printf("Ho calcolato %d medie, e il vettore risultante e': ",tot);
    for(i=0;i<tot;i++)
        printf("%.3f ",M[i]);

    return 0;
}

int mediaMobile(int V[], int n, int k, float M[]){
    int i,j;
    int parziale;

    for(i=0;i<=n-k;i++){
        parziale=0;
        for(j=i;j<i+k;j++){
            parziale=parziale+V[j];
        }
        M[i]=(float)parziale/k;
    }
    return i;
}

int leggi(int v[]){
    int i, fine=0;
    for (i=0;!fine&&i<MAXD;i++) {
        scanf("%d",&v[i]);
        if(v[i]==0){
            fine=1;
            i--; // trascura lo zero per finire
        }
    }
    return i;
}
