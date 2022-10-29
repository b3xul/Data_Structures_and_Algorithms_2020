#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{


    int percorso[100][2]={{0,0}};
    int x0,y0;

    printf("Inserisci una posizione di partenza del topolino: ");
    scanf("%d,%d",&x0,&y0);


    percorso[0][0]=x0;
    percorso[0][1]=y0;
    int flag=1;
    float max=quota[x0][y0];
    int i=0;
    int j=0;
    int k=1;
    int len;

    if(x0>0){
        x0=x0-1;
        i=x0-1;
    }
    if(y0>0){
        y0=y0-1;
        j=y0-1;
    }
    /*while(flag){
        for(i=percorso[0][0]-1,j=percorso[0][1]-1,k=1,l=0;i<percorso[0][0]+2,j<percorso[0][1]+2;i++,j++,k++,l++){
            if(quota[i][j]>quota[percorso[0][0]][percorso[0][1]]){
                max=quota[i][j];
                percorso[k][l]=i;
                percorso[k][l]=j;

            }


            else flag=0;

        }
    }

    while(flag){
        if(quota[i][j]>max)
            max=quota[i][j];

        if((x0==0&&i==1&&j==1)||(i==x0+1&&j==y0+1&&max==quota[x0][y0])){
            flag=0;
        }
        else if((x0==0&&i==1&&j==1)||(i==x0+1&&j==y0+1&&max>quota[x0][y0])){
            percorso[k][0]=x0;
            percorso[k][1]=y0;
            k++;
            x0=i;
            y0=j;
            i=x0-1;
            j=y0-2;
        }
        if(j==y0+1&&i<x0+2&&x0!=0){
            i++;
            j=j-2;
        }
        else if(j<y0+1) j++;
    }
    len=k;
    k=0;
    printf("Il topolino fa il seguente percorso:\n");
    while(k<=len){
        printf("(%d,%d)\n",percorso[k][0],percorso[k][1]);
        k++;
    }
    */
    return 0;
}
