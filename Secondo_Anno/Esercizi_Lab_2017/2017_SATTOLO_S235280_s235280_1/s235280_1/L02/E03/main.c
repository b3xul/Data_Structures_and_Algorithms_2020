#include <stdio.h>
#include <stdlib.h>
#define MAXR 20
#define MAXC 20

int calcolasottomatrice(int inizioi,int finei,int inizioj,int finej,int mat[MAXR][MAXC]);

int main()
{
    FILE *fi;
    if((fi=fopen("Matrice.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura file.\n");
        return -1;
    }


    int nr,nc,i,j,r,c,no=0,ne=0,so=0,se=0;
    int mat[MAXR][MAXC];

    fscanf(fi,"%d %d",&nr,&nc);
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            fscanf(fi,"%d",&mat[i][j]);
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

    printf("Inserisci indici (a partire da zero) di riga e colonna da cui partire per cui sommare le matrici parziali\n(indici non validi per terminare): ");
    scanf("%d %d",&r,&c);

    while(r>=0&&c>=0&&r<nr&&c<nc){
        //somma sottomatrici
        printf("NO = ");
        no=calcolasottomatrice(0,r,0,c,mat);
        printf("= %d\n",no);

        printf("NE = ");
        ne=calcolasottomatrice(0,r,c+1,nc,mat);
        printf("= %d\n",ne);

        printf("SO = ");
        so=calcolasottomatrice(r+1,nr,0,c,mat);
        printf("= %d\n",so);

        printf("SE = ");
        se=calcolasottomatrice(r+1,nr,c+1,nc,mat);
        printf("= %d\n",se);
    printf("Inserisci riga e colonna da cui partire per cui sommare le matrici parziali (indici non validi per terminare): ");
    scanf("%d %d",&r,&c);
    }

    return 0;
}

int calcolasottomatrice(int inizioi,int finei,int inizioj,int finej,int mat[MAXR][MAXC]){
    int i,j;
    int somma=0;

    for(i=inizioi;i<finei;i++){
        for(j=inizioj;j<finej;j++){
            somma=somma+mat[i][j];
            printf((mat[i][j]>=0)?"+":"");
            printf("%d ",mat[i][j]);
        }
    }

    return somma;
}
