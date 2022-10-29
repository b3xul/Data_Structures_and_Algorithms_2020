#include <stdio.h>
#include <stdlib.h>

#define MAXP 50
#define MAXC 20
#define MAXD 10

#include "Item.h"
#include "ST.h"
#include "list.h"

typedef struct medicinale {
    int p; int c; int d;
}Medicinale;

void read_file(FILE* in, Medicinale** medicinali, ST* prodotti, ST* ditte, ST* categorie, link** prodByCat);
void stampa_soluzioni(Medicinale* medicinali, ST prodotti, ST ditte, ST categorie, link* prodByCat, int k);
int stampa_soluzioniR(int pos, int* sol, int* forniti,  Medicinale* medicinali, ST prodotti, ST ditte, ST categorie, link* prodByCat, int k, int CAT, int* count);

int main(int argc, char* argv[])
{
    ST prodotti=NULL;
    ST ditte=NULL;
    ST categorie=NULL;
    Medicinale* medicinali;
    link* prodByCat;    //Vettore di liste

    FILE* in=fopen("medicinali.txt","r");
    if(in==NULL)
        exit(-1);

    int k=atoi(argv[1]);

    read_file(in,&medicinali,&prodotti,&ditte,&categorie,&prodByCat);

    stampa_soluzioni(medicinali,prodotti,ditte,categorie,prodByCat,k);

    return 0;
}

void read_file(FILE* in, Medicinale** medicinali, ST* prodotti, ST* ditte, ST* categorie, link** prodByCat){
    char cat[MAXS];
    char prod[MAXS];
    char ditta[MAXS];
    int i;

    ST p=STinit(MAXP);
    ST d=STinit(MAXD);
    ST c=STinit(MAXC);
    Medicinale* m=(Medicinale*)malloc(MAXP*sizeof(Medicinale));
    link* pbc=(link*)malloc(MAXC*sizeof(link));
    for(i=0;i<MAXC;i++)
        pbc[i]=NULL;


    i=0;
    while(fscanf(in,"%s %s %s",cat,prod,ditta)==3){
		m[i].p=STgetIndex(p,prod);
		if(m[i].p==-1) {  //Se non trovo il prodotto lo inserisco
			m[i].p=STinsert(p,ITEMnew(prod));
		}

		m[i].c=STgetIndex(c,cat);
		if(m[i].c==-1) {
			m[i].c=STinsert(c,ITEMnew(cat));
		}

		m[i].d=STgetIndex(c,ditta);
		if(m[i].d==-1) {
			m[i].d=STinsert(d,ITEMnew(ditta));
		}

        pbc[m[i].c]=list_insert_head(pbc[m[i].c],i);    //Inserisco in testa alla lista di prodotti della categoria c il prodotto i;
        i++;
    }
    for(i=0;i<MAXC;i++){
        printf("Lista %d:\n",i);
        list_show(pbc[i]);
    }
    (*prodByCat)=pbc;
    (*medicinali)=m;
    (*prodotti)=p;
    (*ditte)=d;
    (*categorie)=c;
}

void stampa_soluzioni(Medicinale* medicinali, ST prodotti, ST ditte, ST categorie, link* prodByCat, int k){
    int CAT=STcount(categorie);
    int* sol=(int*)calloc(CAT, sizeof(int));
    int* forniti=(int*)calloc(STcount(ditte),sizeof(int));
    int count=0;

    if(!stampa_soluzioniR(0, sol, forniti, medicinali, prodotti, ditte, categorie, prodByCat, k, CAT, &count))
        printf("Nessuna soluzione possibile.\n");

}

int stampa_soluzioniR(int pos, int* sol, int* forniti, Medicinale* medicinali, ST prodotti, ST ditte, ST categorie, link* prodByCat, int k, int CAT, int* count){
    link l;
    int i;

    if(pos>=CAT){
        for(i=0; i<CAT; i++)
            printf("CATEGORIA %s: PRODOTTO %s (DITTA %s)\t", STsearchByIndex(categorie, medicinali[sol[i]].c),
                                                             STsearchByIndex(prodotti, medicinali[sol[i]].p),
                                                             STsearchByIndex(ditte, medicinali[sol[i]].d));

        printf("\n");
        (*count)++;
        return *count;
    }

    for(l=prodByCat[pos]; l!=NULL; l=l->next){
        forniti[ medicinali[l->val].d]++;
        if(forniti[ medicinali[l->val].d ]<=k){
            sol[pos]=medicinali[l->val].p;
            stampa_soluzioniR(pos+1, sol, forniti, medicinali, prodotti, ditte, categorie, prodByCat, k, CAT, count);
        }
        forniti[ medicinali[l->val].d ]--;
    }

    return *count;
}
