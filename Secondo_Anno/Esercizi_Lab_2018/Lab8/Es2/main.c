#include <stdio.h>
#include <stdlib.h>

#define T_FILENAME "tiles.txt"
#define B_FILENAME "board.txt"
/*Astrazione importante: Mossa!=Tessera!*/

typedef struct tessera{
    char colore[2];
    int valore[2];
}Tessera;

typedef struct tessere_wrapper{
    Tessera* tessere;
    int n;
}Tessere_w;

typedef struct mossa{
    int indice_tessera;
    int rotazione;
}Mossa;

typedef struct Scacchiera{
    Mossa** coordinate;
    int R;
    int C;
}Scacchiera;

Tessere_w leggi_file_tessere();
Scacchiera leggi_file_mosse();
void ottimizza(Scacchiera s,Tessere_w t_w);
void disp_semplici(int pos, Scacchiera s, Tessere_w t_w, int* mark, Mossa** best_s, int* punteggio_max);
Mossa newMossa(int indice, int rotazione);
void stampa_tessere(Tessere_w t_w);
void stampa_scacchiera(Scacchiera s);

int main()
{
    Tessere_w t_w;
    t_w=leggi_file_tessere();

    stampa_tessere(t_w);

    Scacchiera s;  //Matrice di mosse
    s=leggi_file_mosse();

    stampa_scacchiera(s);

    ottimizza(s,t_w);

    return 0;
}

Tessere_w leggi_file_tessere(){
    Tessere_w t_w;
    int i;
    FILE* fp=fopen(T_FILENAME,"r");
    if(fp==NULL)
        exit(-1);

    fscanf(fp,"%d",&t_w.n);

    t_w.tessere=(Tessera*)malloc(t_w.n*sizeof(Tessera));

    for(i=0;i<t_w.n;i++){
        fgetc(fp);  //Rimuovere \n In alternativa al fondo della scanf includo \n
        fscanf(fp,"%c %d %c %d", &t_w.tessere[i].colore[0], &t_w.tessere[i].valore[0], &t_w.tessere[i].colore[1], &t_w.tessere[i].valore[1]);
    }

    return t_w;
}

Scacchiera leggi_file_mosse(){
    Scacchiera board;
    int i,j;
    FILE* fp=fopen(B_FILENAME,"r");
    if(fp==NULL)
        exit(-1);

    fscanf(fp,"%d %d",&board.R,&board.C);

    board.coordinate=(Mossa**)malloc(board.R*sizeof(Mossa*));
    for(i=0;i<board.R;i++)
        board.coordinate[i]=(Mossa*)malloc(board.C*sizeof(Mossa));

    for(i=0;i<board.R;i++){
        for(j=0;j<board.C;j++)
            fscanf(fp,"%d/%d", &board.coordinate[i][j].indice_tessera,&board.coordinate[i][j].rotazione);
    }

    return board;
}

void ottimizza(Scacchiera s,Tessere_w t_w){
    int i,j,tessera, pos=0, punteggio_max=0;
    Mossa** best_s;

    best_s=(Mossa**)malloc(s.R*sizeof(Mossa*));
    for(i=0;i<s.R;i++)
        best_s[i]=(Mossa*)malloc(s.C*sizeof(Mossa));

    for(i=0;i<s.R;i++){
        for(j=0;j<s.C;j++){
            best_s[i][j].indice_tessera=s.coordinate[i][j].indice_tessera;
            best_s[i][j].rotazione=s.coordinate[i][j].rotazione;
        }
    }


    int* mark=(int*)calloc(t_w.n,sizeof(int));
    for(i=0;i<s.R;i++){
        for(j=0;j<s.C;j++){
            tessera=s.coordinate[i][j].indice_tessera;
            if(tessera!=-1)
                mark[tessera]=1;
        }
    }

    disp_semplici(pos,s,t_w,mark,best_s,&punteggio_max);

    printf("Lo schema ottimizzato e':\n");
    s.coordinate=best_s;
    stampa_scacchiera(s);
    printf("Con punteggio massimo di %d!\n",punteggio_max);

}

void disp_semplici(int pos, Scacchiera s, Tessere_w t_w, int* mark, Mossa** best_s, int* punteggio_max){
    int i,j,punteggio_corrente,punteggio_totale,i_tessera,tubo;
    char colore;

    if(pos>=s.R*s.C){
        //Controllo per righe
        punteggio_totale=0;
        for(i=0;i<s.R;i++){
            punteggio_corrente=0;
            colore=t_w.tessere[s.coordinate[i][0].indice_tessera].colore[(s.coordinate[i][0].rotazione)?1:0];
            for(j=0;j<s.C;j++){
                i_tessera=s.coordinate[i][j].indice_tessera;
                tubo=(s.coordinate[i][j].rotazione)?1:0;
                if(t_w.tessere[i_tessera].colore[tubo]!=colore)
                    break;
                punteggio_corrente+=(t_w.tessere[i_tessera].valore[tubo]);
            }
            if(j==s.C)
                punteggio_totale+=punteggio_corrente;
        }

        //Controllo per colonne
        for(i=0;i<s.C;i++){
            punteggio_corrente=0;
            colore=t_w.tessere[s.coordinate[0][i].indice_tessera].colore[(s.coordinate[0][1].rotazione)?0:1];
            for(j=0;j<s.R;j++){
                i_tessera=s.coordinate[j][i].indice_tessera;
                tubo=(s.coordinate[j][i].rotazione)?0:1;
                if(t_w.tessere[i_tessera].colore[tubo]!=colore)
                    break;
                punteggio_corrente+=(t_w.tessere[i_tessera].valore[tubo]);
            }
            if(j==s.R)
                punteggio_totale+=punteggio_corrente;
        }


        if(punteggio_totale>*punteggio_max){
            *punteggio_max=punteggio_totale;
            for(i=0;i<s.R;i++){
                for(j=0;j<s.C;j++){
                    best_s[i][j].indice_tessera=s.coordinate[i][j].indice_tessera;
                    best_s[i][j].rotazione=s.coordinate[i][j].rotazione;
                }
            }
        }

        return;
    }

    int r=pos/s.C, c=pos%s.C, k;

    if(s.coordinate[r][c].indice_tessera!=-1){
        disp_semplici(pos+1,s,t_w,mark,best_s,punteggio_max);
        return;
    }

    for(k=0 ; k<t_w.n ; k++){
        if(mark[k]==0){
            mark[k]=1;
            s.coordinate[r][c]=newMossa(k,0);
            disp_semplici(pos+1,s,t_w,mark,best_s,punteggio_max);
            s.coordinate[r][c]=newMossa(k,1);
            disp_semplici(pos+1,s,t_w,mark,best_s,punteggio_max);
            mark[k]=0;
            s.coordinate[r][c]=newMossa(-1,-1);
        }
    }

    return;
}

Mossa newMossa(int indice, int rotazione){
    Mossa m;
    m.indice_tessera=indice;
    m.rotazione=rotazione;
    return m;
}

void stampa_tessere(Tessere_w t_w){
    int i;
    for(i=0;i<t_w.n;i++)
        printf("Tessera %d: %c:%d %c:%d\n",i,t_w.tessere[i].colore[0], t_w.tessere[i].valore[0], t_w.tessere[i].colore[1], t_w.tessere[i].valore[1]);
}

void stampa_scacchiera(Scacchiera s){
    int i,j;
    for(i=0;i<s.R;i++){
        for(j=0;j<s.C;j++)
            printf("%d/%d ",s.coordinate[i][j].indice_tessera,s.coordinate[i][j].rotazione);
        printf("\n");
    }
    printf("\n");
}
