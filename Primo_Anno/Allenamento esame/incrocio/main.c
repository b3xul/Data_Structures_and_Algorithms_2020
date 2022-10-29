#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
            char ta1[7+1];
            char te1[5+1];

            char ta2[7+1];
            char te2[5+1];

            char ta3[7+1];
            char te3[5+1];
} attimo;

int main(int argc, char *argv[])
{
    if(argc!=3){fprintf(stderr,"Errore nel numero di argomenti!\n");
        return -1;}

    FILE *f1;
    FILE *f2;

    if((f1=fopen(argv[1],"r"))==NULL){
            fprintf(stderr,"Errore nell'apertura del file %s!\n",argv[1]);
            return -2;
    }
    if((f2=fopen(argv[2],"w"))==NULL){
            fprintf(stderr,"Errore nell'apertura del file %s!\n",argv[2]);
            return -3;
    }
    attimo fermata[100];
    int i,j=0,k=0,p=0;
    int n=0;
    int coda;
    int strada1=1,strada2=1,strada3=1;
    while((fscanf(f1,"%s%s%s%s%s%s",fermata[n].ta1,fermata[n].te1,fermata[n].ta2,fermata[n].te2,fermata[n].ta3,fermata[n].te3))!=EOF){
        n++;
    }
    coda=n;

    for(i=0;i<coda*3;i++){
        if(j==coda) strada1=0;
        if(k==coda) strada2=0;
        if(p==coda) strada3=0;

        if(strcmp(fermata[j].te1,fermata[k].te2)>0){
                if(strcmp(fermata[k].te2,fermata[p].te3)>0&&strada3){
                        fprintf(f2,"%s\n",fermata[p].ta3);
                        p++;
                }
                else if(strada2){
                    fprintf(f2,"%s\n",fermata[k].ta2);
                    k++;
                }
                else{
                    fprintf(f2,"%s\n",fermata[j].ta1);
                    j++;
                }
        }

        else{
                if(strcmp(fermata[j].te1,fermata[p].te3)>0&&strada3){
                    fprintf(f2,"%s\n",fermata[p].ta3);
                    p++;
                }
                else if(strada1){
                    fprintf(f2,"%s\n",fermata[j].ta1);
                    j++;
                }
                else{
                    fprintf(f2,"%s\n",fermata[k].ta2);
                    k++;
                }
        }

    }

    fclose(f1);
    fclose(f2);
    return 0;
}
