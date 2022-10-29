#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *scelte;
    int num_scelte;
}Livello;

void w_generatore(char *nome_i,char *nome_o);
int generatore_R(int pos,Livello *val,char *sol,int n,int count,FILE *fo);

int main()
{
    char nome_i[11]="Valori.txt";
    char nome_o[10]="Sigle.txt";

    w_generatore(nome_i,nome_o);

    return 0;
}

void w_generatore(char *nome_i,char *nome_o){

    FILE *fi,*fo;
    if((fi=fopen(nome_i,"r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file in ingresso.\n");
        exit(-1);
    }
    if((fo=fopen(nome_o,"w"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file in uscita.\n");
        exit(-2);
    }
    int i,n,pos;
    Livello *val;
    char buffer[10+1];
    char *sol;
    int count;

    fscanf(fi,"%d",&n);
    val=(Livello*)malloc(n*sizeof(Livello));  //vettore di struct Livello
    if(val==NULL)   exit(-3);

    i=0;
    while(fscanf(fi,"%s",buffer)!=EOF){
        val[i].num_scelte=strlen(buffer);
        val[i].scelte=(char*)malloc(val[i].num_scelte*sizeof(char)); //alloca in ogni livello il vettore di caratteri adeguato
        if(val[i].scelte==NULL)   exit(-3);
        strcpy(val[i].scelte,buffer);   //riempi il livello attuale
        i++;
    }

    sol=(char*)malloc(n*sizeof(char));
    if(sol==NULL)   exit(-3);

    pos=0;
    count=-1;

    if(generatore_R(pos,val,sol,n,count,fo)==-1)
        printf("Nessuna soluzione disponibile.\n");


    fclose(fi);
    fclose(fo);

    return;
}

int generatore_R(int pos,Livello *val,char *sol,int n,int count,FILE *fo){
    int i;
    if(pos==n){
        for(i=0;i<n;i++)
            fprintf(fo,"%c",sol[i]);
        fprintf(fo,"\n");
        return count+1;
    }
    for(i=0;i<val[pos].num_scelte;i++){
        sol[pos]=val[pos].scelte[i];
        count=generatore_R(pos+1,val,sol,n,count,fo);
    }
    return count;
}
