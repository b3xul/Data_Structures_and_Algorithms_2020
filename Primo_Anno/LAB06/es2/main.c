#include <stdio.h>
#include <stdlib.h>
#define N 4

int main()
{
    int i,j,uguale;

    int v1[N]={0};
    int v2[N]={0};

    printf("Scrivimi qualche numero: ");

    for(i=0;i<N;i++)
    scanf("%d",&v1[i]);

    printf("Scrivimi qualche altro numero: ");

    for(i=0;i<N;i++)
    scanf("%d",&v2[i]);

    uguale=1;
    for(i=0;i<N&&uguale==1;i++){
        uguale=0;
        for(j=0;j<N&&uguale==0;j++){
            if(v1[i]==v2[j]){
                uguale=1;
            }
        }
    }


    if(uguale==1){
        printf("Sono gli stessi numeri!");
    }
    else{
        printf("Sono diversi!");
    }

    return 0;
}
