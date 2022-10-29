#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

int main()
{
    int m[N][N];
    int i,j;
    int val,length;
    int count=0;
    int trovata=0;
    int ecc=0;

    printf("Devi darmi ben 25 valori:\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d",&m[i][j]);
        }
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("\t%d ",m[i][j]);
        }
        printf("\n");
    }

    printf("Ora dammi un valore da cercare e quante volte lo vuoi: \n");
    scanf("%d%d",&val,&length);

    for(i=0;i<N;i++){
            trovata=0;
            count=0;
        for(j=0;j<N&&!trovata;j++){
            if(m[i][j]==val){
                count++;
            }
            if(count==length){
                trovata=1;
                printf("La sequenza compare nella riga %d\n",i+1);
                ecc++;
            }
            if(m[i][j]!=val){
                count=0;
            }
        }
    }

    for(i=0;i<N;i++){
            trovata=0;
            count=0;
        for(j=0;j<N&&!trovata;j++){
            if(m[j][i]==val){
                count++;
            }
            if(count==length){
                trovata=1;
                printf("La sequenza compare nella colonna %d\n",i+1);
                ecc++;
            }
            if(m[j][i]!=val){
                count=0;
            }
        }
    }
    if(ecc==0){
        printf("Sequenza non trovata..");
    }
    return 0;
}
