#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Graph.h"

/********************************************************************
  Main
********************************************************************/
int main(int argc, char* argv[]) {

    Graph G;
    int k,j;
    FILE* in;

    in=fopen(argv[1],"r");
    if(in==NULL)
        exit(-1);

    /*Leggo Grafo*/
    G=GRAPHload(in);

    fclose(in); /**Aggiunta**/

    scanf("%d",&k);
    /*Calcolo k-core di G*/
    cerca_k_core(G,k);

    scanf("%d",&j);
    /*Verifico se G e' j-edge-connected*/
    verifica_j_edge(G,j);

    GRAPHfree(G);

    return 0;
}
