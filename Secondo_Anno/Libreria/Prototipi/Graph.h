#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED

#include "PQ.h"
#include "Queue.h"
#include "ST.h"

typedef struct {
	int v, w, weight;
} Edge;
typedef struct node *link;
typedef struct _graph *Graph;

void GRAPHbfs(Graph G);
void GRAPHbridge(Graph G);
int GRAPHcc(Graph G);
void GRAPHdfs(Graph G);
void GRAPHedges(Graph G, Edge *a);
void GRAPHfree(Graph G);
Graph GRAPHinit(int V);
void GRAPHinsert(Graph G);
void GRAPHmstK(Graph G);
void GRAPHmstP(Graph G);
int GRAPHpath(Graph G);
int GRAPHpathH(Graph G);
void GRAPHread(Graph G);
void GRAPHremove(Graph G);
Graph GRAPHreverse(Graph G);
int GRAPHscc(Graph G);
void GRAPHshow(Graph G);
void GRAPHspD(Graph G);
void GRAPHspBF(Graph G);
void GRAPHwrite(Graph G);

#endif //GRAPH_H_DEFINED
