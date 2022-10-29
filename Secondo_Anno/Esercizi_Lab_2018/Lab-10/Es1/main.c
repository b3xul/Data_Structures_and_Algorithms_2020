#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 101
#define MAX_ES 5
#define MAX_DIAG 3
#define FILENAME "elementi.txt"
#define DD 11
#define DP 33

typedef struct esercizio{
    char nome[MAX_STR]; int tipo; int d_ingresso; int d_uscita; int requisito_precedenza; int finale; float valore; int difficolta;
}Esercizio;

typedef struct elementi_{
    Esercizio* elementi;
    int n;
}Elementi;

typedef struct diagonale{
    int indici_esercizi[MAX_ES]; int n_es; float valore; int difficolta; int avanti; int indietro; int sequenza; int bonus; //float valore_bonus
}Diagonale;

typedef struct diagonali_wrapper{
    Diagonale* diagonali;
    int n_diag;
    int diag_allocate;
}Diagonali_wrapper;


Elementi elementi_read();
Esercizio esercizio_read(FILE* fp);
Diagonali_wrapper* crea_diagonali(Elementi e);

void diagonali_stampa(Diagonale p[MAX_DIAG]);
void diagonali_copia(Diagonale dst[MAX_DIAG], Diagonale src[MAX_DIAG]);

void disp_rip(int pos, int* diagonale_corrente, int difficolta_corrente, Esercizio* val, int n_elementi, Diagonali_wrapper* d_w, int finale, int acro);
void crea_programma(Elementi e, Diagonali_wrapper* d_w);
void comb_rip(int pos, int start, int diff, Elementi e, Diagonali_wrapper* d_w, int* sol, int* best_sol, float* best_val, int* best_bonus_i);
int check_valido(int* sol, Elementi e, Diagonali_wrapper* d_w, float* val, int* best_bonus_i);

int main()
{
    Diagonali_wrapper* d_w;

    Elementi e=elementi_read();

    d_w=crea_diagonali(e);
    crea_programma(e,d_w);

    return 0;
}

Diagonali_wrapper* crea_diagonali(Elementi e){
    int pos=0, n=e.n;  //K=numero di elementi prendibili
    Esercizio* val=e.elementi;
    int* diagonale_corrente=(int*)calloc(MAX_ES,sizeof(int));

    Diagonali_wrapper* d_w=(Diagonali_wrapper*)malloc(1*sizeof(Diagonali_wrapper));

    d_w->diagonali=(Diagonale*)calloc(1,sizeof(Diagonale));
    d_w->n_diag=0;
    d_w->diag_allocate=1;

    disp_rip(pos,diagonale_corrente,0,val,n,d_w,0,0);

    printf("DD = %d DP = %d\nNumero di diagonali realizzabili = %d\n",DD,DP,d_w->n_diag);

    return d_w;
}

/*Pos: indice del vettore di esercizi contenuto nella diagonale che sto riempiendo attualmente
 *val: e.elementi= vettore di esercizi
 *n_elementi: e.n= numero di esercizi
 *&d_w.diagonali= vettore soluzione contenente solo soluzioni valide
 *&d_w.n_diag= totale diagonali del vettore diagonali
 *&d_w.diag_allocate= totale diagonali allocabili in d_w.diagonali
*/
void disp_rip(int pos, int* diagonale_corrente, int difficolta_corrente, Esercizio* val, int n_elementi, Diagonali_wrapper* d_w, int finale, int acro){

    int i,n_acro;

    //Diagonale valida se:d_w->diagonali
    if(pos>0){  //Ha almeno un elemento
        if(acro>0){ //Ha almeno un elemento acrobatico
            if(d_w->n_diag==d_w->diag_allocate){
                (d_w->diag_allocate)*=2;
                (d_w->diagonali)=(Diagonale*)realloc(d_w->diagonali, d_w->diag_allocate * sizeof(Diagonale));
                if(d_w->diagonali==NULL)
                    exit(-1);
            }

            d_w->diagonali[d_w->n_diag].n_es=pos;
            (d_w->diagonali)[d_w->n_diag].difficolta=difficolta_corrente;
            (d_w->diagonali)[d_w->n_diag].valore=0.0;
            (d_w->diagonali)[d_w->n_diag].avanti=0;
            (d_w->diagonali)[d_w->n_diag].indietro=0;
            (d_w->diagonali)[d_w->n_diag].sequenza=0;
            (d_w->diagonali)[d_w->n_diag].bonus=0;
            n_acro=0;
            for(i=0;i<pos;i++){
                (d_w->diagonali)[d_w->n_diag].indici_esercizi[i]=diagonale_corrente[i];
                (d_w->diagonali)[d_w->n_diag].valore+=val[diagonale_corrente[i]].valore;
                if(val[diagonale_corrente[i]].tipo==2){
                    (d_w->diagonali)[d_w->n_diag].avanti=1;
                    n_acro++;
                }
                else if(val[diagonale_corrente[i]].tipo==1){
                    (d_w->diagonali)[d_w->n_diag].indietro=1;
                    n_acro++;
                }
                else
                    n_acro=0;

                if((d_w->diagonali)[d_w->n_diag].sequenza==0 && n_acro>=2)
                    (d_w->diagonali)[d_w->n_diag].sequenza=1;

                if(i==pos-1 && val[diagonale_corrente[i]].difficolta>=8)
                    (d_w->diagonali)[d_w->n_diag].bonus=1;

            }
            (d_w->n_diag)++;
        }
    }

    if(pos>=MAX_ES || finale)//Ho riempito la diagonale su cui sto lavorando fino al massimo numero di esercizi, oppure il mio ultimo esercizio preso aveva la propriet� di essere l'ultimo prendibie per cui caso terminale della diagonale
        return;


    for(i=0;i<n_elementi;i++){  //Scorre su elementi
        //Pruning su ricorsione: Non posso ricorrere se:
        if(pos==0 && ( (val[i].d_ingresso==0) || (val[i].requisito_precedenza==1) ) )  //primo elemento ha direzione di ingresso= di spalle
            continue;
        if(pos>0 && (val[diagonale_corrente[pos-1]].d_uscita != val[i].d_ingresso) )  //nuovo elemento ha d_ingresso!= da d_uscita del precedente
            continue;
        if(difficolta_corrente+val[i].difficolta>DD)    //prendo elemento che fa eccedere la difficolt� della diagonale
            continue;
        diagonale_corrente[pos]=i;
        disp_rip(pos+1,diagonale_corrente,difficolta_corrente+val[i].difficolta,val,n_elementi,d_w,val[i].finale, ( (acro==0 && val[i].tipo==0) ? 0:acro+1) );  //( (acro==0 && val[i].tipo==0) ? 0:acro+1) sostituibile con acro+val[i]+tipo
    }
}

/* Programma deve contenere almeno 1 diagonale in avanti e 1 in indietro e 1 in seq (può essere la stessa) e somma delle difficoltà delle diagonali<DP */
void crea_programma(Elementi e, Diagonali_wrapper* d_w){
    int i,j,d,best_bonus_i=-1;
    int sol[MAX_DIAG];
    int best_sol[MAX_DIAG];
    float best_val;

    comb_rip(0,0,0,e,d_w,sol,best_sol,&best_val,&best_bonus_i);

    printf("TOT = %.3f\n", best_val);
    for(i=0;i<MAX_DIAG;i++) {
        d=best_sol[i];
        printf("DIAG %d > %.3f %s\n", best_sol[i], d_w->diagonali[d].valore, ((i==best_bonus_i) ? "* 1.5 (BONUS)" : ""));
        for(j=0;j<d_w->diagonali[d].n_es;j++)
            printf("%s ", e.elementi[d_w->diagonali[d].indici_esercizi[j]].nome);
        printf("\n");
    }
}

void comb_rip(int pos, int start, int diff, Elementi e, Diagonali_wrapper* d_w, int* sol, int* best_sol, float* best_val, int* best_bonus_i){
    int i,bonus_i=-1;
    float val;
    if(pos>=MAX_DIAG){
        if(check_valido(sol, e, d_w, &val, &bonus_i)){
            if(val>*best_val){
                *best_val=val;
                *best_bonus_i=bonus_i;
                for(i=0;i<MAX_DIAG;i++)
                    best_sol[i]=sol[i];
            }
        }
        return;
    }

    for(i=start;i<d_w->n_diag;i++){
        if(diff+d_w->diagonali[i].difficolta>DP) continue;
        sol[pos]=i;
        comb_rip(pos+1,i,diff+d_w->diagonali[i].difficolta,e,d_w,sol,best_sol,best_val,best_bonus_i);
    }
}

int check_valido(int* sol, Elementi e, Diagonali_wrapper* d_w, float* val, int* best_bonus_i){
    int i,avanti=0,indietro=0,sequenza=0;
    *val=0;
    *best_bonus_i=-1;
    float best_bonus=0;

    for(i=0;i<MAX_DIAG;i++){
        if(d_w->diagonali[sol[i]].avanti)
            avanti=1;
        if(d_w->diagonali[sol[i]].indietro)
            indietro=1;
        if(d_w->diagonali[sol[i]].sequenza)
            sequenza=1;
        if(d_w->diagonali[sol[i]].bonus && d_w->diagonali[sol[i]].valore*1.5>best_bonus){
            best_bonus=d_w->diagonali[sol[i]].valore*1.5;
            *best_bonus_i=i;
        }
    }
    if(!avanti || !indietro || !sequenza)
        return 0;


    for(i=0;i<MAX_DIAG;i++){
        if(i==*best_bonus_i)
            *val+=best_bonus;
        else
            *val+=d_w->diagonali[sol[i]].valore;
    }
    return 1;
}


Elementi elementi_read(){
    FILE* fp=fopen(FILENAME,"r");
    if(fp==NULL)
        exit(-1);

    int i;
    Elementi e;

    fscanf(fp,"%d",&e.n);

    e.elementi=(Esercizio*)malloc(e.n*sizeof(Esercizio));
    for(i=0;i<e.n;i++)
        e.elementi[i]=esercizio_read(fp);

    return e;
}

Esercizio esercizio_read(FILE* fp){
    Esercizio e;
    fscanf(fp,"%s%d%d%d%d%d%f%d",e.nome,&e.tipo,&e.d_ingresso,&e.d_uscita,&e.requisito_precedenza,&e.finale,&e.valore,&e.difficolta);
    return e;
}
