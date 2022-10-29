#include <stdio.h>
#include <stdlib.h>
#define N 5

int main()
{
    int x,i,tripletta;
    int v[N]={0};

    printf("Inserisci numeri: ");

    for(i=0;i<N;i++){
        scanf("%d",&x);
        v[i]=x;
    }

    printf("Il vettore contiene: ");
    for(i=0;i<N;i++){
        printf("%d ",v[i]);
    }

    printf("\n");

    i=0;
    tripletta=0;

    while(i<N-1&&tripletta==0){

    if((v[i])==((v[i+1])-1)&&((v[i+1])-1)==((v[i+2])-2)){
        printf("E' presente una tripletta formata da %d %d %d in posizione %d", v[i], v[i+1], v[i+2],i+1);
        tripletta=1;
    }

    else{
        printf("Non ci sono triplette");
        tripletta=1;
    }

    }
    return 0;
}
