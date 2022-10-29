#include <stdio.h>
#include <stdlib.h>
#define N 3

int giocapc(char [][N],int);
int giocaumano(char [][N],int);

int main()
{
    char griglia[N][N];
    int i,j;
    int inizio=0; //chi inizia//
    int vincitore=0; //chi vince//


    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            griglia[i][j]=' ';
        }
    }
    //Griglia vuota pronta//

    printf("Chi deve iniziare a giocare? (1=Pc 2=Umano) -> ");

    while(inizio!=1&&inizio!=2){ //controlla chi inizia//
        scanf("%d",&inizio);
        switch(inizio){
            case 1: vincitore=giocapc(griglia,N);
                break;

            case 2: vincitore=giocaumano(griglia,N);
                break;

            default: printf("Inserisci 1 oppure 2, nient'altro!\n");
        }
    }



    switch(vincitore){ //guarda chi ha vinto//
    case 1:
        printf("Vince la macchina!!\n");
        break;
    case 2:
        printf("Vince l'umano!!\n");
        break;
    default:
        printf("Sembra proprio che questo sia un pareggio!\n");
    }
    return 0;
}

int giocapc(char griglia[][N],int n){
    return 1;
}

int giocaumano(char griglia[][N],int n){ //prende la griglia (con dimensione perchè matrice di caratteri), e restituisce il vincitore se in quel turno fa tris, e altrimenti richiama la funzione dell'avversario

    int i,j,k=0,riga,colonna;
    int tris=0; //flag//

    //stampa griglia//
    for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                printf("%c ",griglia[i][j]);
                if(j<N-1) printf("|");
            }
            printf("\n");
    }


    printf("Dimmi riga e colonna dove mettere la crocetta: ");

    /*while(fscanf(stdin,"%d%d",&riga,&colonna)!=2){
        printf("Scrivi giusto grazie!\n");
    };      ♥ ♥ ♥ */

    riga=0,colonna=0; //solo per entrare nel while la prima volta

    while(riga<=0||riga>N||colonna<=0||colonna>N){ //controllo che la posizione sia FUORI dalla griglia e nel caso continuo a chiedere, altrimenti inserisco//
        scanf("%d%d",&riga,&colonna);

        if(riga>0&&riga<=N&&colonna>0&&colonna<=N) griglia[riga-1][colonna-1]='x';
        else printf("Posizione fuori dalla griglia!\n");
    }

    riga=riga-1; //trasformo in indici per comodità//
    colonna=colonna-1;

    //stampa nuova griglia//
    for(i=0;i<N&&!tris;i++){
        for(j=0;j<N;j++){
                printf("%c ",griglia[i][j]);
                if(j<N-1) printf("|");
            }
            printf("\n");
    }

    //controlla se ha fatto tris//
    k=0;                            //ogni volta riazzera contatore//
    for(i=riga,j=0;j<N&&!tris;j++){ //controlla riga//
        if(griglia[i][j]=='x'){
            k++;
        }
        if(k==3) tris=1;
    }

    k=0;
    for(i=0,j=colonna;i<N&&!tris;i++){ //controlla colonna//
        if(griglia[i][j]=='x'){
            k++;
        }
        if(k==3) tris=1;
    }

    k=0;
    if(riga+colonna==N-1&&!tris){       //controlla diagonale da in alto a destra a in basso a sinistra se indice riga+indice colonna=N-1//
        for(i=0,j=N-1;i<N&&j>=0;i++,j++){
                if(griglia[i][j]=='x'){
                    k++;
                }
                if(k==3) tris=1;
            }
    }
    k=0;
    if(riga-colonna==0&&!tris){         //controlla diagonale da in alto a sinistra a in basso a destra se indice riga=indice colonna//
        for(i=0,j=0;i<N&&j<N;i++,j++){
                if(griglia[i][j]=='x'){
                    k++;
                }
                if(k==3) tris=1;
            }
    }

    if(tris) return 2; //vince umano//
    else return giocapc(griglia,n); //turno del pc//
}
