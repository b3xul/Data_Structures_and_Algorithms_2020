#include <stdio.h>
#include <stdlib.h>
#define RIGHE 10
#define COLONNE 7

int main(int argc,char *argv[])
{
    if(argc!=3){
        fprintf(stderr,"Errore nel numero di argomnti!\n");
        return -1;
    }

    FILE *fim;
    FILE *fker;
    FILE *fout;

    if((fim=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"Errore nel'apertura del file %s!\n",argv[1]);
        return -2;
    }

    if((fker=fopen(argv[2],"r"))==NULL){
        fprintf(stderr,"Errore nel'apertura del file %s!\n",argv[2]);
        return -3;
    }

    if((fout=fopen("risultato.txt","w"))==NULL){
        fprintf(stderr,"Errore nel'apertura del file risultato.txt\n");
        return -4;
    }

    int immagine[RIGHE][COLONNE];
    int kernel[3][3];
    int i,j,k,t,v,z;
    int filtrata[RIGHE][COLONNE];

    for(i=0;i<RIGHE;i++){
        for(j=0;j<COLONNE;j++){
            fscanf(fim,"%d",&immagine[i][j]);
            filtrata[i][j]=0;
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            fscanf(fker,"%d",&kernel[i][j]);
        }
    }


    for(i=0;i<RIGHE;i++){
        for(j=0;j<COLONNE;j++){
            for(k=0,v=i-1;k<3&&v<i+2;k++,v++){
                for(t=0,z=j-1;t<3&&z<j+2;t++,z++){
                    if(v<0||v>RIGHE||z<0||z>COLONNE){
                        immagine[v][z]=0;
                    }
                    filtrata[i][j]+=immagine[v][z]*kernel[k][t];
                }
            }
        }
    }


    for(i=0;i<RIGHE;i++){
        for(j=0;j<COLONNE;j++){
            fprintf(fout,"%d ",filtrata[i][j]);
        }
        fprintf(fout,"\n");
    }
    fclose(fim);
    fclose(fker);
    fclose(fout);

    return 0;
}
