#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXR 20
#define MAXC 20

int mat_search (char mat[MAXR][MAXC+1], int r, int c, char s[MAXC+1]);

int main()
{
    FILE *fp;
    //apro file
    if((fp=fopen("matrice.txt","r"))==NULL){
        fprintf(stderr,"File non trovato");
        return -1;
    }


    int i,r,c,tot;
    char s[MAXC+1];
    char mat[MAXR][MAXC+1]; //+1 altrimenti rischio di non comprendere il '\0' nel caso c=20

    //leggo matrice e ricavo dimensioni effettive
    i=0;
    while(fscanf(fp,"%s",mat[i])!=EOF){
        printf("%s\n",mat[i]);
        i++;
    }
    r=i;
    c=strlen(mat[0]);   //ipotizzo comunque che sia rettangolare
    printf("\n");

    printf("Inserisci parola da ricercare: ");
    scanf("%s",s);

    tot=mat_search(mat,r,c,s); //<- passaggio di matrice,righe,colonne,stringa da cercare a funzione

    printf("Ho trovato '%s' %d volte",s,tot);

    fclose(fp);

    return 0;
}

int mat_search (char mat[MAXR][MAXC+1], int r, int c, char s[MAXC+1]){
    int i,j,k,cnt,tot=0,dx,dy,q,p;//q,p indici ausiliari
    int delta[2][2]={   {0,1}, //per muoversi lungo la riga l'indice di riga i deve rimanere costante(+0) e quello di colonna j deve aumentare/diminuire di 1
                        {1,0}};//per muoversi lungo la colonna l'indice di riga deve aumentare/diminuire di 1 e quello di colonna j deve rimanere costante(+0)
                               //diagonale (1,1)
                               //antidiagonale(1,-1)

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(mat[i][j]==s[0]){
                if(s[1]=='\0') tot++; //caso banale di una parola da una sola lettera
                else{
                    /* k=0: riga, k=1: colonna, k=2: diagonale, k=3: anti-diagonale */
                    for (k=0; k<2; k++) {
                        dx = delta[k][0]; //a x dovremo aggiungere/togliere delta[0][0]=0 per muoverci lungo la riga e delta[1][0]=1 per muoverci lungo la colonna
                        dy = delta[k][1]; //a y dovremo aggiungere/togliere delta[0][1]=1 per muoverci lungo la riga e delta[1][1]=0 per muoverci lungo la colonna

                        //controllo a sinistra e verso l'alto
                        for(p=i-dx,q=j-dy,cnt=1;    //parto a cercare dalla seconda lettera (posizione i-dx,j-dy perchè ho già trovato la prima
                            p>=0 && q>=0 && p<r && q<c && mat[p][q]==s[cnt];    //controlli
                            p-=dx,q-=dy){
                            cnt++;  //quante lettere della parola cercata trovo
                            if(cnt==strlen(s)) tot++;}  //quante volte trovo l'intera parola
                        // controllo a destra e verso il basso
                        for(p=i+dx,q=j+dy,cnt=1;
                            p>=0 && q>=0 && p<r && q<c && mat[p][q]==s[cnt];
                            p+=dx,q+=dy){
                            cnt++;
                            if(cnt==strlen(s)) tot++;
                        }
                    }
                }
            }
        }
    }
    return tot;
}
