#include <stdio.h>
#include <stdlib.h>
#define N 2
int gioca1(char [][N],int,char,char);
int gioca2(char [][N],int,char,char);

int main()
{
    char griglia[N][N];
    int i,j;
    int inizio=0; //chi inizia//
    int vincitore=0; //chi vince//
    char giocatore1[50];
    char giocatore2[50];
    char simbolo1;
    char simbolo2;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            griglia[i][j]=' ';
        }
    }
    //Griglia vuota pronta//
    printf("Inserisci il nome del primo contendente :\n");
    scanf("%s",giocatore1);
    getchar();
    printf("Che simbolo vuoi?:\n");
    simbolo1=getchar();
    printf("Inserisci il nome del secondo contendente :\n");
    scanf("%s",giocatore2);
    getchar();
    printf("Che simbolo vuoi?:\n");
    simbolo2=getchar();

    printf("Chi inizia? (1=%s 2=%s) -> ",giocatore1,giocatore2);

    while(inizio!=1&&inizio!=2){ //controlla chi inizia//
        scanf("%d",&inizio);
        switch(inizio){
            case 1: vincitore=gioca1(griglia,N,simbolo1,simbolo2);
                break;

            case 2: vincitore=gioca2(griglia,N,simbolo1,simbolo2);
                break;

            default: printf("Inserisci 1 oppure 2, nient'altro!\n");
        }
    }

    for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                printf("%c ",griglia[i][j]);
                if(j<N-1) printf("|");
            }
            printf("\n");
    }


    switch(vincitore){ //guarda chi ha vinto//
    case 1:
        printf("Vince %s!!\n",giocatore1);
        break;
    case 2:
        printf("Vince %s!!\n",giocatore2);
        break;
    default:
        printf("Sembra proprio che questo sia un pareggio!\n");
    }
    return 0;
}


int gioca1(char griglia[][N],int n,char simbolo1,char simbolo2){ //prende la griglia (con dimensione perchè matrice di caratteri), e restituisce il vincitore se in quel turno fa tris, e altrimenti richiama la funzione dell'avversario//

    int i,j,k=0,riga,colonna;
    int tris=0; //flag tris//
    int finito=1; //flag completamento tabella//
    int posizionato=0; //flag inserimento simbolo//
    //stampa griglia//
    for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                printf("%c ",griglia[i][j]);
                if(j<N-1) printf("|");
            }
            printf("\n");
    }


    printf("Dimmi riga e colonna dove mettere %c: ",simbolo1);

    riga=0,colonna=0; //solo per entrare nel while la prima volta

    while(!posizionato){ //controllo che la posizione sia FUORI dalla griglia e nel caso continuo a chiedere, altrimenti inserisco//
        scanf("%d%d",&riga,&colonna);

        if(riga>0&&riga<=N&&colonna>0&&colonna<=N&&griglia[riga-1][colonna-1]!=simbolo1&&griglia[riga-1][colonna-1]!=simbolo2){
            griglia[riga-1][colonna-1]=simbolo1;
            posizionato=1;}

        else if (griglia[riga-1][colonna-1]==simbolo1||griglia[riga-1][colonna-1]==simbolo2){
            printf("Casella gia' occupata!\n");
            posizionato=0;}

        else{
            printf("Posizione fuori dalla griglia!\n");
            posizionato=0;}
    }

    riga=riga-1; //trasformo in indici per comodità//
    colonna=colonna-1;

    //controlla se ha fatto tris//
    k=0;                            //ogni volta riazzera contatore//
    for(i=riga,j=0;j<N&&!tris;j++){ //controlla riga//
        if(griglia[i][j]==simbolo1){
            k++;
        }
        if(k==N) tris=1;
    }

    k=0;
    for(i=0,j=colonna;i<N&&!tris;i++){ //controlla colonna//
        if(griglia[i][j]==simbolo1){
            k++;
        }
        if(k==N) tris=1;
    }

    k=0;
    if(riga+colonna==N-1&&!tris){       //controlla diagonale da in alto a destra a in basso a sinistra se indice riga+indice colonna=N-1//
        for(i=0,j=N-1;i<N&&j>=0;i++,j--){
                if(griglia[i][j]==simbolo1){
                    k++;
                }
                if(k==N) tris=1;
            }
    }
    k=0;
    if(riga-colonna==0&&!tris){         //controlla diagonale da in alto a sinistra a in basso a destra se indice riga=indice colonna//
        for(i=0,j=0;i<N&&j<N;i++,j++){
                if(griglia[i][j]==simbolo1){
                    k++;
                }
                if(k==N) tris=1;
            }
    }

    for(i=0;i<N&&finito;i++){
        for(j=0;j<N&&finito;j++){
            if(griglia[i][j]!=simbolo1&&griglia[i][j]!=simbolo2) finito=0;
        }
    }

    if(tris) return 1; //vince giocatore 1//
    else if(finito&&!tris) return 3;
    else {return gioca2(griglia,n,simbolo1,simbolo2);} //turno del giocatore 2//
}

int gioca2(char griglia[][N],int n,char simbolo1,char simbolo2){ //prende la griglia (con dimensione perchè matrice di caratteri), e restituisce il vincitore se in quel turno fa tris, e altrimenti richiama la funzione dell'avversario//

    int i,j,k=0,riga,colonna;
    int tris=0; //flag//
    int finito=1;
    int posizionato=0;
    //stampa griglia//
    for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                printf("%c ",griglia[i][j]);
                if(j<N-1) printf("|");
            }
            printf("\n");
    }


    printf("Dimmi riga e colonna dove mettere %c: ",simbolo2);

    riga=0,colonna=0; //solo per entrare nel while la prima volta

    while(!posizionato){ //controllo che la posizione sia FUORI dalla griglia e nel caso continuo a chiedere, altrimenti inserisco//
        scanf("%d%d",&riga,&colonna);

        if(riga>0&&riga<=N&&colonna>0&&colonna<=N&&griglia[riga-1][colonna-1]!=simbolo1&&griglia[riga-1][colonna-1]!=simbolo2){
            griglia[riga-1][colonna-1]=simbolo2;
            posizionato=1;}

        else if (griglia[riga-1][colonna-1]==simbolo1||griglia[riga-1][colonna-1]==simbolo2){
            printf("Casella gia' occupata!\n");
            posizionato=0;}

        else{
            printf("Posizione fuori dalla griglia!\n");
            posizionato=0;}
    }

    riga=riga-1; //trasformo in indici per comodità//
    colonna=colonna-1;

    //controlla se ha fatto tris//
    k=0;                            //ogni volta riazzera contatore//
    for(i=riga,j=0;j<N&&!tris;j++){ //controlla riga//
        if(griglia[i][j]==simbolo2){
            k++;
        }
        if(k==N) tris=1;
    }

    k=0;
    for(i=0,j=colonna;i<N&&!tris;i++){ //controlla colonna//
        if(griglia[i][j]==simbolo2){
            k++;
        }
        if(k==N) tris=1;
    }

    k=0;
    if(riga+colonna==N-1&&!tris){       //controlla diagonale da in alto a destra a in basso a sinistra se indice riga+indice colonna=N-1//
        for(i=0,j=N-1;i<N&&j>=0;i++,j--){
                if(griglia[i][j]==simbolo2){
                    k++;
                }
                if(k==N) tris=1;
            }
    }
    k=0;
    if(riga-colonna==0&&!tris){         //controlla diagonale da in alto a sinistra a in basso a destra se indice riga=indice colonna//
        for(i=0,j=0;i<N&&j<N;i++,j++){
                if(griglia[i][j]==simbolo2){
                    k++;
                }
                if(k==N) tris=1;
            }
    }

    for(i=0;i<N&&finito;i++){
        for(j=0;j<N&&finito;j++){
            if(griglia[i][j]!=simbolo1&&griglia[i][j]!=simbolo2) finito=0;
        }
    }

    if(tris) return 2; //vince giocatore 2//
    else if(finito&&!tris) return 3; //se nessuno ha vinto e non ci sono più spazi liberi pareggio//
    else return gioca1(griglia,n,simbolo1,simbolo2); //turno del giocatore 1//
}
