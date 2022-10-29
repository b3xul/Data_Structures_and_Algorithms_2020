#ifndef DAG_H_DEFINED
#define DAG_H_DEFINED

#include "ST.h"

typedef struct {
	int v, w, weight;
} Edge;
typedef struct node *link;
typedef struct _dag *DAG;

void  DAGedges(DAG D, Edge *a);
DAG   DAGinit(int V);
void  DAGinsert(DAG D);
void  DAGread(DAG D);
void  DAGremove(DAG D);
void  DAGrts(DAG D);
void  DAGshow(DAG D);
void  DAGwrite(DAG D);

#endif //DAG_H_DEFINED

