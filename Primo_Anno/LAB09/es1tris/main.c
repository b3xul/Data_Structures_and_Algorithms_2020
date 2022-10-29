#include <stdio.h>
#include <stdlib.h>
#define N 5
#define LENGTH 11

int main()
{
    FILE* f;
    int i,j=0;
    int percorso=1;int uscita=0;int trovato=0;
    char palude[N][LENGTH];
    int strada[LENGTH]={0};

    f=fopen("mappa.txt","r");
    if(f==NULL){
        printf("File non trovato!");
        return -1;
    }

    while(!feof(f)){
    for(i=0;i<N;i++){
            fscanf(f,"%s",&palude[i][0]);
        }
    }
    while(!feof(f)){
    for(i=0;i<N;i++){
        for(j=0;j<LENGTH;j++){
            fprintf(f,"%c",palude[i][j]);
        }
        printf("\n");
    }
    }

    i=0;j=0;
    while(i<N){
        if(palude[i][0]=='*'){
            j=0;
            strada[j]=i;
            percorso=1;
        }
        while(j<LENGTH&&percorso&&!uscita){

            if(i!=0&&palude[i-1][j+1]=='*'){
                strada[j+1]=i-1;
                trovato=1;
                i=i-1;
            }
            if(palude[i][j+1]=='*'){
                strada[j+1]=i;
                trovato=1;
            }
            if(i!=N&&palude[i+1][j+1]=='*'){
                strada[j+1]=i+1;
                trovato=1;
                i=i+1;
            }
            if(j==LENGTH-1&&percorso){
                uscita=1;
            }
            if(trovato==0){
                percorso=0;
            }
            j++;
            trovato=0;
        }
    i++;
    }
    if(!uscita){
        printf("Non vi e' alcun percorso.");
    }
    else{
        for(i=0;i<LENGTH;i++)
        printf("%d ",strada[i]);
    }

    fclose(f);
    return 0;
}
