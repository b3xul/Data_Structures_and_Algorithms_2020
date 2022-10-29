#include <stdio.h>
#include <stdlib.h>
#define N 5
int main()
{
    int i,tot=0;
    float media;

    int v[N]={0};

    printf("Inserisci 5 numeri interi: ");

    for(i=0;i<N;i++){
    scanf("%d",&v[i]);
    }

    int max=v[0];
    int posizione[N]={0};

    for(i=0;i<N;i++){
    printf("%d ",v[i]);
    }
    printf("\n");

    for(i=0;i<N;i++){
            tot=tot+v[i];
    }
    media=(float)tot/N;
    printf("La media vale: %f\n",media);

    for(i=1;i<N;i++){
        if(v[i]>max){
            max=v[i];
        }
    }
    printf("Il massimo vale: %d\n",max);

    for(i=0;i<N;i++){

        if(v[i]==max){
        posizione[i]=i;
        }

    }
    printf("Il massimo si trova nelle seguenti posizioni:\n");
    for(i=0;i<N;i++){
        printf("%d ",posizione[i]);
    }
    return 0;
}
