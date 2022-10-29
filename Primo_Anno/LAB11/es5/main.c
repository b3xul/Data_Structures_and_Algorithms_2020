#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct results{
                char nomi[20+1];
                char cognomi[20+1];
                float punteggi;
}results;

int main()
{
    FILE *f1;
    FILE *f2;

    f1=fopen("gara.txt","r");
    if(f1==NULL){
        fprintf(stderr,"Errore nell'apertura del primo file.\n");
        return -1;
    }

    f2=fopen("garaord.txt","w");
    if(f2==NULL){
        fprintf(stderr,"Errore nell'apertura del secondo file.\n");
        return -2;
    }

    results tabella;
    results alfa[100];
    int i=0,j,length,n=0;
    results best[3];

    for(i=0;i<100;i++){
        strcpy(alfa[i].cognomi,"\0");
    }
    fscanf(f1,"%s%s%f",alfa[0].nomi,alfa[0].cognomi,&alfa[0].punteggi);
    while(fscanf(f1,"%s%s%f",tabella.nomi,tabella.cognomi,&tabella.punteggi)!=EOF){
      for(i=n;i>=0;i--){
            if(strcmp(alfa[i].cognomi,tabella.cognomi)>0){
                strcpy(alfa[i+1].cognomi,alfa[i].cognomi);
                strcpy(alfa[i].cognomi,tabella.cognomi);

                strcpy(alfa[i+1].nomi,alfa[i].nomi);
                strcpy(alfa[i].nomi,tabella.nomi);

                alfa[i+1].punteggi=alfa[i].punteggi;
                alfa[i].punteggi=tabella.punteggi;
            }
            else{
                strcpy(alfa[i+1].cognomi,tabella.cognomi);
                strcpy(alfa[i+1].nomi,tabella.nomi);
                alfa[i+1].punteggi=tabella.punteggi;
                break;
            }
      }
        n++;
    }
    length=n;

    for(i=0;i<=length;i++){
        printf("%s %s %.1f\n",alfa[i].nomi,alfa[i].cognomi,alfa[i].punteggi);
        fprintf(f2,"%s %s %.1f\n",alfa[i].nomi,alfa[i].cognomi,alfa[i].punteggi);
    }


    for(i=0;i<3;i++) best[i].punteggi=0;


    for(i=0;i<3;i++){
        for(j=0;j<=length;j++){
            if(alfa[j].punteggi>best[i].punteggi&&strcmp(best[0].cognomi,alfa[j].cognomi)!=0&&strcmp(best[1].cognomi,alfa[j].cognomi)!=0){
                best[i].punteggi=alfa[j].punteggi;
                strcpy(best[i].nomi,alfa[j].nomi);
                strcpy(best[i].cognomi,alfa[j].cognomi);
            }
        }
    }

    printf("\nI primi tre classificati sono:\n");

    for(i=0;i<3;i++){
        printf("%s %s con %.1f punti di media\n",best[i].nomi,best[i].cognomi,best[i].punteggi);
    }

    fclose(f1);
    fclose(f2);
    return 0;
}
