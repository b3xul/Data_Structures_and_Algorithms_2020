#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define MAXS 11 /**Dire nella relazione perche' qua e non in graph.c**/

typedef struct edge { int v; int w; } Edge; /**Edge STANDARD**/

typedef struct myGraph* Graph;  /** AGGIUNTO "struct" **/

/********************************************************************
  Prototipi di funzione
********************************************************************/

Graph GRAPHload (FILE *fin);

/** Spostata in Graph.c
int get_index(Vertex* vertici, char* id);
**/

 /**AGGIUNTE**/
void GRAPHfree(Graph G);

void cerca_k_core (Graph G, int k);
void verifica_j_edge (Graph G, int j);
/****/

#endif // GRAPH_H
