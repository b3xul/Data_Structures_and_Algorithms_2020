#include <stdio.h>
#include <stdlib.h>

typedef struct att{
    int S;
    int F;
}att_t;

void attSel(int N, att_t* v);
void powerset(int pos, att_t* v, int* soluzione_corrente, int* soluzione_migliore, int durata_corrente, int* durata_max, int N);
int incompatibile(att_t* v, int* soluzione_corrente, int pos);
int durata_A(att_t a);

int main(){
    att_t* V;
    int i,n_att;

    FILE* fp=fopen("att1.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file\n");
        exit(-1);
    }

    fscanf(fp,"%d",&n_att);
    V=(att_t*)malloc(n_att*sizeof(att_t));
    for(i=0;i<n_att;i++)
        fscanf(fp,"%d%d",&V[i].S,&V[i].F);

    attSel(n_att,V);

    return 0;
}

void attSel(int N, att_t* v){
    int* soluzione_corrente=(int*)calloc(N,sizeof(int));
    int* soluzione_migliore=(int*)calloc(N,sizeof(int));
    int durata_massima=0;
    int i;

    powerset(0,v,soluzione_corrente,soluzione_migliore,0,&durata_massima,N);

    printf("Soluzione migliore con valore massimo di durata=%d:\n",durata_massima);
    for(i=0;i<N;i++){
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


    if(!incompatibile(v,soluzione_corrente,pos)){       //Confronto v[i] con v[prec] per vedere se posso aggiungere i (è compatibile)
        soluzione_corrente[pos]=1;
        powerset(pos+1,v,soluzione_corrente,soluzione_migliore, durata_corrente+durata_A(v[pos]) ,durata_max,N);
    }
    soluzione_corrente[pos]=0;
    powerset(pos+1,v,soluzione_corrente,soluzione_migliore,durata_corrente,durata_max,N);  //Prec indica il valore dell'ultimo indice preso, quindi pos se ho preso quell'indice, prec se non l'ho preso

    return;
}

int incompatibile(att_t* v, int* soluzione_corrente, int pos){
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

