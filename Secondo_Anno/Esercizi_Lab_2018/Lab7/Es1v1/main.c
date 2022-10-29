#include <stdio.h>
#include <stdlib.h>

#define N 4     //Numero di tipi di gemme

int disp_rip(int pos, char* val, int* sol, int* n_gemme, int n, int k, int prec);
int controlla(int* sol, int* n_gemme, int k);

int main()
{
    FILE* fp=fopen("hard_test_set.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }
    int i,j,k,n_sets,max_lun;
    char gemme[N]={'Z','R','T','S'};
    int n_gemme[N];
    int* sol;

    fscanf(fp,"%d",&n_sets);

    for(i=0;i<n_sets;i++){
        printf("Test set #%d: ", i+1);
        max_lun=0;
        /*Inizializzo lunghezza massima della collana e numero di gemme massime disponibili*/
        for(j=0;j<N;j++){
            fscanf(fp,"%d",&n_gemme[j]);
            printf("%d ",n_gemme[j]);
            max_lun+=n_gemme[j];
        }
        printf("\n");

        for(k=max_lun;k>=1;k--){
            //K= lunghezza della collana che vado a guardare E numero massimo di ripetizioni per OGNI elemento di gemme
            //Nella condizione di terminazione dovrò controllare che i vincoli non eccedano le disponibilità di ogni gemma
            //ma non che la cardinalità sia massima perchè la prima che trovo è sicuramente quella a cardinalità massima per cui posso già interrompere la ricerca
            printf("k=%d\n",k);
            sol=(int*)malloc(k*sizeof(int));
            if(sol==NULL){
                fprintf(stderr,"Errore nell'allocazione\n");
                exit(-2);
            }

            if(disp_rip(0,gemme,sol,n_gemme,N,k,-1))
                break;
        }

    }

    return 0;
}

int disp_rip(int pos, char* val, int* sol, int* n_gemme, int n, int k, int prec){
    int i;

    /*Condizione di terminazione*/
    if(pos>=k){
        for(i=0;i<k;i++){
            printf("%c",val[sol[i]]);
        }
        printf("\nE' una soluzione valida e di lunghezza massima=%d\n",k);
        return 1;
    }

    /*Ricorsione*/
    for(i=0;i<n;i++){
        if(n_gemme[i]>0){   //Pruning sul numero di gemme permette di arrivare a k=18
            if(prec!=-1){
                if( ((sol[prec]==0) || (sol[prec]==2)) && (i!=0) && (i!=1) )        //Se non rispetta condizioni non ricorre ma passa al ciclo successivo
                    continue;
                if( ((sol[prec]==1) || (sol[prec]==3)) && (i!=2) && (i!=3) )
                    continue;
            }
            n_gemme[i]--;
            sol[pos]=i;     //Sol conterrà gli indici di val da stampare
            if(disp_rip(pos+1,val,sol,n_gemme,n,k,pos))
                return 1;
            n_gemme[i]++;
        }
    }
    return 0;
}
