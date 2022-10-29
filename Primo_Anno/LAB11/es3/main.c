#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

typedef struct info{
                char materia [N];
                char nome_prof [N];
                char cognome_prof [N];
                int periodo;
                int crediti;
                float percentuale;
    }info;

int main(int argc,char *argv[])
{

    if(argc!=2){
        fprintf(stderr,"Si e' verificato un errore nel numero di argomenti\n");
        return -1;
    }

    FILE *f1;

    f1=fopen(argv[1],"r");
    if(f1==NULL){
        fprintf(stderr,"Si e' verificato un errore nell'apertura del file\n");
        return -2;
    }

    info esami[80];
    int i=0;
    int n=0;
    int length;
    int max;
    int sum=0;
    float tot=0;
    float media;
    float min1=101.0;
    float min2=101.0;
    float min3=101.0;
    float min4=101.0;
    char cercami[N];

    while(fscanf(f1,"%s%s%s%d%d%f",esami[i].materia,esami[i].nome_prof,esami[i].cognome_prof,&esami[i].periodo,&esami[i].crediti,&esami[i].percentuale)!=EOF){
        i++;
    }
    length=i;
    max=esami[0].crediti;

    for(i=0;i<length;i++){
        if(esami[i].crediti>max){
            max=esami[i].crediti;
        }
        if(esami[i].periodo==1&&esami[i].percentuale<min1){
            min1=esami[i].percentuale;
        }
        if(esami[i].periodo==2&&esami[i].percentuale<min2){
            min2=esami[i].percentuale;
        }
        if(esami[i].periodo==3&&esami[i].percentuale<min3){
            min3=esami[i].percentuale;
        }
        if(esami[i].periodo==4&&esami[i].percentuale<min4){
            min4=esami[i].percentuale;
        }
    }

    for(i=0;i<length;i++){
        if(esami[i].crediti==max){
            printf("L'esame %s vale il massimo dei crediti: %d\n",esami[i].materia,max);
        }
        if(esami[i].periodo==1&&esami[i].percentuale==min1){
            printf("L'esame %s ha la minor percentuale di superamento del primo periodo: %f\n",esami[i].materia,min1);
        }
        if(esami[i].periodo==2&&esami[i].percentuale==min2){
            printf("L'esame %s ha la minor percentuale di superamento del secondo periodo: %f\n",esami[i].materia,min2);
        }
        if(esami[i].periodo==3&&esami[i].percentuale==min3){
            printf("L'esame %s ha la minor percentuale di superamento del terzo periodo: %f\n",esami[i].materia,min3);
        }
        if(esami[i].periodo==4&&esami[i].percentuale==min4){
            printf("L'esame %s ha la minor percentuale di superamento del quarto periodo: %f\n",esami[i].materia,min4);
        }
    }

    printf("Ora cercami un professore che di cognome fa: ");
    scanf("%s",cercami);
    for(i=0;i<length;i++){
        if(strcmp(cercami,esami[i].cognome_prof)==0){
            sum+=esami[i].crediti;
            tot+=esami[i].percentuale;
            n++;
        }
    }
    media=(float)tot/n;
    if(n>0){
        printf("La somma dei crediti degli insegnamenti di %s e' %d\n",cercami,sum);
        printf("La media di superamento degli esami di %s e' %.1f\n",cercami,media);
    }
    else printf("Non e' stato trovato nessun %s",cercami);
    fclose(f1);

    return 0;
}
