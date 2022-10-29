#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int completo(int [][9],int);

int main(int argc,char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"Errore nel numero di argomenti!\n");
        return -1;
    }

    FILE *fi;
    FILE *fo;

    if((fi=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file %s!\n",argv[1]);
        return -2;
    }
    if((fo=fopen("Risolto.txt","w"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file Risolto.txt!\n");
        return -3;
    }

    char sudoku[9][9];
    int provvisoria[9][10*9]={{0}};
    int risolto[9][9]={{0}};
    int i,j,k,l,m,n;
    int contarighe;
    int contacolonne;
    int trovato;
    int possibile;
    int posriga,poscolonna;

    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
                fscanf(fi,"%c%*c",&sudoku[i][j]);
                if(isdigit(sudoku[i][j])) risolto[i][j]=sudoku[i][j]-'0';
        }
    }

    do{
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){

                    if(risolto[i][j]==0){

                        if(i<3) contarighe=0;
                        else if(i<6&&i>=3) contarighe=1;
                        else if(i>=6) contarighe=2;

                        if(j<3) contacolonne=0;
                        else if(j<6&&j>=3) contacolonne=1;
                        else if(j>=6) contacolonne=2;

                        for(k=1;k<10;k++){
                            trovato=0;
                            for(l=contarighe*3;l<contarighe*3+3&&!trovato;l++){ //controllo il blocco//
                                for(m=contacolonne*3;m<contacolonne*3+3&&!trovato;m++){
                                    if(risolto[l][m]==k) trovato=1;
                                }
                            }

                            for(l=0;l<9&&!trovato;l++){
                                if(risolto[i][l]==k) trovato=1; //controllo la riga//

                                if(risolto[l][j]==k) trovato=1; //controllo la colonna//
                            }
                            if(!trovato){
                                for(l=j*9+1;l<j*9+1+10&&!trovato;l++){
                                    if(provvisoria[i][l]==0){
                                        provvisoria[i][j*9]--;
                                        provvisoria[i][l]=k;
                                        trovato=1;
                                    }
                                }
                            }
                        }
                        if(provvisoria[i][9*j]==-1){
                                risolto[i][j]=provvisoria[i][9*j+1];

                                for(l=0;l<81;l++){
                                    if(provvisoria[i][l]==risolto[i][j]){
                                            provvisoria [i][l]=0;
                                            provvisoria [i][(l/9)*9]++;
                                    }
                                }
                                for(l=0;l<9;l++){
                                    if(provvisoria[l][j]==risolto[i][j]){
                                            provvisoria [l][j]=0;
                                            provvisoria [l][(j/9)*9]++;
                                    }
                                }
                        }

                    }
            }
        }

        for(k=1;k<10;k++){
            for(i=0;i<9;i++){
                possibile=0;
                for(j=0;j<90&&possibile<2;j++){
                    if(provvisoria[i][j]==k){
                        possibile++;
                        posriga=i;
                        poscolonna=j;
                    }
                }
                if(possibile==1) risolto[posriga][poscolonna/9]=k;
            }
        }

        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                printf("%d ",risolto[i][j]);
            }
            printf("\n");
        }

        /*for(k=1;k<10;k++){
            for(n=0;n<9;n++){
                for(i=0;i<9;i++){
                    possibile=0;
                    for(j=9*n+1;j<9*n+1+10&&possibile<2;j++){
                        if(provvisoria[i][j]==k){
                            possibile++;
                            posriga=i;
                            poscolonna=j;
                        }
                    }
                }
                if(possibile==1) risolto[posriga][poscolonna/9]=k;
            }
        }
        for(i=0;i<9;i++){
            for(j=0;j<90;j++){
                provvisoria[i][j]=0;
            }
        }*/
    }
    while(completo(risolto,9)==0);

    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            fprintf(fo,"%d ",risolto[i][j]);
        }
        fprintf(fo,"\n");
    }

    fclose(fi);
    fclose(fo);
    return 0;
}

int completo(int risolto[][9],int m){
    int i,j;
    int res=1;

    for(i=0;i<9&&res;i++){
        for(j=0;j<9;j++){
            if(risolto[i][j]==0) res=0;
        }
    }

    return res;
}
