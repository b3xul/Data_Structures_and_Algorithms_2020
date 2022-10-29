#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXC 50*2 //50 numeri, altrettanti spazi o a capo
//Define semplicemente sostituisce nel testo, non è una variabile globale ma è solo una costante simbolica

void leggiMatrice(int Matrice[][MAXC],const int MAXR,int *nr,int *nc);

int riconosciRegione(int M[][MAXC],int nr,int nc, int r,int c,int *b,int *h);

int main()
{
    const int MAXR=50;
    int nr,nc,i,j,r,c,b,h;
    int M[MAXR][MAXC];
    int contatore_regioni=0;

    leggiMatrice(M,MAXR,&nr,&nc);

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(M[i][j]==1){   //cerca inizio regione
                r=i;
                c=j;
                contatore_regioni++;
                if(riconosciRegione(M,nr,nc,r,c,&b,&h)){
                    printf("Regione %d: estr. sup. SX = <%d,%d> ",contatore_regioni,r,c);
                    printf("b = %d, ",b);
                    printf("h = %d, ",h);
                    printf("Area = %d\n",b*h);
                }
            }
        }
    }

    return 0;
}

void leggiMatrice(int Matrice[][MAXC],const int MAXR,int *nr,int *nc){
    int i,j;
    char ch;

    FILE *fi;
    if((fi=fopen("Matrice.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura file.\n");
        exit(-1);
    }

    j=0;
    while(i<MAXR&&fscanf(fi,"%c",&ch)!=EOF)
            if(isdigit(ch)){
                Matrice[i][j]=(int)ch-'0';
                j++;
            }
            else if(ch=='\n'){
                i++;
                j=0;
            }

    (*nr)=i+1;
    (*nc)=j+1;

    fclose(fi);

    return;
}

int riconosciRegione(int M[][MAXC],int nr,int nc, int r,int c,int *b,int *h){
    int i,j;

    *b=0;
    *h=0;

    i=r;
    j=c;

    while(M[i][j]==1&&i<nr){
        while(M[i][j]==1&&j<nc){
            M[i][j]=2;    //per evitare di contare due volte la stessa sequenza su più righe
            j++;
        }
        *b=j-c;              //lunghezza base
        j=c;                //re-inizializzo j
        *h=*h+1;                //aumento lunghezza altezza
        i++;                //aumento riga
    }

    if(i>r||j>c)    return 1;

    return 0;
}
