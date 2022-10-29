#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"
#include "Graph.h"

#define DBG 0

typedef struct node *link;
struct node { int v; int wt; link next; };

struct G { int **madj; link *ladj; int V; int E;};

static int **MATRIXint(int r, int c, int val);
static link NEW(int dst, int w, link next);
static Edge EDGEcreate(int v, int w, int wt);
static void  insertE(Graph g, Edge e);
static int adjacent(Graph g, int v, int w);

static link NEW(int v, int wt, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->v = v;
  x->wt = wt;
  x->next = next;
  return x;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  for (i=0; i < r; i++) t[i] = malloc(c * sizeof(int));
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V) {
  Graph g = malloc(sizeof(*g));
  if (g == NULL)
    return NULL;
  g->V = V;
  g->E = 0;
  g->madj = MATRIXint(V, V, 0);
  g->ladj = NULL; /* questo campo viene inizializzato solo su richiesta */
  return g;
}

void GRAPHfree(Graph g, int listgen) {
  int v;
  link tmp, t;
  for (v=0; v<g->V; v++)
    free(g->madj[v]);
  free(g->madj);
  if (listgen) {
    for (v=0; v < g->V; v++)
      for (t=g->ladj[v]; t != NULL;) {
        tmp = t;
        t = t->next;
        free(tmp);
      }
    free(g->ladj);
  }
  free(g);
}

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static void  insertE(Graph g, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (g->madj[v][w] == 0)
    g->E++;
  g->madj[v][w] = wt;
  g->madj[w][v] = wt;
}

void GRAPHinsertE(Graph g, int id1, int id2, int wt) {
  insertE(g, EDGEcreate(id1, id2, wt));
}

int GRAPHmat2list(Graph g) {
  int v, w;
  if (g->ladj != NULL)
    return 0;
  if (g->madj == NULL)
    return -1;
  g->ladj = calloc(g->V, sizeof(link));
  if (g->ladj == NULL)
    return -1;

  for (v=0; v<g->V; v++)
    for (w=0; w<g->V; w++)
      if (g->madj[v][w]) {
        g->ladj[v] = NEW(w, g->madj[v][w], g->ladj[v]);
        g->ladj[w] = NEW(v, g->madj[v][w], g->ladj[w]);
      }
  return 0;
}

void GRAPHstore(Graph g, ST st) {
  int i, j;
  if (g == NULL || st == NULL)
    return;
  if (g->madj == NULL)
    return;

  for (i=0; i<g->V; i++) {
    STdisplayByIndex(st, i);
    printf("\n");
    for (j=0; j<g->V; j++) {
      if (g->madj[i][j]) {
        printf("\t\t");
        STdisplayByIndex(st, j);
        printf(" ");
      }
    }
    printf("\n");
  }
}

static int adjacent(Graph g, int v, int w) {
  if (g == NULL)
    return 0;
  if (g->madj == NULL)
    return 0;
  return (g->madj[v][w] > 0);
}

int GRAPHcheck3clique(Graph g, int x, int y, int z) {
  int ok = 1;
  if (g == NULL)
    return 0;
  if (g->madj == NULL)
    return 0;

  ok &= adjacent(g, x, y);
  ok &= adjacent(g, x, z);
  ok &= adjacent(g, y, z);

  return ok;
}

