#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prodotto{
    char *nome;
    float prezzo;
}Prodotto;

int contaProdotti(void);
Prodotto *leggiProdotti(int n);
int comb_sempl(int pos,Prodotto *val,Prodotto *sol,int n,int k,int start,int count,int cap,float curr_val);

int main()
{
    int risultati;
    int n,k;
    float cap;
    n=contaProdotti();

    Prodotto *val;
    val=leggiProdotti(n);

    printf("Inserisci la cardinalita' dell'insieme cercato: ");
    scanf("%d",&k);

    Prodotto *sol=(Prodotto *)malloc(k*sizeof(Prodotto));
    if(sol==NULL)   exit(-3);

    printf("Inserisci la spesa massima accettabile: ");
    scanf("%f",&cap);

    risultati=comb_sempl(0,val,sol,n,k,0,0,cap,0);

    if(risultati==0)
        printf("Non ci sono soluzioni possibili.\n");

    return 0;
}


int contaProdotti(void){

    FILE *fi;
    if((fi=fopen("prodotti.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }

    int n;
    fscanf(fi,"%d",&n);

    fclose(fi);

    return n;
}

Prodotto *leggiProdotti(int n){
    FILE *fi;
    if((fi=fopen("prodotti.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }
    fscanf(fi,"%*d");

    int i;
    Prodotto *val=(Prodotto *)malloc(n*sizeof(Prodotto));
    if(val==NULL) exit(-2);

    char buffer[25+1];

    for(i=0;i<n;i++){
        fscanf(fi,"%s%f",buffer,&val[i].prezzo);
        val[i].nome=strdup(buffer);
    }

    fclose(fi);

    return val;
}

int comb_sempl(int pos,Prodotto *val,Prodotto *sol,int n,int k,int start,int count,int cap,float curr_val){
    int i;

    if(pos==k){
        if(curr_val<=cap){
            for(i=0;i<k;i++)
                printf("%s\t",sol[i].nome);
            printf("\n");
            return count+1;
        }
        return count;
    }

    for(i=start;i<n;i++){

        curr_val+=val[i].prezzo;
        if(curr_val<=cap){
            sol[pos].prezzo=val[i].prezzo;
            sol[pos].nome=strdup(val[i].nome);
        }
        count=comb_sempl(pos+1,val,sol,n,k,i+1,count,cap,curr_val);
        curr_val-=val[i].prezzo;
    }

    return count;
}

