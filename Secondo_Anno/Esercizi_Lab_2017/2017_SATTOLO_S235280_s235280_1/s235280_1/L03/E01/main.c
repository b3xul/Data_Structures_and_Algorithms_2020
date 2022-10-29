#include <stdio.h>
#include <stdlib.h>
#define MAXR 50
#define MAXC 50

typedef struct regione{
    int inizioi;int inizioj;int b;int h;int Area;
}regione;

void analizzaregione(int mat[MAXR][MAXC],regione a, int contatore_regioni);

int main()
{
    FILE *fi;
    if((fi=fopen("Matrice.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura file.\n");
        return -1;
    }

    int nr,nc,i,j;
    int mat[MAXR][MAXC];
    int contatore_regioni=0;
    regione a;

    fscanf(fi,"%d %d",&nr,&nc);
    for(i=0;i<nr;i++){  //leggi e stampa matrice
        for(j=0;j<nc;j++){
            fscanf(fi,"%d",&mat[i][j]);
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(mat[i][j]==1){   //cerca inizio regione
                a.inizioi=i;
                a.inizioj=j;
                contatore_regioni++;
                analizzaregione(mat,a,contatore_regioni);
            }
        }
    }

    return 0;
}

void analizzaregione(int mat[MAXR][MAXC],regione a, int contatore_regioni){

    int i,j;

    printf("Regione %d: estr. sup. SX = <%d,%d> ",contatore_regioni,a.inizioi,a.inizioj);

    a.b=0;
    a.h=0;

    i=a.inizioi;
    j=a.inizioj;

    while(mat[i][j]==1&&i<MAXR){
        while(mat[i][j]==1&&j<MAXC){
            mat[i][j]=2;    //per evitare di contare due volte la stessa sequenza su più righe
            j++;
        }
        a.b=j-a.inizioj;    //lunghezza base
        j=a.inizioj;        //re-inizializzo j
        a.h++;              //aumento lunghezza altezza
        i++;                //aumento riga
    }
    printf("b = %d, ",a.b);

    printf("h = %d, ",a.h);

    a.Area=a.b*a.h;
    printf("Area = %d\n",a.Area);

    return;
}
