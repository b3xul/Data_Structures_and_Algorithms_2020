#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "D:\Users\utente\Desktop\Università\Secondo Anno\Materiali Algoritmi e Programmazione\Algoritmi_Teoria\Codici\2019\Codice C Cap06\RecursiveSort\RecursiveSorting.h"


typedef Item att_t;

void attSel(int N, att_t* v);
void powerset(int pos, att_t* v, int* soluzione_corrente, int* soluzione_migliore, int durata_corrente, int* durata_max, int N);
int interseca_sol(att_t* v, int* soluzione_corrente, int pos);
void attSelDP(int n, att_t* v);
int durata_A(att_t a);
void attSelRecursive(int n, att_t* v);
int attSelRRecursive(int pos, att_t* v, int* q);
void displaySol(att_t* v, int* opt, int* q, int n);
void displaySolR(int pos, att_t* v, int* opt, int* q);

int main(){
    att_t* V;
    int i,n_att;

    FILE* fp=fopen("att1.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file\n");
        exit(-1);
    }

    fscanf(fp,"%d",&n_att);
    V=(att_t*)malloc((n_att+1)*sizeof(att_t));
    V[0].S=0;
    V[0].F=0;
    for(i=1;i<=n_att;i++)
        fscanf(fp,"%d%d",&V[i].S,&V[i].F);

    MergeSort(V,n_att+1);
    for(i=1;i<=n_att;i++)
        printf("(%d,%d)\n",V[i].S,V[i].F);

    attSel(n_att+1,V);

    attSelRecursive(n_att+1,V);

    attSelDP(n_att+1,V);

    return 0;
}

void attSel(int N, att_t* v){
    printf("Soluzione con powerset:\n");
    int* soluzione_corrente=(int*)calloc(N,sizeof(int));
    int* soluzione_migliore=(int*)calloc(N,sizeof(int));
    int durata_massima=0;
    int i;

    powerset(0,v,soluzione_corrente,soluzione_migliore,0,&durata_massima,N);

    printf("Soluzione migliore con valore massimo di durata=%d:\n",durata_massima);
    for(i=1;i<N;i++){
        if(soluzione_migliore[i]!=0)
            printf("(%d,%d)\n",v[i].S,v[i].F);
    }
    free(soluzione_migliore);
    free(soluzione_corrente);
}

/*Uso powerset con disposizioni ripetute di 2 elementi (0 e 1) a gruppi di N posizioni*/
void powerset(int pos, att_t* v, int* soluzione_corrente, int* soluzione_migliore, int durata_corrente, int* durata_max, int N){
    int i;

    if(pos>=N){ //Caso terminale
        if(durata_corrente>*durata_max){
            *durata_max=durata_corrente;
            for(i=0;i<N;i++){
                soluzione_migliore[i]=soluzione_corrente[i];
            }
            return;
        }
        return;
    }


    if(!interseca_sol(v,soluzione_corrente,pos)){       //Confronto v[i] con v[prec] per vedere se posso aggiungere i (è compatibile)
        soluzione_corrente[pos]=1;
        powerset(pos+1,v,soluzione_corrente,soluzione_migliore, durata_corrente+durata_A(v[pos]) ,durata_max,N);
    }
    soluzione_corrente[pos]=0;
    powerset(pos+1,v,soluzione_corrente,soluzione_migliore,durata_corrente,durata_max,N);  //Prec indica il valore dell'ultimo indice preso, quindi pos se ho preso quell'indice, prec se non l'ho preso

    return;
}

int interseca_sol(att_t* v, int* soluzione_corrente, int pos){
    int i;
    for(i=0;i<pos;i++){
        if(soluzione_corrente[i]){
            if( (v[i].S<v[pos].F ) && (v[pos].S<v[i].F) )
                return 1;
        }
    }
    return 0;
}

int durata_A(att_t a){
    return a.F-a.S;
}

int max(int a,int b){
    return (a>b)?a:b;
}

int incompatibile(att_t* v, int i, int j){
    if( (v[i].S<v[j].F ) && (v[j].S<v[i].F) )
        return 1;
    return 0;
}

void attSelRecursive(int n, att_t* v){

    printf("Ricorsione per trovare valore\n");
    int i,j;
    int* q=(int*)calloc(n,sizeof(int));
    q[0]=q[1]=0;

    for(i=2;i<n;i++){
        for(j=1;j<i;j++){
            if(!incompatibile(v,i,j))
                q[i]=j;
        }
    }

    printf("Valore massimo di durate ottenibili: %d\n",attSelRRecursive(n-1,v,q));  //N= dimensione v e q, N-1 è l'indice!

    return;

}

int attSelRRecursive(int pos, att_t* v, int* q){
    if(pos==0)
        return 0;
    return max( attSelRRecursive(pos-1,v,q) , durata_A(v[pos])+attSelRRecursive(q[pos],v,q));
}

void attSelDP(int n, att_t* v){
    printf("Programmazione dinamica\n");
    int i,j;
    int* q=(int*)calloc(n,sizeof(int));
    q[0]=q[1]=0;

    for(i=2;i<n;i++){
        for(j=1;j<i;j++){
            if(!incompatibile(v,i,j))
                q[i]=j;
        }
    }

    int* opt=(int*)calloc(n,sizeof(int));
    opt[0]=0;
    opt[1]=durata_A(v[1]);

    /*Non mi serve distinguere i 2 casi di compatibilità o meno perchè in q includo quell'informazione
    (opt[q[i]] sarebbe opt[i-1] in quel caso e si andrebbe semplicemente a sommare i due valori*/

    for(i=2;i<n;i++){
        opt[i]=max( opt[i-1], durata_A(v[i])+opt[q[i]]);
    }
    printf("Valore massimo di durate ottenibili: %d\n",opt[n-1]);

    displaySol(v,opt,q,n-1);    //Passo indice di partenza

    printf("Oppure:\n");

    displaySolR(n-1,v,opt,q);
}

void displaySol(att_t* v, int* opt, int* q, int n){
    printf("Soluzione:\n");
    while(n>0){
        if(opt[n]>opt[n-1]){ //Ho preso la cella n
            printf("(%d,%d) ",v[n].S,v[n].F);
            n=q[n];
        }
        else
            n--;
    }
    printf("\n");
}

void displaySolR(int pos, att_t* v, int* opt, int* q){

  if (pos==0)
    return;

  if (durata_A(v[pos])+opt[q[pos]] >= opt[pos-1]) {
    displaySolR(q[pos], v, opt, q);
    printf("(%d %d) ", v[pos].S, v[pos].F);
  }
  else
    displaySolR(pos-1, v, opt, q);

}
