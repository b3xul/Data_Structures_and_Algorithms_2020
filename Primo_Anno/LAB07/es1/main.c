#include <stdio.h>
#include <stdlib.h>
#define N 5

float power(int,int);

int main()
{
    int vbase[N];
    int vexp[N];
    float vres[N];
    int i;

    printf("Inserisci i valori delle basi: ");
    for(i=0;i<N;i++){
        scanf("%d",&vbase[i]);
    }
    printf("Inserisci i valori degli esponenti: ");
    for(i=0;i<N;i++){
        scanf("%d",&vexp[i]);
    }

    for(i=0;i<N;i++){
        vres[i]= power(vbase[i],vexp[i]);
    }
    printf("Il vettore risultante e': ");
    for(i=0;i<N;i++){

            printf("%f ",vres[i]);
    }
    return 0;
}

float power(int a,int b){ //a e b parametri formali//
    float R=1.0;
    int i;

    for(i=1;i<=b;i++){
        R=R*a;
        }
    if(b<0){
        for(i=1;i<=-b;i++){
        R=R*a;
        }
        R=(float)1/R;
    }


    return R;
}
