#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define MAXL 31
#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct G* Graph;

Graph GRAPHinit(int nV);
void  GRAPHfree(Graph g, int listgen);
void  GRAPHinsertE(Graph g, int id1, int id2, int wt);
void  GRAPHstore(Graph g, ST st);
int   GRAPHcheck3clique(Graph g, int x, int y, int z);
int   GRAPHmat2list(Graph g);

#endif /* GRAPH_H_INCLUDED */
