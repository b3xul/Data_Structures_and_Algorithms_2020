#include <stdio.h>
#include <stdlib.h>
#define N 8

int main()
{
    int matrix[N][N];
    int i=0,j=0,k=1,l=0;

    while(l<N/2){
    i=l;
    for(j=0+l;j<N-l;j++){
            matrix[i][j]=k;
            k++;
        }
    j--;

    for(i=1+l;i<N-l;i++){
            matrix[i][j]=k;
            k++;
        }
    i--;

    for(j=N-2-l;j>=0+l;j--){
            matrix[i][j]=k;
            k++;
    }
    j++;

    for(i=N-2-l;i>0+l;i--){
            matrix[i][j]=k;
            k++;
    }

    if(i==l&&j==l){
        k=1;
        l++;
    }
    }
    printf("La tua magica matrice e':\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("\t%d",matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
