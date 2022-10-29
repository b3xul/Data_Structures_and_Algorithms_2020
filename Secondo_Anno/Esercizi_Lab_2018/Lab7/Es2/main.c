#include <stdio.h>
#include <stdlib.h>

#define N 4     //Numero di tipi di gemme

int disp_rip(int pos, int curr_val, int* curr_sol, int* n_gemme, int* valori_gemme, int* gemme_usate, int* gemme_ripetute, int prec, int* best_sol, int* best_val, int* best_lun, int max_rip, int max_lun);
void solve(char* gemme, int* n_gemme, int* valori_gemme, int max_lun, int max_rip);
int min(int a,int b);

int main()
{
    FILE* fp=fopen("test_set.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }

    int i,j,n_sets,max_lun;
    char gemme[N]={'Z','R','T','S'};
    int n_gemme[N];
    int valori_gemme[N];
    int max_rip;

    fscanf(fp,"%d",&n_sets);

    for(i=0;i<n_sets;i++){
        printf("\nTest set #%d: ", i+1);

        max_lun=0;

        /*Inizializzo lunghezza massima della collana e numero di gemme usate*/
        for(j=0;j<N;j++){
            fscanf(fp,"%d",&n_gemme[j]);
            max_lun+=n_gemme[j];
        }
        printf("\n");

        /*Inizializzo valori delle gemme*/
        for(j=0;j<N;j++) {
            fscanf(fp, "%d", &valori_gemme[j]);
            printf("%c = %d [val=%d], ", gemme[j], n_gemme[j], valori_gemme[j]);
        }
        fscanf(fp, "%d", &max_rip);
        printf("TOT = %d {maxrip = %d}\n", max_lun, max_rip);

        solve(gemme,n_gemme,valori_gemme,max_lun,max_rip);

    }

    fclose(fp);
    return 0;
}

void solve(char* gemme, int* n_gemme, int* valori_gemme, int max_lun, int max_rip){
    int best_lun=0,best_val=0,prec=-1,pos=0,curr_val=0;
    int* curr_sol=(int*)calloc(max_lun,sizeof(int));
    int* best_sol=(int*)calloc(max_lun,sizeof(int));
    int* gemme_usate=(int*)calloc(N,sizeof(int));
    int* gemme_ripetute=(int*)calloc(N,sizeof(int));
    int i;

    disp_rip(pos,curr_val,curr_sol,n_gemme,valori_gemme,gemme_usate,gemme_ripetute,prec,best_sol,&best_val,&best_lun,max_rip,max_lun);

    printf("Soluzione ottima con val=%d e lunghezza %d.\n", best_val, best_lun);
    printf("Composizione collana: ");
    for (i=0; i<best_lun; i++)
        printf("%c", gemme[best_sol[i]]);
    printf("\n");

    free(gemme_ripetute);
    free(gemme_usate);
    free(best_sol);
    free(curr_sol);
    return;
}

int disp_rip(int pos, int curr_val, int* curr_sol, int* n_gemme, int* valori_gemme, int* gemme_usate, int* gemme_ripetute, int prec, int* best_sol, int* best_val, int* best_lun, int max_rip, int max_lun) {
    int i,prec_rip;

    /*Controllo se la soluzione attuale ha valore massimo*/
    if(curr_val>*best_val){
        if (gemme_usate[0] <= gemme_usate[3]){  //Controllo se il numero di Z è minore di quello di S
            *best_val=curr_val;
            *best_lun=pos;
            for(i=0;i<pos;i++)
                best_sol[i]=curr_sol[i];
        }
    }
    /*Se ho raggiunto il massimo della lunghezza della soluzione mi fermo*/
    if (pos >= max_lun)
        return 1;

    for(i=0;i<N;i++){
        /*Condizione sbagliata, controlla che ogni tipologia non si ripeta più di max_rip volte, ma non max_rip volte consecutivamente
        if(gemme_usate[i]+1<=min(n_gemme[i],max_rip)){*/
        /*Controllo ci siano ancora gemme disponibili*/
        if(n_gemme[i]-gemme_usate[i]>0){
            /*Controllo condizioni di vicinanza*/
            if(prec!=-1){
                if( ((prec==0) || (prec==2)) && (i!=0) && (i!=1) )        //Se non rispetta condizioni sul rapporto con la gemma precedente non ricorre ma passa al ciclo successivo
                    continue;
                if( ((prec==1) || (prec==3)) && (i!=2) && (i!=3) )
                    continue;
            }
            /*Controllo condizione su gemme ripetute consecutive*/
            if (prec == i) {
                if (gemme_ripetute[i]+1 > max_rip)
                    continue;
            }

            /*Aggiornamento gemme_ripetute*/
            if(prec==-1)
                gemme_ripetute[i]=1;
            else if(prec==i)
                gemme_ripetute[i]++;
            else{
                gemme_ripetute[i]=1;
                prec_rip=gemme_ripetute[prec];  //Salvo ripetizioni della gemma precedente cosicchè quando ricorro su un'i diversa so se potrò usarne un'altra o no
                gemme_ripetute[prec]=0;
            }
            gemme_usate[i]++;
            curr_sol[pos]=i;     //Sol conterrà gli indici di val da stampare

            /*N.B. Prec indica l'ultima gemma presa, NON l'ultimo indice riempito del vettore curr_sol!*/
            if(disp_rip(pos+1, curr_val+valori_gemme[i], curr_sol, n_gemme, valori_gemme, gemme_usate, gemme_ripetute, i, best_sol, best_val, best_lun, max_rip, max_lun))
                return 1;

            gemme_usate[i]--;
            if(prec==-1)
                gemme_ripetute[i]=0;
            else if(prec==i)
                gemme_ripetute[i]--;
            else{
                gemme_ripetute[i]=0;
                gemme_ripetute[prec]=prec_rip;
            }

        }
    }
    return 0;
}

int min(int a,int b){
    return (a<=b)?a:b;
}
