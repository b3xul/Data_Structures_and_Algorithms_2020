#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXN 1000 //dimensione massima file
#define MAXS 30+1 //dimensione massima stringhe

typedef struct tabella{
    char codice_volo[MAXS];
    char partenza[MAXS];
    char destinazione[MAXS];
    char data_e_ora[MAXS];
    char vettore[MAXS];
} tabella;

typedef enum {
    r_date,r_origine,r_destinazione,r_vettore,r_fine,r_err //da zero a 5
} comando_e;

int leggiTabella(tabella *Tabella,int maxdim);
comando_e leggiComando(char input[12+1]);
void strToLower(char input[12+1]);
int selezionaComando(tabella *Tabella,int nDati,comando_e comando);
int selezionaDati(tabella *Tabella,int nDati,comando_e comando,char info[MAXS*2]);

int main()
{
    int nDati;
    tabella Tabella[MAXN];
    comando_e comando;          /*comando=variabile di tipo comando_elenco*/
    char input[12+1];           /*massima lunghezza per un comando*/
    int continua;

    nDati=leggiTabella(Tabella,MAXN);
    printf("Ho letto %d righe correttamente.\n",nDati);

    printf("Seleziona il comando da eseguire:\ndate per trovare i voli che partono in quell'intervallo di date\norigine per trovare i voli che partono dalla localita' scelta\ndestinazione per trovare i voli che arrivano nella localita' scelta\nvettore per trovare i voli che usano quel vettore\nfine per terminare il programma\n");

    continua=1;
    while(continua){
        scanf("%s",input);
        comando=leggiComando(input);
        continua=selezionaComando(Tabella,nDati,comando);
    }

    return 0;
}

int leggiTabella(tabella *Tabella,int maxdim){
    FILE *fi;
    if((fi=fopen("voli.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }
    int nDati;
    int dati_corretti=0;
    int i;

    fscanf(fi,"%d",&nDati);
    if(nDati>maxdim){
        printf("Troppe informazioni!\n");
        exit(-2);
    }

    for(i=0;i<nDati;i++)
        dati_corretti=dati_corretti+fscanf(fi,"%s%s%s%s%s",Tabella[i].codice_volo,Tabella[i].partenza,Tabella[i].destinazione,Tabella[i].data_e_ora,Tabella[i].vettore);

    return (dati_corretti/5);
}

comando_e leggiComando(char input[12+1]){
    comando_e c;
    char comandi[r_err][12+1]={"date","origine","destinazione","vettore","fine"};
    strToLower(input);

    c=r_date;
    while(c<r_err&&strcmp(input,comandi[c])!=0) c++;

    return c;
}

void strToLower(char input[12+1]){
    int i;
    for(i=strlen(input);i>=0;i--) input[i]=tolower(input[i]);
    return;
}

int selezionaComando(tabella Tabella[MAXN],int nDati,comando_e comando){
    char info[MAXS*2];  //informazioni relative al comando
    int flag=1;         //1=continua, 0=non continuare
    int trovato=1;      //se non trovo farlo sapere all'utente

    if(comando!=r_fine) getchar();          //buttare lo spazio tra comando e informazioni
    gets(info);

    switch(comando){
        case r_date:
            trovato=selezionaDati(Tabella,nDati,r_date,info);
            break;
        case r_origine:
            trovato=selezionaDati(Tabella,nDati,r_origine,info);
            break;
        case r_destinazione:
            trovato=selezionaDati(Tabella,nDati,r_destinazione,info);
            break;
        case r_vettore:
            trovato=selezionaDati(Tabella,nDati,r_vettore,info);
            break;
        case r_fine: flag=0;
            break;
        default: printf("Comando non riconosciuto, riprova!\n");
            break;
    }
    if(!trovato) printf("Nessun volo corrispondente\n");

    return flag;
}

int selezionaDati(tabella Tabella[MAXN],int nDati,comando_e comando,char info[MAXS*2]){
    int i;
    char data1[MAXS],data2[MAXS];
    int trovato=0;
    char tmp[MAXS];

    switch(comando){
        case r_date:
            sscanf(info,"%s%s",data1,data2);
            if(strcmp(data1,data2)>0){
                strcpy(tmp,data1);
                strcpy(data1,data2);
                strcpy(data2,tmp);
            }
            int lunghezza1=strlen(data1);
            int lunghezza2=strlen(data2);
            for(i=0;i<nDati;i++){
                if(strncmp(Tabella[i].data_e_ora,data1,lunghezza1)>=0&&strncmp(Tabella[i].data_e_ora,data2,lunghezza2)<=0){
                    printf("%s\n",Tabella[i].codice_volo);
                    trovato=1;
                }
            }
            break;
        case r_origine:
            for(i=0;i<nDati;i++){
                if(strcmp(Tabella[i].partenza,info)==0){
                    printf("%s\n",Tabella[i].codice_volo);
                    trovato=1;
                }
            }
            break;
        case r_destinazione:
            for(i=0;i<nDati;i++){
                if(strcmp(Tabella[i].destinazione,info)==0){
                    printf("%s\n",Tabella[i].codice_volo);
                    trovato=1;
                }
            }
            break;
        case r_vettore:
            for(i=0;i<nDati;i++){
                if(strcmp(Tabella[i].vettore,info)==0){
                    printf("%s\n",Tabella[i].partenza);
                    trovato=1;
                }
            }
            break;
        default: printf("Errore inaspettato, riprova!\n");
            break;
    }

    return trovato;
}
