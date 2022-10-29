#include <stdio.h>
#include <stdlib.h>

#define N 4     //Numero di tipi di gemme

int disp_rip(int pos, char* val, int* sol, int* n_gemme, int n, int k);
int controlla(int* sol, int* n_gemme, int k);

int main()
{
    FILE* fp=fopen("very_easy_test_set.txt","r");
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

            if(disp_rip(0,gemme,sol,n_gemme,N,k))
                break;
        }

    }

    return 0;
}

int disp_rip(int pos, char* val, int* sol, int* n_gemme, int n, int k){
    int i;

    /*Condizione di terminazione*/
    if(pos>=k){

        /*printf("Trying: ");
        for(i=0;i<k;i++){
            printf("%c",val[sol[i]]);
        }
        printf("\n");*/

        if(controlla(sol,n_gemme,k)){
            for(i=0;i<k;i++){
                printf("%c",val[sol[i]]);
            }
            printf("     E' una soluzione valida e di lunghezza massima=%d\n",k);
            return 1;
        }
        //printf("Soluzione non accettabile!\n");
        return 0;
    }

    /*Ricorsione*/
    for(i=0;i<n;i++){
        sol[pos]=i;     //Sol conterrà gli indici di val da stampare
        if(disp_rip(pos+1,val,sol,n_gemme,n,k))
            return 1;
    }
    return 0;
}

int controlla(int* sol, int* n_gemme, int k){
    int i;
    int gemme_usate[N]={0};

    //Z=0 R=1 T=2 S=3

    for(i=0;i<k;i++){
        gemme_usate[sol[i]]++;
        if(gemme_usate[sol[i]]>n_gemme[sol[i]])
            return 0;
        if(i>=1){
            switch(sol[i-1]){
                /*Accorpabili*/
                case 0:     //Z seguito da Z o R
                    if( (sol[i]!=0) && (sol[i]!=1) )
                        return 0;
                    break;
                case 1:     //R seguito da T o S
                    if( (sol[i]!=2) && (sol[i]!=3) )
                        return 0;
                    break;
                case 2:     //T seguito da Z o R
                    if( (sol[i]!=0) && (sol[i]!=1) )
                        return 0;
                    break;
                case 3:     //S seguito da T o S
                    if( (sol[i]!=2) && (sol[i]!=3) )
                        return 0;
                    break;

            }
        }
    }

    return 1;
}
