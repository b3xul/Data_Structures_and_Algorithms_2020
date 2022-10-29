#include <stdio.h>
#include <stdlib.h>
#define N 5

int main()
{
    int n=2,x,monotona;
    int v[N]={0};


        printf("Inserisci un numero intero: ");
        scanf("%d",&x);

        monotona=0;
        v[0]=x;

        printf("Inserisci un numero intero: ");
        scanf("%d",&x);
        v[1]=x;

    if(v[1]>v[0]){

    while(n<N&&monotona==0){

        printf("Inserisci un numero intero: ");
        scanf("%d",&x);

        if(x>v[n-1]){
            v[n]=x;
            n++;
        }
        else
            monotona=1;
        }
    }

    if(v[1]<v[0]){

    while(n<N&&monotona==0){

        printf("Inserisci un numero intero: ");
        scanf("%d",&x);

        if(x<v[n-1]){
            v[n]=x;
            n++;
        }
        else
            monotona=1;
        }
    }

    printf("Il vettore contiene: ");

    for(n=0;n<N;n++)
        printf("%d ",v[n]);

    return 0;
}
