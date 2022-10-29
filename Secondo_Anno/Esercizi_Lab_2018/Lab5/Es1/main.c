#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_STR 256

typedef struct amico{ int* scelte; int n_scelte;}Amico;

char*** leggi_file(int* A,Amico** val,int** sol);
int princ_molt(int pos, Amico* val, int* sol, int A, char*** tab, int count);

int main()
{
    char*** Tab_simboli;
    int A;  //N amici
    Amico* val;
    int* sol;
    Tab_simboli=leggi_file(&A,&val,&sol);
    int count;

    count=princ_molt(0,val,sol,A,Tab_simboli,0);

    printf("Ci sono %d possibili playlist.\n",count);
    return 0;
}

char*** leggi_file(int* A,Amico** val,int** sol){
    FILE* fp;
    fp=fopen("brani.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file.\n");
        exit(-1);
    }

    int i,j;

    fscanf(fp,"%d",A);

    char buf[MAX_STR];
    Amico* v=(Amico*)malloc((*A)*sizeof(Amico));
    char*** tab=(char***)malloc((*A)*sizeof(char**));    //tab=matrice di stringhe (riga=amico; colonna=canzone)
    int* s=(int*)calloc((*A),sizeof(int));

    for(i=0;i<(*A);i++){
        fscanf(fp,"%d",&(v[i].n_scelte));

        v[i].scelte=(int*)malloc(v[i].n_scelte*sizeof(int));
        tab[i]=(char**)malloc(v[i].n_scelte*sizeof(char*));   //tab[i]=riga di n_scelte canzoni

        for(j=0;j<v[i].n_scelte;j++){
            v[i].scelte[j]=j;
            fscanf(fp,"%s",buf);
            tab[i][j]=strdup(buf);                     //tab[i][j]= canzone
        }
    }

    (*val)=v;
    (*sol)=s;
    return tab;
}

int princ_molt(int pos, Amico* val, int* sol, int A, char*** tab, int count){
    int i;

    if(pos>=A){ //Condizione di terminazione
        count++;
        printf("Playlist %d: ",count);
        for(i=0;i<A;i++){
            printf("%s ",tab[i][sol[i]]);     //Stampa la canzone che ha indice sol[i] (indice soluzione associato all'amico i) tra le canzoni dell'amico i (tab[i])
        }
        printf("\n");
        return count;
    }

    for(i=0;i<val[pos].n_scelte;i++){     //A ogni livello si itera sulle scelte che l'amico A può fare
        sol[pos]=i;     //Prendo soluzione attuale dell'amico A
        count=princ_molt(pos+1, val, sol, A, tab, count);   //Ricorro sull'amico successivo: esplora in profondità
        //Non serve backtrack;
    }
    return count;

}
