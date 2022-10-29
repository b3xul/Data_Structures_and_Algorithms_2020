#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 10

int main()
{
    int matrice [N][M];
    int numero;
    char spazio;
    int i=0;
    int j=0;
    int flag=1;
    int num_righe=0;
    int num_colonne=0;
    int riga;
    int colonna;
    int n;
    int m;

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            matrice[i][j]=0;
        }
    }
    i=0;
    j=0;
    printf("Inserisci una matrice di interi, mettendo uno spazio tra i vari numeri della riga:\n");

    while(flag==1&&scanf("%d%c",&numero,&spazio)!=EOF){
        matrice[i][j]=numero;
        switch(spazio){
            case ' ':
                j++;
                break;

            case '\n':
                i++;
                if(j>num_colonne) num_colonne=j;
                j=0;
                break;

            default: printf("Formato carattere non valido\n");
            }

        if(i==N||j==M){
            printf("Dimensioni matrice eccessive.\n");
            flag=0;
        }
    }
    num_righe=i;

    if(flag){
        printf("La tua matrice attuale e':\n");
        for(i=0;i<num_righe;i++){
            for(j=0;j<num_colonne+1;j++){
                printf("%d ",matrice[i][j]);
            }
            printf("\n");
        }
        do{ printf("Dimmi riga e colonna da dove iniziare ad azzerare la sottomatrice da te scelta: ");
            scanf("%d%d",&riga,&colonna);
            if(riga>num_righe||colonna>num_colonne||riga<0||colonna<0){
                printf("Posizione non disponibile.\n");
                flag=0;
                }
            else {
                printf("Il numero di partenza sara' dunque il %d\n",matrice[riga][colonna]);
                flag=1;
            }
            }
        while(!flag);

        do{ printf("Dimmi di quante righe e colonne e' composta la tua sottomatrice: ");
            scanf("%d%d",&n,&m);
            if(riga+n>num_righe||colonna+m>num_colonne){
                printf("Sottomatrice troppo grande.\n");
                flag=0;
                }
            else flag=1;
            }
        while(!flag);

        for(i=riga;i<riga+n;i++){
            for(j=colonna;j<colonna+m;j++){
                matrice[i][j]=0;
            }
        }

        printf("La tua nuova matrice e':\n");
        for(i=0;i<num_righe;i++){
            for(j=0;j<num_colonne+1;j++){
                printf("%d ",matrice[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
