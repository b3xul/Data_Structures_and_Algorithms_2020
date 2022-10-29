#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

int main()
{
    char nome[N+1];
    char city[N+1];
    char partenza[N+1];
    char arrivo[N+1];
    FILE *treni;
    int numpart=0;
    int numarr=0;

    printf("Inserisci il nome del file ferroviario: ");
    scanf("%s",nome);

    treni=fopen(nome,"r");
    if(treni==NULL){
        printf("Il file non e' stato trovato");
        return -1;
    }

    printf("Inserisci il nome di una citta': ");
    scanf("%s",city);

    printf("In partenza sono presenti i seguenti treni:\n");
    while(fscanf(treni,"%s %s",partenza,arrivo)!=EOF){
        if(!strncmp(partenza,city,strlen(city))){
            printf("\t%s \t%s\n",partenza,arrivo);
            numpart++;
        }
    }
    fclose(treni);

    treni=fopen(nome,"r");
    printf("In arrivo sono presenti i seguenti treni:\n");

    while(fscanf(treni,"%s %s",partenza,arrivo)!=EOF){
        if(!strncmp(arrivo,city,strlen(city))){
            printf("\t%s \t%s\n",partenza,arrivo);
            numarr++;
        }
    }

    printf("Da %s partono %d treni e arrivano %d treni",city, numpart,numarr);


    fclose(treni);
    return 0;
}
