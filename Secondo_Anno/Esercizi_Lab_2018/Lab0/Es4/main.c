#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DIM 20

int main(int argc, char* argv[]){
 FILE* fp;
 char filename[21];
 int i,j,k,m,max_k,max_m,nr,nc,min,sum,tot,dim,end;
 int mat[MAX_DIM][MAX_DIM];
 scanf("%s",filename);

 if((fp=fopen(filename,"r"))==NULL){
  fprintf(stderr,"Errore apertura file");
  exit(-1);
 }

 fscanf(fp,"%d%d",&nr,&nc);
 min=(nr<=nc)?nr:nc;
 for(i=0;i<nr;i++){
  for(j=0;j<nc;j++){
   fscanf(fp,"%d",&mat[i][j]);
  }
 }
 end=0;

 while(!end){
  printf("Inserisci dim sottomatrice: ");
  scanf("%d", &dim);
  if(dim>0 && dim<=min){
    //nr=3, nc=6
    //dim=2, min=3
    tot=INT_MIN;
   for(k=0;k<=nr-dim;k++){ //riga di partenza= 0 o 1 (da 0 a nr-dim compreso)
    for(m=0;m<=nc-dim;m++){    //colonna di partenza= 0,1,2,3,4 (da 0 a nc-dim compreso)
    sum=0;
     for(i=0;i<dim;i++){        //stampa matrice quadrata di dimensione dim
      for(j=0;j<dim;j++){
       printf("%d ",mat[k+i][m+j]);
       sum+=mat[k+i][m+j];
      }
      printf("\n");
     }
     printf("-------------\n");
     if(sum>=tot){
        tot=sum;
        max_k=k;
        max_m=m;
     }
    }
   }
   printf("Matrice con somma massima (=%d)\n",tot);
   for(i=max_k;i<max_k+dim;i++){        //stampa matrice quadrata di dimensione dim
      for(j=max_m;j<max_m+dim;j++){
       printf("%d ",mat[i][j]);
      }
      printf("\n");
   }
  }
  else
   end=1;
  }
 return 0;
}
