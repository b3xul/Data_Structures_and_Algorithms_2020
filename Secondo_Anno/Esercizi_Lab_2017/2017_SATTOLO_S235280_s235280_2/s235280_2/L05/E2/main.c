#include <stdio.h>
#include <stdlib.h>

#define N 3
#define MAXS 10

typedef struct {
    int a,b;
    char c;
    float d;
    char s[MAXS];
} Item;

void leggiMatrice(Item **p);
//void associaMatrice(Item **p,Item M[N][N]);
void associaMatrice(Item **p,Item *m);
void input(Item **p);

int main()
{
    Item M[N][N];
    Item *p[N];
    //p=(Item **)malloc(N*sizeof(p));

    //associaMatrice(p,M);
    associaMatrice(p,&M[0][0]);
    leggiMatrice(p);
    input(p);


    return 0;
}


/*v1 void associaMatrice(Item **p,Item M[N][N]){

    int i;

    for(i=0;i<N;i++){
        p[i]=&M[i][0];  //per sapere l'indirizzo di ogni cella devo avere l'intera struct oppure il puntatore al primo elemento e poi calcolo io?
    }

    return;
}*/
void associaMatrice(Item **p,Item *m){
    int i;
    for(i=0;i<N;i++,m+=N){  //sposta m di N posizioni in avanti= ottengo l'indirizzo della riga successiva
        p[i]=m;
    }
    return;
}
void leggiMatrice(Item **p){
    FILE *fi;
    if((fi=fopen("Matrice.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }

    int i,j;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            fscanf(fi, "%d%d %c%f%s",&p[i][j].a,&p[i][j].b,&p[i][j].c,&p[i][j].d,p[i][j].s);
            fprintf(stdout, "%d %d %c %.2f %s\n",p[i][j].a,p[i][j].b,p[i][j].c,p[i][j].d,p[i][j].s);
        }
    }

    return;
}

void input(Item **p){
    int r,c;
    int continua=1;

    do{
        printf("Inserisci indici riga e colonna (max %d): ",N-1);
        scanf("%d%d",&r,&c);
        if(r<0||c<0||r>=N||c>=N) continua=0;
        else{
            fprintf(stdout, "%d %d %c %.2f %s\n",p[r][c].a,p[r][c].b,p[r][c].c,p[r][c].d,p[r][c].s);
            fprintf(stdout, "%p %p %p %p %p\n",&p[r][c].a,&p[r][c].b,&p[r][c].c,&p[r][c].d,&p[r][c].s);
        }
    }
    while(continua);
}
