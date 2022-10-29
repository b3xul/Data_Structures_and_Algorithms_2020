#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

int main()
{
    FILE *f;
    char nome[2*N];
    float quota[N][N];
    printf("Inserisci il nome del file da aprire: ");
    scanf("%s",nome);

    f=fopen(nome,"r");
    if(f==NULL){
        printf("File non trovato!");
        return -1;
    }

    int i,j;
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j ++){
            fscanf(f, "%f", &quota[i][j]);
        }
    }
    fclose(f);


    int x0,y0;
    printf("Inserisci la posizione di partenza del topo: ");
    scanf("%d%d",&x0,&y0);
    x0--;
    y0--;

    int flag=1;
    int x,y;
    float max=quota[x0][y0];

    while(flag){
        for(i=x0-1;i<=x0+1;i++){
            for(j=y0-1;j<=y0+1;j++){
                if(i>=0&&j>=0&&i<N&&j<N){
                    if(quota[i][j]>max){
                        max=quota[i][j];
                        x=i;
                        y=j;
                    }
                }
            }
        }
        if(max>quota[x0][y0]){
            printf("Il topo si sposta in (%d,%d) a quota %f\n",x+1,y+1,quota[x][y]);
            x0=x;
            y0=y;
        }
        else{
            printf("Il topo si e' perso e non sa piu' dove andare, mannaggia!");
            flag=0;
        }
    }


    return 0;
}
