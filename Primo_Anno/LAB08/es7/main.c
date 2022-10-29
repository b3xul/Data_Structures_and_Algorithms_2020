#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

int main()
{
    int m[N][N];
    int i,j;
    int primo=0;
    int secondo=0;
    int terzo=0;

    printf("Devi darmi ben 25 valori:\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d",&m[i][j]);
        }
    }

    for(i=0;i<N;i++){
            primo=0;
            secondo=0;
            terzo=0;
        for(j=0;j<N;j++){
            if(m[i][j]!=0){
                primo=0;
                secondo=0;
                terzo=0;
            }
            if(m[i][j]==0&&secondo){
                terzo=1;
            }
            if(m[i][j]==0&&primo){
                secondo=1;
            }
            if(m[i][j]==0){
                primo=1;
            }
            if(primo&&secondo&&terzo){
                printf("La sequenza compare nella riga %d\n",i+1);
                primo=0;
                secondo=0;
                terzo=0;
            }
        }
    }

    for(i=0;i<N;i++){
            primo=0;
            secondo=0;
            terzo=0;
        for(j=0;j<N;j++){
            if(m[j][i]!=0){
                primo=0;
                secondo=0;
                terzo=0;
            }
            if(m[j][j]==0&&secondo){
                terzo=1;
            }
            if(m[j][i]==0&&primo){
                secondo=1;
            }
            if(m[j][i]==0){
                primo=1;
            }
            if(primo&&secondo&&terzo){
                printf("La sequenza compare nella colonna %d\n",i+1);
                primo=0;
                secondo=0;
                terzo=0;
            }
        }
    }
    return 0;
}
