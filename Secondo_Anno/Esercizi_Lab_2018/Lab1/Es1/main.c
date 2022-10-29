#include <stdio.h>
#include <stdlib.h>

#define MAX_TEAMS 20
#define MAX_GAMES 20

int main()
{
    int campionato[MAX_TEAMS][MAX_GAMES];
    int i,j,n,m,max_punti=0;
    int punti[MAX_GAMES];
    int capolista[MAX_GAMES];

    FILE *fp=fopen("mat.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file.\n");
        exit(-1);
    }
    fscanf(fp,"%d%d",&n,&m);
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            fscanf(fp,"%d",&campionato[i][j]);
        }
    }
    //Azzero punti
    for(i=0;i<n;i++)
        punti[i]=0;

    //Per ogni giornata aggiorna il vettore punti per ogni squadra
    //Aggiorna il vettore capolista (ogni volta che una squadra supera il max finisce nel vettore)
    for(i=0;i<m;i++){       //i indica la giornata
        for(j=0;j<n;j++){   //j indica la squadra
            punti[j]+=campionato[j][i]; //squadra j ottiene punti della squadra j nella i-esima giornata
            if(punti[j]>max_punti){
                max_punti=punti[j];
                capolista[i]=j;     //squadra j è la capolista della giornata i
            }
        }
        printf("Giornata %d: capolista: %d \n",i,capolista[i]);
    }
    return 0;
}
