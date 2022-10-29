#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXS 20

typedef struct paese{
    char *nome;
    int abitanti;
    int distanza;
}Paese;

typedef struct wpaese{
    Paese *paesi;
    int **distanze;
}wPaese;

int caricaPaesi(FILE *fi,wPaese *cartina);
void stampaPaese(wPaese cartina,int i,int scelta);
wPaese calcolaDistanze(wPaese cartina,int n);
int comb_sempl(int pos,wPaese cartina,int *solPossibile,int *solMigliore,int n,int k,int start,int count,int *min);
int sommaDistanze(wPaese cartina, int *sol,int n,int k);

int main(int argc,char *argv[])
{
    if(argc!=3){
        fprintf(stderr,"Numero di argomenti non valido.");
        return -1;
    }

    FILE *fi;
    if((fi=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"File non trovato");
        return -2;
    }

    wPaese cartina;

    int n=caricaPaesi(fi,&cartina);
    int k=atoi(argv[2]);
    int i,j;

    int *solPossibile=(int *)malloc(k*sizeof(int));
    if(solPossibile==NULL)
        return -5;

    int *solMigliore=(int *)malloc(k*sizeof(int));
    if(solMigliore==NULL)
        return -6;

    for(i=0;i<n;i++)
        stampaPaese(cartina,i,1);
    printf("\n");
    cartina=calcolaDistanze(cartina,n);

#if DBG
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d\t", cartina.distanze[i][j]);
        }
        printf("\n");
    }
#endif

    int min=INT_MAX;
    comb_sempl(0,cartina,solPossibile,solMigliore,n,k,0,0,&min);   //comb_sempl(pos,cartina,solPossibile,solMigliore,n,k,start,count,min);

    printf("Le %d citta' migliori in cui piazzare delle ATO sono:\n",k);

    for(i=0;i<k;i++)
        stampaPaese(cartina,solMigliore[i],2);

    printf("\nCon somma delle distanze = %d\n",min);

    fclose(fi);

    return 0;
}

int caricaPaesi(FILE *fi,wPaese *cartina){
    int i,n;
    char buffer[MAXS+1];
    fscanf(fi,"%d",&n);

    (*cartina).paesi=(Paese *)malloc(n*sizeof(Paese));

    if((*cartina).paesi==NULL)
        exit(-3);

    for(i=0;i<n;i++){
        fscanf(fi,"%s%d%d",buffer,&(*cartina).paesi[i].abitanti,&(*cartina).paesi[i].distanza);
        (*cartina).paesi[i].nome=strdup(buffer);
        if((*cartina).paesi[i].nome==NULL)
            exit(-4);
    }

    return n;
}

void stampaPaese(wPaese cartina,int i,int scelta){
    if(scelta==1)
        printf("%s %d %d\n",cartina.paesi[i].nome,cartina.paesi[i].abitanti,cartina.paesi[i].distanza);
    else if(scelta==2)
        printf("%s\n",cartina.paesi[i].nome);
    return;
}

wPaese calcolaDistanze(wPaese cartina,int n){
    int i,j;
    cartina.distanze=(int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++)
        cartina.distanze[i]=(int *)malloc(n*sizeof(int));

    for(i=0;i<n;i++){
        for(j=i;j<n;j++){
            cartina.distanze[i][j]=cartina.distanze[j][i]=cartina.paesi[j].distanza-cartina.paesi[i].distanza;
        }
    }
    return cartina;
}

int comb_sempl(int pos,wPaese cartina,int *solPossibile,int *solMigliore,int n,int k,int start,int count,int *min){
    int i;
    int somDist;

    if(pos>=k){
        somDist=sommaDistanze(cartina,solPossibile,n,k);
        if(somDist<=(*min)){
            (*min)=somDist;
            for(i=0;i<k;i++)
                solMigliore[i]=solPossibile[i];

            return count+1;
        }
        return count;
    }

    for(i=start;i<n;i++){
        solPossibile[pos]=i;
        count=comb_sempl(pos+1,cartina,solPossibile,solMigliore,n,k,i+1,count,min);
    }

    return count;
}

int sommaDistanze(wPaese cartina, int *sol,int n,int k){
    int i,j,somma,minDist;

    for(i=0,somma=0;i<n;i++){   //per ogni città
        minDist=INT_MAX;
        for(j=0;j<k;j++){        //per ogni ATO
            if(cartina.distanze[i][sol[j]]<minDist)  //trova la minima distanza città-ATO
                minDist=cartina.distanze[i][sol[j]];
            if(j>0&&cartina.distanze[i][sol[j]]>cartina.distanze[i][sol[j-1]])
                break;
        }
        somma+=cartina.paesi[i].abitanti*minDist;
    }

    return somma;
}
