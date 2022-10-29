#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int matrix[5][5];
    int i,j,k;
    int flag=1;
    int value;
    int length;

    if(argc!=4){
        fprintf(stderr,"Si e' verificato un errore nel numero di argomenti inseriti.\n");
        return -1;
    }

    fp=fopen(argv[1],"r");
    if(fp==NULL){
        fprintf(stderr,"File non trovato.\n");
        return -1;
    }

    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            fscanf(fp,"%d",&matrix[i][j]);
        }
    }

    value=atoi(argv[3]);
    length=atoi(argv[2]);
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(matrix[i][j]==value){
                flag=1;
                for(k=1;k<length&&flag==1;k++){
                    if(j+k<6){
                        if(matrix[i][j+k]!=value){
                            flag=0;
                        }
                    }
                    else flag=0;
                }
                if(flag){
                    printf("La sequenza compare nella riga %d\n",i+1);
                    flag=0;
                }
                flag=1;
                for(k=1;k<length&&flag==1;k++){
                    if(i+k<6){
                        if(matrix[i+k][j]!=value){
                            flag=0;
                        }
                    }
                    else flag=0;
                }
                if(flag){
                    printf("La sequenza compare nella colonna %d\n",j+1);
                    flag=0;
                }
            }
        }
    }
    fclose(fp);
    return 0;
}
