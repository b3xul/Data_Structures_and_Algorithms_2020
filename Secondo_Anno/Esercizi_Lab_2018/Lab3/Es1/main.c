#include <stdio.h>
#include <stdlib.h>

#define MAX_DIM 50

typedef struct regione{
    int x,y;
    int length,height,area;
}Regione;

Regione crea_regione(int mat[][MAX_DIM],int nr,int rc,int i,int j);
void stampa_regione(Regione r);
void leggiMatrice(int mat[][MAX_DIM], int max_dim, int* nr, int* nc);
int riconosciRegione(int mat[][MAX_DIM],int nr,int rc,int i,int j,int* b,int* h);

int main(){


    int i,j,nr,nc,b,h,esiste;
    int mat[MAX_DIM][MAX_DIM];
    Regione max_l,max_h,max_a,tmp;

    /*Leggi matrice*/
    leggiMatrice(mat,MAX_DIM,&nr,&nc);

    /*Stampa matrice*/
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

    /*Per ogni elemento della matrice, cerca regione che parta da lì*/
    esiste=0;

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if (riconosciRegione(mat,nr,nc,i,j,&b,&h)) {
            // stampa messaggio per rettangolo con
            // estremo in (r,c), base b e altezza h
                printf("Rettangolo con base=%d e altezza=%d\n",b,h);
                tmp=crea_regione(mat,nr,nc,i,j);
                //stampa_regione(tmp);
                if(!esiste){
                    esiste=1;
                    max_l=max_h=max_a=tmp;
                }
                if(tmp.length>max_l.length)
                    max_l=tmp;
                if(tmp.height>max_h.height)
                    max_h=tmp;
                if(tmp.area>max_a.area)
                    max_a=tmp;
            }
        }
    }

    /*Stampa matrice
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }*/

    printf("Max Base: ");
    stampa_regione(max_l);
    printf("Max Altezza: ");
    stampa_regione(max_h);
    printf("Max Area: ");
    stampa_regione(max_a);
    return 0;
}

int riconosciRegione(int mat[][MAX_DIM],int nr,int rc,int i,int j,int* b,int* h){
    Regione r;
    int k,m;
    r.x=i;
    r.y=j;
    r.height=0;
    r.length=0;
    r.area=0;

    /*Conta lunghezza*/
    k=j;
    while(mat[i][k]==1){
        r.length++;
        if(k!=j)            //Evito di mettere a 2 il primo elemento, così il ciclo sull'altezza può facilmente partire da lì
            mat[i][k]=1;
        k++;
    }
    *b=r.length;

    /*Conta altezza*/
    k=i;
    while(mat[k][j]==1){
        r.height++;
        for(m=j;m<j+r.length;m++) //Mette a 2 anche le celle "in basso a destra" del rettangolo
            mat[k][m]=1;
        k++;
    }
    *h=r.height;

    /*Conta area*/
    r.area=r.height*r.length;

    return (r.area!=0)?1:0;
}

Regione crea_regione(int mat[][MAX_DIM],int nr,int rc,int i,int j){
    Regione r;
    int k,m;
    r.x=i;
    r.y=j;
    r.height=0;
    r.length=0;
    r.area=0;

    /*Conta lunghezza*/
    k=j;
    while(mat[i][k]==1){
        r.length++;
        if(k!=j)            //Evito di mettere a 2 il primo elemento, così il ciclo sull'altezza può facilmente partire da lì
            mat[i][k]=2;
        k++;
    }

    /*Conta altezza*/
    k=i;
    while(mat[k][j]==1){
        r.height++;
        for(m=j;m<j+r.length;m++) //Mette a 2 anche le celle "in basso a destra" del rettangolo
            mat[k][m]=2;
        k++;
    }

    /*Conta area*/
    r.area=r.height*r.length;

    return r;
}

void stampa_regione(Regione r){
    printf("estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",r.x,r.y,r.length,r.height,r.area);
}

void leggiMatrice(int mat[][MAX_DIM], int max_dim, int* nr_p, int* nc_p){
    int i,j;
    FILE* fp;

    if((fp=fopen("mat.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file");
        exit(-1);
    }

    fscanf(fp,"%d%d",nr_p,nc_p);
    if(*nr_p>50||*nc_p>50||*nr_p<0||*nc_p<0){
        fprintf(stderr,"Errore nelle dimensioni della matrice!");
        exit(-2);
    }

    for(i=0;i<*nr_p;i++){
        for(j=0;j<*nc_p;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
}
