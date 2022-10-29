#include <stdio.h>
#include <stdlib.h>
#define N 5

void mult(int [],int,int); //[]=indirizzo vettore

int main()
{
    int v[N],x,i;

    printf("Inserisci N valori: ");
    for(i=0;i<N;i++){
        scanf("%d",&v[i]);
    }
    printf("\n");

    printf("Il vettore vale: ");
    for(i=0;i<N;i++){
        printf("%d ",v[i]);
    }
    printf("\n");

    printf("Ora dammi una x: ");
    scanf("%d",&x);

    printf("\n");

    mult(v,N,x);

    printf("Il nuovo vettore vale: ");
    for(i=0;i<N;i++){
        printf("%d ",v[i]);
    }

    return 0;
}

void mult(int v[],int n,int x){
    int i;
    for(i=0;i<n;i++){
        v[i]=x*v[i];
    }
    return;
}
