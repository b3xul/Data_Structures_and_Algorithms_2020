#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 6

int main()
{
    int v[N];
    int i,j,x;

    for(i=0;i<N;i++){
        v[i]=INT_MAX;
    }

    printf("Inserisci una serie di 6 valori: ");


    for(i=0;i<N;i++){
        scanf("%d",&x);
        for(j=N-2;j>=0;j--){
            if(x<v[j]){

                        v[j+1]=v[j];
                        v[j]=x;

                }
            else {
                v[j+1]=x;
                }
        }
        }



    for(i=0;i<N;i++){
        printf("%d ",v[i]);
    }

    return 0;
}
