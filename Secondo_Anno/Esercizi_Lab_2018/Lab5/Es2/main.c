#include <stdio.h>
#include <stdlib.h>

int** malloc2dR(int* nr, int* nc, FILE*fp);
void malloc2dP(int*** m,int* nr, int* nc, FILE*fp);
void separa(int **mat, int nr, int nc, int** nere, int** bianche, int* dimN, int* dimB);
void free2d(int** m,int nr,int nc);
void print1d(int* a, int n);
void print2d(int** mat,int nr,int nc);

int main()
{
    int** mat;
    int nr,nc;
    int* nere;
    int* bianche;
    int dimN,dimB;

    FILE* fp;

    fp=fopen("mat1.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Impossibile aprire file.\n");
        exit(-1);
    }

    mat=malloc2dR(&nr,&nc,fp);
    //malloc2dP(&mat,&nr,&nc,fp);

    print2d(mat,nr,nc);

    separa(mat,nr,nc,&nere,&bianche,&dimN,&dimB);   //malloc1dP

    printf("Nere:\n");
    print1d(nere,dimN);
    printf("Bianche:\n");
    print1d(bianche,dimB);


    free(bianche);
    free(nere);
    free2d(mat,nr,nc);

    return 0;
}

int** malloc2dR(int* nr, int* nc, FILE*fp){

    int** mat;
    int i,j;

    fscanf(fp,"%d%d",nr,nc);

    /*Alloco*/
    mat=(int**)malloc((*nr)*sizeof(int*));
    for(i=0;i<(*nr);i++)
        mat[i]=(int*)malloc((*nc)*sizeof(int));

    /*Riempio*/
    for(i=0;i<(*nr);i++)
        for(j=0;j<(*nc);j++)
            fscanf(fp,"%d",&mat[i][j]);

    return mat;
}

void malloc2dP(int*** m,int* nr, int* nc, FILE*fp){

    int** mat;
    int i,j;

    fscanf(fp,"%d%d",nr,nc);

    /*Alloco*/
    mat=(int**)malloc((*nr)*sizeof(int*));
    for(i=0;i<(*nr);i++)
        mat[i]=(int*)malloc((*nc)*sizeof(int));

    /*Riempio*/
    for(i=0;i<(*nr);i++)
        for(j=0;j<(*nc);j++)
            fscanf(fp,"%d",&mat[i][j]);

    (*m)=mat;
}

void separa(int **mat, int nr, int nc, int** nere, int** bianche, int* dimN, int* dimB){
    //nr*nc pari: 4*4/2=16/2=8 nere (e 8 bianche) ->nr*nc/2
    //nr*nc dispari: 3x3/2=9/2=4, ma in realtà 5 nere (e 4 bianche)->nr*nc/2+1
    //se nr*nc pari: stesso numero di bianche e nere, altrimenti 1 nera in più

    *dimB=(nr*nc)/2;

    if((nr*nc)%2==0)
        *dimN=*dimB;
    else
        *dimN=*dimB+1;


    int* n=(int*)malloc((*dimN)*sizeof(int));
    int* b=(int*)malloc((*dimB)*sizeof(int));

    int i,j,m=0,q=0;  //Basta un solo indice per bianche e nere perchè crescono di 1 alla volta (cresce solo dopo che anche bianche ha letto il suo numero

    for(i=0;i<nr;i++){    //Scorro la matrice
        for(j=0;j<nc;j++){
            if((i+j)%2==0)     //indici pari->nere
                n[m++]=mat[i][j];      //i/nc=numero di riga, i/nr=numero di colonna
            else
                b[q++]=mat[i][j];
        }
    }

    (*nere)=n;
    (*bianche)=b;
}

void free2d(int** m,int nr,int nc){
    int i;
    for(i=0;i<nr;i++)
        free(m[i]);

    free(m);
}

void print1d(int* a, int n){
    int i;
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}

void print2d(int** mat,int nr,int nc){
    int i,j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }

}
