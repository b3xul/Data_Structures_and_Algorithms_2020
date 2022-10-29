#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXS 200

typedef struct voce{
    int lunghezza;
    char parola[MAXS];
} voce;

// typedef struct voce dizionario[30]; ok ma superfluo

int main()
{
    FILE *fi;
    FILE *fs;
    FILE *fo;
    if((fi=fopen("src.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file sorgente.");
        return -1;
    }
    if((fs=fopen("sost.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file dizionario.");
        return -2;
    }
    if((fo=fopen("dest.txt","w"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file di output.");
        return -3;
    }

    int i;
    int ld; //lunghezza dizionario
    voce v[30]; //30 voci del dizionario
    char parola[MAXS];
    int trovato; //flag di confronto nel dizionario
    int length;   //strlen parola

    fscanf(fs,"%d",&ld);    //leggi dizionario
    for(i=0;i<ld;i++){
        fscanf(fs,"%d %s",&v[i].lunghezza,v[i].parola);
    }

    while(fscanf(fi,"%s",parola)!=EOF){
        length=strlen(parola);
        trovato=0;
        if(ispunct(parola[length-1])) length--;

        for(i=0;i<ld&&!trovato;i++){
            if(length==v[i].lunghezza){
                fprintf(fo,"%s",v[i].parola);   //stampa parola senza virgola (nel vocabolario non ci sono)
                trovato=1;
            }
        }
        if(!trovato) fprintf(fo,"%s",parola);   //stampa parola e segno di punteggiatura

        char c=getc(fi);

        if(ispunct(parola[length])&&trovato) putc(parola[length],fo);   //devo stampare il segno di punteggiatura solo se ho usato parola del dizionario
        if(c!=EOF) putc(c,fo);  //stampa spazio o a capo, ma non EOF

    }

    fclose(fi);
    fclose(fs);
    fclose(fo);

    return 0;
}
