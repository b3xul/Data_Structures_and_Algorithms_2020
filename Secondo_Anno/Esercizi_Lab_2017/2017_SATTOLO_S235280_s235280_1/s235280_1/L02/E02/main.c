#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int dentrolaparola(char parola[25+1],char ch);

void contieneprefisso(char parola[25+1],char prefisso[5], int lunghezzaprefisso,int posizione);

int main()
{
    FILE *f1;
    FILE *f2;

    if((f1=fopen("sequenze.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura file sequenze!\n");
        return -1;
    }
    if((f2=fopen("testo.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura file di testo!\n");
        return -2;
    }
    int nseq,i,j,k,continua,lunghezzaprefisso,lunghezzariga,posizione;
    char prefisso[20][5+1];
    char parola[25+1];
    char riga[200+1];

    fscanf(f1,"%d",&nseq);
    for(i=0;i<nseq;i++){
        fscanf(f1,"%s",prefisso[i]);
        for(j=0;j<strlen(prefisso[i]);j++) prefisso[i][j]=tolower(prefisso[i][j]);
    }
    posizione=0;
    while(fgets(riga,200,f2)!=NULL){
        continua=1;
        k=0;
        lunghezzariga=strlen(riga);
        while(k<lunghezzariga){
            while(continua){
                continua=dentrolaparola(parola,riga[k]);
                k++;
            }
            posizione++;
            for(i=0;i<nseq;i++){
                lunghezzaprefisso=strlen(prefisso[i]);
                contieneprefisso(parola,prefisso[i],lunghezzaprefisso,posizione);
            }
            continua=1;
            if(strlen(parola)==0) posizione --;
            parola[0]='\0';
        }
    }
    return 0;
}

int dentrolaparola(char parola[25+1],char ch){
    char stringach[2];

    if(ispunct(ch)||isspace(ch)||(int)ch<0) return 0; //'=-110??
    else{
        stringach[0]=tolower(ch);
        stringach[1]='\0';
        strcat(parola,stringach);
        return 1;
    }
}

void contieneprefisso(char parola[25+1],char prefisso[5], int lunghezzaprefisso,int posizione){

    if(strncmp(parola,prefisso,lunghezzaprefisso)==0){
        printf("%s\n",prefisso);
        printf("%s %d\n",parola,posizione);
    }
}
