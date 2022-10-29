#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXR 60
#define MAXC 80
#define MAXP 1000

int leggiPagina(char pagina[][MAXC+1],int rmax);
int riconosciParole(char pagina[][MAXC+1],int nr,char *parole[],int pmax);
void ordinaParole(char *parole[],int np);
int confrontaParole(char *p1,char *p2);
int ricercaBinaria(char *parole[],int np,char cerca[]);

int main()
{
    char pagina[MAXR][MAXC+1];
    char *parole[MAXP];
    char cerca[MAXC];

    int nr,np,indice,indicei,indicef,i,trovato;

    nr = leggiPagina(pagina,MAXR);
    np = riconosciParole(pagina,nr,parole,MAXP);
    ordinaParole(parole,np);

    printf("Inserisci la parola da ricercare: ");
    scanf("%s",cerca);
    i=0;
    while(cerca[i++]!='\0'){   //lavora sulla stringa cerca per separare "l'" dal resto
        if(!isalpha(cerca[i])) cerca[i+1]='\0';
    }

    while(strcmp(cerca,"$fine")!=0){
        indice = ricercaBinaria(parole,np,cerca);
        if(indice!=-1){
            indicei=indice-1;
            indicef=indice+1;

            trovato=1;
            while(trovato&&indicei>=0){ //iterazione all'indietro per trovare la prima delle posizioni della parola uguale a quella cercata

                if(confrontaParole((parole[indicei]),cerca)==0) indicei--;
                else trovato=0;
            }
            indicei++;  //compenso perchè diminuisco indice, poi controllo se parola al nuovo indice corrisponde, ma se non corrisponde esco comunque con l'indice diminuito

            trovato=1;
            while(trovato&&indicef<MAXR){
                if(confrontaParole((parole[indicef]),cerca)==0) indicef++;
                else trovato=0;
            }
            indicef--;

            printf("Parola %s trovata in:\n",cerca);
            for(i=indicei;i<=indicef;i++)
                printf("(%d,%d) ",(parole[i]-pagina[0])/(MAXC+1),(parole[i]-pagina[0])%(MAXC+1));   //pagina di 0 è il primo indirizzo della pagina, parole di i è l'indirizzo alla prima lettera della parola trovata
                                                                                                    //sapendo che in memoria ho la matrice di quelle dimensioni mi ricavo gli indici
            printf("\n");
        }
        else printf("Parola non trovata.\n");

        printf("Inserisci la nuova parola da ricercare: ");
        scanf("%s",cerca);
    }

    return 0;
}

int leggiPagina(char pagina[][MAXC+1],int rmax){
    int i,nr;

    FILE *fi;
    if((fi=fopen("sequenze.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file di input\n");
        exit(-1);
    }

    i=0;
    while(fgets(pagina[i++],MAXC,fi)!=NULL)    if(i==rmax) break;    //acquisisci vettore di massimo rmax righe

    nr=i+1; //da indice a numero effettivo di righe

    return nr;
}
int riconosciParole(char pagina[][MAXC+1],int nr,char *parole[],int pmax){
    int i,j,k,np;

    i=0;j=0;k=0;
    while(pagina[i][j]!='\0'){  //fgets inserisce un null dopo che smette di leggere (EOF o \n)
        if(j==0||((!isalpha(pagina[i][j-1]))&&isalpha(pagina[i][j])))   //prima lettera della riga o lettera preceduta da altro carattere incrementano il numero di parole
            parole[k++]=&pagina[i][j];

        if(pagina[i][j]=='\n'){ //vai a capo
            i++;
            j=0;
        }
        else j++;
    }
    np=k;

    return np;
}

void ordinaParole(char *parole[],int np){   //insertion sort che non tiene conto di maiuscole o minuscole
    int i,j;
    char *x;

    for(i=1;i<np;i++){
        x=parole[i];
        j=i-1;
        while(j>=0&&confrontaParole(x,parole[j])<0){    //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
            parole[j+1]=parole[j];  //se parole[i] è minore di quello che lo precede trasla quest'ultimo avanti di uno
            j--;
        }
        parole[j+1]=x;  //piazza parole[i] dopo quello di cui non è minore
    }

    return;
}

int confrontaParole(char *p1,char *p2){

    int i;
    char parola1[MAXC+1];
    char parola2[MAXC+1];

    i=0;
    while(isalpha(p1[i])){
        parola1[i]=tolower(p1[i]); //uso due stringhe ausiliarie in cui copio il valore della parola puntata dal puntatore, la rendo minuscola e la trasformo in stringa aggiungendo il /0
        i++;
    }
    parola1[i]='\0';

    i=0;
    while(isalpha(p2[i])){
        parola2[i]=tolower(p2[i]);
        i++;
    }
    parola2[i]='\0';

    i=0;
    while(parola1[i]==parola2[i]&&parola1[i]!='\0') //se una delle 2 parole finisce prima dell'altra il confronto tra codici ascii funziona comunque (/0 viene prima di tutto nella tabella ASCII)
        i++;                                        //basta un controllo sulla prima parola per evitare che si continui a confrontare anche dopo la fine delle parole
                                                    //equivalente a fare strcmp(parola1,parola2)
    return (parola1[i]-parola2[i]);
}

int ricercaBinaria(char *parole[],int np,char cerca[]){
    int l=0;
    int r=np-1;
    int m;  //indice medio ricerca dicotomica
    int differenza; //risultato della confrontaParole

    while(l<=r){
        m=l+(r-l)/2;
        differenza=confrontaParole(parole[m],cerca);
        if(differenza==0)  //parole di m è un puntatore, k è il k-esimo elemento del vettore puntato da quel puntatore
            return m; //parole[m][k] prima lettera diversa-> quella da confrontare per stabilire se la parola cercata si trova prima o dopo nel vettore

        if(differenza>0)
            r=m-1;    //se la parola intermedia viene dopo la parola cercata: l'indice destro diventa l'estremo di mezzo -1 (cerca nella prima metà)
        else l=m+1;

    }

    return (-1);  //se non ho trovato la parola
}
