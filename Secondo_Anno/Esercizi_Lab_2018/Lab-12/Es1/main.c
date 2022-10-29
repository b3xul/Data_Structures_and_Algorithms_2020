#include <stdio.h>
#include <stdlib.h>

#include "Item.h"
#include "ST.h"
#include "PQ.h"
#include "Graph.h"

#define NOMEFILE "grafo1.txt"

int main()
{
    FILE* fp=fopen(NOMEFILE,"r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file.\n");
        exit(-1);
    }

    Graph G=GRAPHload(fp);
    GRAPHstore(G,stdout);


    return 0;
}
