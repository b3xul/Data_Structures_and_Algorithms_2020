#include <stdio.h>
#include <stdlib.h>
#define N 5

float over_Avg(int [],int,int *);

int main()
{
    int v[N];
    int i;
    int superiori=0;
    float media;

    printf("Inserisci dei valori: ");
    for(i=0;i<N;i++){
        scanf("%d",&v[i]);
    }

    media=over_Avg(v,N,&superiori);

    printf("La media dei valori da te inseriti e' %f\n",media);
    printf("%d numeri sono sopra la media",superiori);

    return 0;
}

float over_Avg(int v[],int n,int *superiori){
    int i;
    float c=0;
    int d=0;

    for(i=0;i<n;i++){
        c=(float)v[i]+c;
        }
    c=c/n;
    for(i=0;i<n;i++){
        if(v[i]>c){
                d++;
            }
    }
    *superiori=d;

    return c;
}
