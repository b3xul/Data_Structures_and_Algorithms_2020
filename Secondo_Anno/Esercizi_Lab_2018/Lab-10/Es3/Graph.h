#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"
#include "ST.h"

typedef struct graph* Graph;
typedef struct edge{int v; int w; int flusso; }Edge;

Edge Edge_load(int v, int w, int flusso);
Graph Graph_init(int V);
void Graph_insert_edge(Graph G, Edge e);
void Graph_store(Graph G, ST st);
void Graph_store_list(Graph G, ST st);
void Graph_create_list(Graph G);
int Graph_list_present(Graph G);
int Graph_check_3clique_M(Graph G, int u, int v, int w);
int Graph_check_3clique_L(Graph G, int u, int v, int w);
void Graph_free(Graph G);
#endif // GRAPH_H_INCLUDED
