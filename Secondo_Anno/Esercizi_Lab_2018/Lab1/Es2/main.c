#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_WORD 50
#define MAX_DIZIONARIO 30
#define MAX_RIGA 201

typedef struct entry{
    char compresso[MAX_WORD];
    char originale[MAX_WORD];
    int lunghezza;
}Entry;

int leggo_dizionario(Entry* dizionario);
void processa_riga(char* riga,Entry* dizionario,int S,FILE* fo);
int confronta_stringa(char* riga,int i,char* originale,int lunghezza);

int main(){
    char riga[MAX_RIGA];
    Entry dizionario[MAX_DIZIONARIO];

    int S=leggo_dizionario(dizionario);
    FILE* fp;

    fp=fopen("sorgente.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file");
        exit(-1);
    }

    FILE* fo;

    fo=fopen("ricodificato.txt","w");
    if(fo==NULL){
        fprintf(stderr,"Errore apertura file");
        exit(-2);
    }

    while(fgets(riga,MAX_RIGA,fp)!=NULL){
        processa_riga(riga,dizionario,S,fo);
    }

    return 0;
}

int leggo_dizionario(Entry* dizionario){

    int i,S;
    FILE* fp;

    fp=fopen("dizionario.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file");
        exit(-1);
    }

    fscanf(fp,"%d",&S);

    for(i=0;i<S;i++){
        fscanf(fp,"%s%s",dizionario[i].compresso,dizionario[i].originale);
        dizionario[i].lunghezza=strlen(dizionario[i].originale);
    }

    return S;
}

void processa_riga(char* riga,Entry* dizionario,int S,FILE* fo){

    int i=0,j,match;

    while(riga[i]!='\n'){
        match=0;
        for(j=0;j<S;j++){
            if(confronta_stringa(riga,i,dizionario[j].originale,dizionario[j].lunghezza)){
                match=1;
                break;
            }
        }
        if(match){
            fprintf(fo,"%s",dizionario[j].compresso);
            fprintf(stdout,"%s",dizionario[j].compresso);
            i+=dizionario[j].lunghezza;
        }
        else{
            fprintf(fo,"%c",riga[i]);
            fprintf(stdout,"%c",riga[i]);
            i++;
        }
    }
    fprintf(fo,"\n");
    fprintf(stdout,"\n");
    return;
}

int confronta_stringa(char* riga,int i,char* originale,int lunghezza){
    return (strncmp(riga+i,originale,lunghezza)==0);
}
