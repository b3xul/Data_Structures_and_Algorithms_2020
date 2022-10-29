#include <stdio.h>
#include <stdlib.h>
#define N 5

int main()
{
    int x,i,n1=0,n2=0;
    int v1[N]={0};
    int v2[N]={0};

    while(n1<N&&n2<N){
    printf("Inserisci un numero: ");
    scanf("%d",&x);



    if(x>0||(x<0&&x%3==0)){

        v1[n1]=x;
        n1++;

    }
    else if(x<0&&x%3!=0&&x%2!=0){

        v2[n2]=x;
        n2++;

    }
    }

    printf("v1 contiene: ");
    for(i=0;i<N;i++){
        printf("%d ",v1[i]);
    }
    printf("\n");

    printf("v2 contiene: ");
    for(i=0;i<N;i++){
        printf("%d ",v2[i]);
    }
    return 0;
}
