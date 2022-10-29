#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"
#include "Graph.h"
#include "ST.h"

//11:45
void GRAPHread(Graph* G, FILE* in, Vertex** computers, ST* st, int* V);

int main(int argc, char** argv)
{
    Vertex* computers=NULL;
    Graph G=NULL;
    ST st=NULL;
    int V,cmd,finito=0;

    FILE* in=fopen(argv[1],"r");

    if(in==NULL){
        fprintf(stderr,"Errore apertura file\n");
        exit(-1);
    }

    GRAPHread(&G, in,&computers,&st,&V);

    do{
        printf("Quale operazione vuoi eseguire?\n");
        printf("\t1: Visualizza numero e nome dei nodi\n");
        printf("\t2: Visualizza archi incidenti su un nodo\n");
        printf("\t3: Genera matrice di adiacenza\n");
        printf("\t4: Calcolo dei flussi\n");
        printf("\t0: Esci\n");
        scanf("%d", &cmd);
        switch(cmd){

            case 0:
                finito=1;
                GRAPHfree(G);
                STfree(st);
                free(computers);
            break;
            default:
                printf("Scelta non valida\n");
            break;
        }
    }while(!finito);
    return 0;
}

void GRAPHread(Graph* G, FILE* in, Vertex** computers, ST* STABLE, int* V){
    Graph g;
    ST st;
    int i,flusso;
    Vertex* res;
    char buf1[MAXC];
    char buf2[MAXC];

    fscanf(in,"%d", V);

    g=GRAPHinit(*V);
    st=STinit(*V);
    res=(Vertex*)calloc(*V,sizeof(Vertex));

    for(i=0;i<*V;i++){
        fscanf(in,"%s %s",buf1,buf2);
        strcpy(res[i].nome,buf1);
        strcpy(res[i].rete,buf2);
        STinsert(st,ITEMnew(buf1));
    }

    while(fscanf(in,"%s %s %d",buf1,buf2,&flusso)==3){
        STsearch(st,buf1);
    }
    (*G)=g;
    (*STABLE)=st;
    (*computers)=res;

    return;
}
