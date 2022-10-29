#include <stdio.h>
#include <stdlib.h>
#define N 4
int main()
{
    int v1[N];
    int v2[N];
    int nr1[N]={0};
    int nr2=-1;
    int i,j,uguali=1;

    printf("Inserisci dei valori nel primo: ");
    for(i=0;i<N;i++){
        scanf("%d",&v1[i]);
    }

    printf("Inserisci dei valori nel secondo: ");
    for(i=0;i<N;i++){
        scanf("%d",&v2[i]);
    }
    for(i=0;i<N;i++){

        for(j=0;j<N;j++){
                if(j!=i){
                    if(v1[i]==v1[j]){
                        nr1[i]++;
                    }
                }
        }
    }

    for(i=0;i<N&&uguali==1;i++){
        nr2=-1;
        for(j=0;j<N;j++){
            if(v1[i]==v2[j]){
                nr2++;
            }
        }
        if(nr2!=nr1[i]){
                uguali=0;
            }
    }


    if(uguali==1){
        printf("Tutti uguali");
    }
    else printf("Non tutti uguali");
    return 0;
}
