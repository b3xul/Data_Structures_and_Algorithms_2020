#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_DIM 30

void ruota(int V[MAX_DIM], int N, int P, int dir);
void ruota_wrapper(int mat[MAX_DIM][MAX_DIM], char selettore[8], int indice, char direzione[4], int P, int nr, int nc);
void stampa_mat(int mat[MAX_DIM][MAX_DIM],int nr,int nc);

int main()
{
    int mat[MAX_DIM][MAX_DIM];
    int i,j,nr,nc,indice,posizioni,end=0;
    char selettore[8];
    char direzione[9];

    /*Lettura matrice*/
    FILE *fp=fopen("mat.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file.\n");
        exit(-1);
    }
    fscanf(fp,"%d%d",&nr,&nc);
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }

    while(!end){
        printf("Inserire <selettore> <indice> <direzione> <posizioni>: ");
        scanf("%s %d %s %d",selettore,&indice,direzione,&posizioni);
        if(!strcmp(selettore,"fine") || indice < 0 || indice > nr || indice > nc)
            end=1;
        else{
            indice--;
            ruota_wrapper(mat,selettore,indice,direzione,posizioni,nr,nc);
            stampa_mat(mat,nr,nc);
        }
    }

    return 0;
}

void ruota_wrapper(int mat[MAX_DIM][MAX_DIM], char selettore[8], int indice, char direzione[9], int P, int nr, int nc){
    int* V_R;
    int V_C[MAX_DIM];
    int N,dir,i;

    if(strcmp(direzione,"su")==0||strcmp(direzione,"sinistra")==0)
        dir=1;
    else
        dir=-1;

    if(!strcmp(selettore,"riga")){  //riga
        N=nc;
        P=P%N;
        /*for(i=0;i<nc;i++)
            V[i]=mat[indice][i];
        ruota(V,N,P,dir);
        for(i=0;i<nc;i++)
            mat[indice][i]=V[i];
        */
        V_R=&(mat[indice][0]);
        ruota(V_R,N,P,dir);
    }
    else{       //colonna
        N=nr;
        P=P%N;
        for(i=0;i<nr;i++)
            V_C[i]=mat[i][indice];
        ruota(V_C,N,P,dir);
        for(i=0;i<nr;i++)
            mat[i][indice]=V_C[i];
    }
}

void ruota(int V[MAX_DIM], int N, int P, int dir) {
  int tmpVet[MAX_DIM], i;
  //DIR: 1 SX(SU)
  //    -1:DX (GIU)
  if (dir == -1) {
    /* scambia direzione: P spostamenti a DX sono equivalenti a N-P a SX */
    P = N-P;
  }
  /* salvo i primi P elementi di V nel vettore temporaneo */
  for (i=0; i<P; i++) {
    tmpVet[i] = V[i];
  }
  /* sposta di P posizioni a sinistra */
  for (i=0; i<N-P; i++) {
    V[i] = V[i+P];
  }
  /* ricopia a partire da N-P+i  l'intervallo salvato nel vettore temporaneo */
  for (i=0; i<P; i++) {
    V[N-P+i] = tmpVet[i];
  }

}

void stampa_mat(int mat[MAX_DIM][MAX_DIM],int nr,int nc){
    int i,j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}
