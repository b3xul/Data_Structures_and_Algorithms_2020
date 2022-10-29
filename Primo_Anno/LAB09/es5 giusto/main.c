#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{
    float quota [N][N]={{0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1},
                        {0.1,0.2,0.2,0.2,0.2,0.2,0.3,0.3,0.3,0.1},
                        {0.1,0.2,0.3,0.3,0.4,0.5,0.5,0.5,0.5,0.1},
                        {0.1,0.2,0.3,0.3,0.5,0.5,0.5,0.7,0.7,0.1},
                        {0.1,0.2,0.4,0.4,0.5,0.7,0.7,0.8,0.7,0.1},
                        {0.1,0.2,0.4,0.4,0.5,0.7,0.8,0.9,0.8,0.1},
                        {0.1,0.2,0.4,0.4,0.5,0.7,0.8,0.9,1.4,0.1},
                        {0.1,0.2,0.4,0.4,0.5,0.7,0.8,0.9,1.2,0.1},
                        {0.1,0.2,0.4,0.4,0.5,0.7,0.8,0.9,1.1,0.1},
                        {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1}};
    int x0,y0;
    printf("Inserisci la posizione di partenza del topo: ");
    scanf("%d%d",&x0,&y0);
    x0--;
    y0--;

    int flag=1;
    int i,j;
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
