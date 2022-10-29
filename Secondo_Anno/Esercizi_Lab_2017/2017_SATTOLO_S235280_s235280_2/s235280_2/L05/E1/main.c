#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SMAX 25

int N;

typedef struct Data{
    int giorno;
    int mese;
    int anno;
}Data;

typedef struct info{
    char *v_codice;
    char *v_nome;
    char *v_cognome;
    char *v_categoria;
    Data data;
    int ore;
}atleta;

typedef enum{
    o_data,o_codice,o_cognome
}Ordinamenti;

void contaAtleti(void);
atleta* allocaAtleti(void);
void inizializzaAtleti(atleta v[]);

void menu(atleta v[]);

int ordinavett(int scelta,atleta v[]);
int confrontaAtleti_Data(atleta *a,atleta *b);
int confrontaAtleti_Codice(atleta *a,atleta *b);
int confrontaAtleti_Cognome(atleta *a,atleta *b);

int stampaAtleti(int scelta, atleta v[]);

int stampaCategorie(atleta v[]);
int confrontaAtleti_Categoria(atleta *a,atleta *b);

int ricercaAtleta(int ord,int scelta,atleta v[],char cerca[],int **occ);
int Dicotomica(int op,atleta v[],atleta wrap,int *occ,int *k);
int Lineare(int op,atleta v[],atleta wrap,int *occ,int *k);
int confrontaAtleti_Cognome2(atleta v[],atleta *wrap);

void stampaAtleta(atleta v[],int pos);

void liberaAtleti(atleta v[]);

int main()
{
    contaAtleti();

    atleta *v_atleti;   //vettore di struct

    v_atleti=allocaAtleti(); //alloca un vettore da N struct

    inizializzaAtleti(v_atleti);

    menu(v_atleti);

    liberaAtleti(v_atleti);

    return 0;
}

void contaAtleti(){

    FILE *fi;
    int n_globale;

    if((fi=fopen("atleti.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file atleti.txt");
        exit(-1);
    }

    fscanf(fi,"%d",&n_globale);
    N=n_globale;

    fclose(fi);

    return;
}
atleta *allocaAtleti(void){

    atleta *v_atleti;
    v_atleti=(atleta *)malloc(N*sizeof(atleta));    //alloca lo spazio necessario a far stare la struct in v_atleti che è un vettore di struct (primo indirizzo)
    if(v_atleti==NULL)  exit(-1);

    return v_atleti;
}

void inizializzaAtleti(atleta v[]){

    FILE *fi;

    fi=fopen("atleti.txt","r"); //non faccio controllo perchè tanto sarebbe uscito prima
    fscanf(fi,"%*d");   //butto la prima riga del file perchè non mi serve

    int i;

    char codice[SMAX+1];
    char nome[SMAX+1];
    char cognome[SMAX+1];
    char categoria[SMAX+1];

    for(i=0;i<N;i++){

        fscanf(fi,"%s %s %s %s %d/%d/%d %d",codice,cognome,nome,categoria,&v[i].data.giorno,&v[i].data.mese,&v[i].data.anno,&v[i].ore);
                                        //v[i] struct atleta INTERA, accedo al campo tramite '.'
        v[i].v_codice=(char *)malloc((strlen(codice)+1)*sizeof(char));
        if(v[i].v_codice==NULL)  exit(-2);
        strcpy(v[i].v_codice,codice);
                                        //v[i].v_codice puntatore, ci alloco una stringa della lunghezza che mi serve
        v[i].v_cognome=(char *)malloc((strlen(cognome)+1)*sizeof(char));
        if(v[i].v_cognome==NULL)  exit(-3);
        strcpy(v[i].v_cognome,cognome);

        v[i].v_nome=(char *)malloc((strlen(nome)+1)*sizeof(char));
        if(v[i].v_nome==NULL)  exit(-4);
        strcpy(v[i].v_nome,nome);

        v[i].v_categoria=(char *)malloc((strlen(categoria)+1)*sizeof(char));
        if(v[i].v_categoria==NULL)  exit(-5);
        strcpy(v[i].v_categoria,categoria);

    }
        //come le libero queste? for i..N free(v[i]->v_codice)? no perchè parte di una struct, basta liberare il puntatore che lo punta?

    return;
}

void menu(atleta v[]){
    int op;
    int scelta;
    int ordinamento=-1;
    int continua=1;
    int *occ=malloc(sizeof(int));
    //atleta **p_anagrafica;
    char cerca[SMAX];

    while(continua){
        printf("Operazioni eseguibili (inserire il numero relativo):\n");
        printf("1. stampa, a scelta se a video o su file, dei contenuti dell'anagrafica\n2. ordinamento del vettore per data di nascita ascendente\n3. ordinamento del vettore per codice atleta\n4. ordinamento del vettore per cognome (e nome in caso di omonimi)\n5. stampa a video degli atleti, divisi per categoria sportiva\n6. aggiornamento del monte ore settimanali\n7. ricerca di un atleta per codice\n8. ricerca di un atleta per cognome (anche parziale).\n0. terminare l'esecuzione del programma\n");
        scanf("%d",&op);

        switch(op){
            case 1:
                printf("0 per stampare anagrafica su video, 1 per stampare su file: ");
                scanf("%d",&scelta);
                stampaAtleti(scelta,v);
                break;
            case 2:
            case 3:
            case 4:
                ordinamento=ordinavett(op,v);
                break;
            case 5:
                //p_anagrafica=allocaVettore(v);
                ordinamento=stampaCategorie(v);
                break;
            case 6:
                printf("Inserisci il nome completo dell'atleta a cui vuoi modificare il monte ore: ");
                scanf("%s",cerca);
                if(ricercaAtleta(ordinamento,op,v,cerca,occ)!=-1){
                    printf("Inserisci il nuovo monte ore settimanale: ");
                    scanf("%d",&(v[occ[0]].ore));
                    stampaAtleta(v,occ[0]);
                }
                break;
            case 7:
                printf("Inserire codice da cercare: ");
                scanf("%s",cerca);
                ricercaAtleta(ordinamento,op,v,cerca,occ);

                break;
            case 8:
                printf("Inserire cognome (anche parziale) da cercare: ");
                scanf("%s",cerca);
                ricercaAtleta(ordinamento,op,v,cerca,occ);
                break;
            case 0:
                continua=0;
                break;
            default:
                printf("Scelta non disponibile!\n");
        }
    }
    return;
}

int stampaAtleti(int scelta, atleta v[]){
    FILE *fo;
    int i;

    switch(scelta){
        case 0:
            for(i=0;i<N;i++)
                stampaAtleta(v,i);
            break;
        case 1:
            fo=fopen("Anagrafica.txt","w");
            for(i=0;i<N;i++)    fprintf(fo,"%s %s %s %s %d/%d/%d %d\n",v[i].v_codice,v[i].v_nome,v[i].v_cognome,v[i].v_categoria,v[i].data.giorno,v[i].data.mese,v[i].data.anno,v[i].ore);
            break;
        default:
            printf("Scelta non valida!\n");
            return 0;
    }
    printf("\n");

    return 1;
}

int ordinavett(int scelta,atleta v[]){
    scelta=scelta-2;
    int i,j;
    atleta x;

    switch(scelta){
        case o_data:    //insertion sort

            for(i=1;i<N;i++){
                x=v[i];
                j=i-1;                      //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
                while(j>=0&&(confrontaAtleti_Data(&x,&v[j])<0)){
                    v[j+1]=v[j];            //se A[i] è minore di quello che lo precede trasla quest'ultimo avanti di uno
                    j--;
                }
                v[j+1]=x;                   //piazza A[i] dopo quello di cui non è minore
            }

            return o_data;

        case o_codice:

            for(i=1;i<N;i++){
                x=v[i];
                j=i-1;                      //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
                while(j>=0&&(confrontaAtleti_Codice(&x,&v[j])<0)){
                    v[j+1]=v[j];            //se A[i] è minore di quello che lo precede trasla quest'ultimo avanti di uno
                    j--;
                }
                v[j+1]=x;                   //piazza A[i] dopo quello di cui non è minore
            }

            return o_codice;

        case o_cognome:

            for(i=1;i<N;i++){
                x=v[i];
                j=i-1;                      //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
                while(j>=0&&(confrontaAtleti_Cognome(&x,&v[j])<0)){
                    v[j+1]=v[j];            //se A[i] è minore di quello che lo precede trasla quest'ultimo avanti di uno
                    j--;
                }
                v[j+1]=x;                   //piazza A[i] dopo quello di cui non è minore
            }

            return o_cognome;

        default:
            printf("Errore inaspettato! Riprova:\n");
    }

    return -1;
}

int confrontaAtleti_Data(atleta *a,atleta *b){

    if((a->data.anno)!=(b->data.anno)) return (a->data.anno)-(b->data.anno);
    else if((a->data.mese)!=(b->data.mese)) return (a->data.mese)-(b->data.mese);
    else if((a->data.giorno)!=(b->data.giorno)) return (a->data.giorno)-(b->data.giorno);

    return 0;
}

int confrontaAtleti_Codice(atleta *a,atleta *b){

    return strcmp(a->v_codice,b->v_codice);
}

int confrontaAtleti_Cognome(atleta *a,atleta *b){

    int c1=strcmp(a->v_cognome,b->v_cognome);

    if(c1==0)   return strcmp(a->v_nome,b->v_nome);

    return c1;
}

int stampaCategorie(atleta v[]){
    int i,j;
    atleta x;

    for(i=1;i<N;i++){
        x=v[i];
        j=i-1;                      //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
        while(j>=0&&(confrontaAtleti_Categoria(&x,&v[j])<0)){
            v[j+1]=v[j];            //se A[i] è minore di quello che lo precede trasla quest'ultimo avanti di uno
            j--;
        }
        v[j+1]=x;                   //piazza A[i] dopo quello di cui non è minore
    }
    stampaAtleti(0,v);

    return 3;   //ordinamento
}

int confrontaAtleti_Categoria(atleta *a,atleta *b){

    return strcmp(a->v_categoria,b->v_categoria);
}

int ricercaAtleta(int ord,int op,atleta v[],char cerca[],int **occ){
    op=op-6; //in questo modo op varrà sicuramente 1 per il codice e 2 per il cognome, esattamente i valori associati a o_codice e o_cognome

    int trovato;
    atleta wrap;
    int *k=malloc(sizeof(int));
    int i;

    if(op==1){  //Ricerca per codice
        wrap.v_codice=(char *)malloc((strlen(cerca)+1)*sizeof(char));
        if(wrap.v_codice==NULL)  exit(-6);
        strcpy(wrap.v_codice,cerca);
        if(ord==op)
            trovato=Dicotomica(op,v,wrap,occ,k);
        else
            trovato=Lineare(op,v,wrap,occ,k);
        if(trovato!=-1&&op!=0)
            stampaAtleta(v,trovato);
    }

    else {   //ricerca per cognome
        wrap.v_cognome=(char *)malloc((strlen(cerca)+1)*sizeof(char));
        if(wrap.v_cognome==NULL)  exit(-7);
        strcpy(wrap.v_cognome,cerca);
        if(ord==op)
            trovato=Dicotomica(op,v,wrap,occ,k);
        else
            trovato=Lineare(op,v,wrap,occ,k);
        if(trovato!=-1&&op!=0){
            for(i=0;i<(*k);i++)
                stampaAtleta(v,occ[i]);
        }
    }

    if(trovato==-1)
        printf("Nessun atleta trovato!\n");


    return trovato;
}

int Dicotomica(int op,atleta v[],atleta wrap,int *occ,int *k){
    int l=0;
    int r=N-1;
    int m;  //indice medio ricerca dicotomica
    int differenza; //risultato della confrontaParole

    int dim=1;
    (*k)=0;

    if(op==1){
        while(l<=r){
            m=l+(r-l)/2;
            differenza=confrontaAtleti_Codice(&v[m],&wrap);
            if(differenza==0)
                return m;
            if(differenza>0)
                r=m-1;
            else l=m+1;
        }
    }
    else{
        while(l<=r){
            m=l+(r-l)/2;
            differenza=confrontaAtleti_Cognome2(&v[m],&wrap);
            if(differenza==0){
                if((*k)==dim){
                    dim=2*dim;
                    realloc(occ,dim*sizeof(int));
                }
                occ[(*k)]=m;
                (*k)++;
            }
            if(differenza>0)
                r=m-1;    //se la parola intermedia viene dopo la parola cercata: l'indice destro diventa l'estremo di mezzo -1 (cerca nella prima metà)
            else l=m+1;
        }
    }
    if((*k)==0)return (-1);  //se non ho trovato la parola
    else return (*k);
}

int Lineare(int op,atleta v[],atleta wrap,int *occ,int *k){
    int i;
    int dim=1;
    (*k)=0;

    if(op==1){
        for(i=0;i<N;i++){
            if(confrontaAtleti_Codice(&v[i],&wrap)==0)  return i;
        }
    }
    else{
        for(i=0;i<N;i++){
            if(confrontaAtleti_Cognome2(&v[i],&wrap)==0){
                if((*k)==dim){
                    dim=2*dim;
                    realloc(occ,dim*sizeof(int));
                }
                occ[(*k)]=i;
                (*k)++;
            }

        }
    }
    if((*k)==0)return (-1);  //se non ho trovato la parola
    else return (*k);
}

int confrontaAtleti_Cognome2(atleta *v,atleta *w){

    int c1=strncmp(v->v_cognome,w->v_cognome,strlen(w->v_cognome));

    return c1;
}

void stampaAtleta(atleta v[],int pos){

    fprintf(stdout,"%s %s %s %s %d/%d/%d %d\n",v[pos].v_codice,v[pos].v_nome,v[pos].v_cognome,v[pos].v_categoria,v[pos].data.giorno,v[pos].data.mese,v[pos].data.anno,v[pos].ore);

    return;
}

void liberaAtleti(atleta v[]){

    int i;

    for(i=0;i<N;i++){
        free(v[i].v_codice);
        free(v[i].v_nome);
        free(v[i].v_cognome);
        free(v[i].v_categoria);
    }

    free(v);

    return;
}
