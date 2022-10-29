#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

typedef struct stazione{
            char partenza[N+1];
            char arrivo[N+1];
            }stazione;

int main(int argc,char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"Errore nel numero di argomenti!");
        return -1;
    }

    FILE *treni;
    treni=fopen(argv[1],"r");
    if(treni==NULL){
        printf("Il file non e' stato trovato");
        return -2;
    }

    char city[N+1];
    stazione fermate;
    int numpart=0;
    int numarr=0;

    printf("Inserisci il nome di una citta': ");
    scanf("%s",city);

    printf("In partenza sono presenti i seguenti treni:\n");
    while(fscanf(treni,"%s%s",fermate.partenza,fermate.arrivo)!=EOF){
        if(!strncmp(fermate.partenza,city,strlen(city))){
            printf("\t%s \t%s\n",fermate.partenza,fermate.arrivo);
            numpart++;
        }
    }
    fclose(treni);

    treni=fopen(argv[1],"r");
    printf("In arrivo sono presenti i seguenti treni:\n");

    while(fscanf(treni,"%s%s",fermate.partenza,fermate.arrivo)!=EOF){
        if(!strncmp(fermate.arrivo,city,strlen(city))){
            printf("\t%s \t%s\n",fermate.partenza,fermate.arrivo);
            numarr++;
        }
    }

    printf("Da %s partono %d treni e arrivano %d treni",city, numpart,numarr);


    fclose(treni);
    return 0;
}
