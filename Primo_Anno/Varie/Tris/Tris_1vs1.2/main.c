#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 3
#define M 50

int gioca(char [][N],int,char,char,int);

int main()
{
    char griglia[N][N];
    int i,j;
    int turno=0; //chi inizia//
    int vincitore=0; //chi vince//
    char giocatore1[M];
    char giocatore2[M];
    char simbolo1;
    char simbolo2;
    char turnostr[M];

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            griglia[i][j]=' ';
        }
    }
    //Griglia vuota pronta//
    printf("Inserisci il nome (quante parole vuoi :) ) del primo contendente :\n");
    fgets(giocatore1,M+2,stdin); //+2 cazzooo
    giocatore1[strlen(giocatore1)-1]='\0';
    printf("Che simbolo vuoi?:\n");
    simbolo1=getchar();
    getchar();
    printf("Inserisci il nome (quante parole vuoi :) ) del secondo contendente :\n");
    fgets(giocatore2,M+2,stdin);
    giocatore2[strlen(giocatore2)-1]='\0';
    printf("Che simbolo vuoi?:\n");
    simbolo2=getchar();
    getchar();
    printf("Chi inizia? (1=%s 2=%s) -> ",giocatore1,giocatore2); //N.B. Un pò bruttino perchè gli "a capo che prende sono quelli della stringa

    while(turno!=1&&turno!=2){//controlla chi inizia//
        scanf("%s",turnostr);
        getchar();
        if(isdigit(turnostr[0])){
        turno=turnostr[0]-'0';
        switch(turno){
            case 1: vincitore=gioca(griglia,N,simbolo1,simbolo2,turno); //passo alla stessa funzione chi inizia
                break;

            case 2: vincitore=gioca(griglia,N,simbolo1,simbolo2,turno);
                break;

            default:printf("Inserisci 1 oppure 2, nient'altro!\n");
            }
        }
        else printf("Inserisci almeno un numero per carita'\n");

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


int gioca(char griglia[][N],int n,char simbolo1,char simbolo2,int turno){ //prende la griglia (con dimensione perchè matrice di caratteri), e restituisce il vincitore se in quel turno fa tris, e altrimenti richiama la funzione cambiando chi inizia

    int i,j,k=0,riga,colonna;
    int tris=0; //flag tris//
    int finito=1; //flag completamento tabella//
    int posizionato=0; //flag inserimento simbolo//
    char coord[N+1]; //Coordinate in stringa
    //stampa griglia//
    for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                printf("%c ",griglia[i][j]);
                if(j<N-1) printf("|");
            }
            printf("\n");
    }

    printf("Dimmi riga e colonna dove mettere ");
    if(turno==1){
            printf("%c: ",simbolo1);
    }
    else if (turno==2){
            printf("%c: ",simbolo2);
    }
    riga=0,colonna=0; //solo per entrare nel while la prima volta

    while(!posizionato){ //controllo che la posizione sia FUORI dalla griglia e nel caso continuo a chiedere, altrimenti inserisco//
        /*gets(coord); rompe tutto per davveroo*/


        fgets(coord,5,stdin); /*se il buffer si svuota uscendo dal while al primo giro allora non c'è problema, ma se deve passare
                                per la seconda volta dentro il while legge il \n finale come se fosse il nuovo fgets!-> e invece no!
                                bastava considerare che c'era il \0 e quindi farlo più grande di uno! :)
                                Quindi un carattere riga, un carattere spazio, un carattere colonna, il /0, il /n, totale=5*/

        coord[strlen(coord)-1]='\0';

        if(isdigit(coord[0])&&isdigit(coord[2])){
        riga=coord[0]-'0';
        colonna=coord[2]-'0';
            if(riga>0&&riga<=N&&colonna>0&&colonna<=N&&griglia[riga-1][colonna-1]!=simbolo1&&griglia[riga-1][colonna-1]!=simbolo2){
                if(turno==1) griglia[riga-1][colonna-1]=simbolo1;
                else if(turno==2) griglia[riga-1][colonna-1]=simbolo2;
                posizionato=1;}

            else if (riga>0&&riga<=N&&colonna>0&&colonna<=N&&(griglia[riga-1][colonna-1]==simbolo1||griglia[riga-1][colonna-1]==simbolo2))
                printf("Casella gia' occupata!\n");


            else printf("Posizione fuori dalla griglia!\n");

        }
        else
            printf("Il formato dev'essere 'riga colonna'\n");


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

        for(i=0;i<N&&finito;i++){   //controlla se sono finiti gli spazi//
            for(j=0;j<N&&finito;j++){
                if(griglia[i][j]!=simbolo1&&griglia[i][j]!=simbolo2) finito=0;
            }
        }

        if(tris&&turno==1) return 1; //vince giocatore 1//
        else if(tris&&turno==2) return 2; //vince giocatore 2//
        else if(finito&&!tris) return 3;
        else {
                if(turno==1) turno=2;
                else if(turno==2) turno=1;
                return gioca(griglia,n,simbolo1,simbolo2,turno);
            } //turno dell'altro giocatore//
}

