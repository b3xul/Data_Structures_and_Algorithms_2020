#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define MAXS 11

typedef struct edge {
	int v;
	int w;
} Edge;

typedef struct myGraph* Graph;  /** Aggiunta "struct" **/

/********************************************************************
  Prototipi di funzione
********************************************************************/

/** Spostata in Graph.c
int get_index(Vertex* vertici, char* id);
**/

/**AGGIUNTE**/
Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
void  GRAPHpath(Graph G, int id1, int id2);
void  GRAPHpathH(Graph G, int id1, int id2);
void  GRAPHbfs(Graph G, int id);

void cerca_k_core (Graph G, int k);
void verifica_j_edge (Graph G, int j);
/****/

#endif // GRAPH_H
