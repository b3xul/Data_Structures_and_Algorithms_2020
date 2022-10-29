#include "Graph.h"

typedef struct node* link;
struct node{int v; int flusso; link next;};     //User� sempre link, non mi serve crearne un typedef
struct graph{int V; int E; int** mAdj; link* lAdj; link z;};

static link Node_new(int v, int flusso, link next){
    link x;
    x=(link)malloc(sizeof(struct node));
    x->v=v;
    x->flusso=flusso;
    x->next=next;
    return x;
}

static int adiacent_M(Graph G, int u, int v);
static int adiacent_L(Graph G, int u, int v);

Graph Graph_init(int V){
    int i,j;
    Graph G;    //E' puntatore a graph
    G=(Graph)malloc(sizeof(struct graph));

    G->V=V;
    G->E=0;
    G->mAdj=(int**)malloc(V*sizeof(int*));
    for(i=0;i<V;i++){
        G->mAdj[i]=(int*)malloc(V*sizeof(int));
        for(j=0;j<V;j++){
            G->mAdj[i][j]=-1;
        }
    }
    G->lAdj=NULL;
    G->z=NULL;
    return G;
}

Edge Edge_load(int v, int w, int flusso){
    Edge e;
    e.v=v;
    e.w=w;
    e.flusso=flusso;
    return e;
}

void Graph_insert_edge(Graph G, Edge e){
    G->E++;
    int v=e.v, w=e.w, flusso=e.flusso;
    if (G->mAdj[v][w] == 0)
        G->E++;
    G->mAdj[v][w]=flusso;
    G->mAdj[w][v]=flusso;
}

void Graph_store(Graph G, ST st){
    int i,j;
    for(i=0;i<G->V;i++){
        ST_store_by_index(st,i);
        printf("\n");
        for(j=0;j<G->V;j++){
            if(G->mAdj[i][j]!=-1){
                printf("\t");
                ST_store_by_index(st,j);
                printf(" Flusso: %d\n", G->mAdj[i][j]);
            }
        }
    }
}

void Graph_store_list(Graph G, ST st){
    int i;
    link w;
    for(i=0;i<G->V;i++){
        ST_store_by_index(st,i);
        printf("\n");
        for(w=G->lAdj[i];w!=G->z;w=w->next){
            printf("\t");
            ST_store_by_index(st,w->v);
            printf(" Flusso: %d\n", w->flusso);
        }
    }
}

void Graph_create_list(Graph G){
    int i,j;
    G->z=Node_new(-1,-1,NULL);
    G->lAdj=(link*)malloc(G->V*sizeof(link));
    for(i=0;i<G->V;i++){
        G->lAdj[i]=G->z;
    }

    for(i=0;i<G->V;i++){
        for(j=i+1;j<G->V;j++){
            if(G->mAdj[i][j]!=-1){
                G->lAdj[i]=Node_new( j, G->mAdj[i][j], G->lAdj[i] );
                G->lAdj[j]=Node_new( i, G->mAdj[j][i], G->lAdj[j] );
            }
        }
    }
}

int Graph_list_present(Graph G){
    return (G->lAdj!=NULL);
}

int Graph_check_3clique_M(Graph G, int u, int v, int w){
    if(adiacent_M(G,u,v) && adiacent_M(G,u,w) && adiacent_M(G,v,w))
        return 1;
    return 0;
}

int Graph_check_3clique_L(Graph G, int u, int v, int w){
    if(adiacent_L(G,u,v) && adiacent_L(G,u,w) && adiacent_L(G,v,w))
        return 1;
    return 0;
}

static int adiacent_M(Graph G, int u, int v){
    return (G->mAdj[u][v]>0);
}

static int adiacent_L(Graph G, int u, int v){
    link i;
    for(i=G->lAdj[u];i!=G->z;i=i->next){
        if(i->v==v)
            return 1;
    }
    return 0;
}

void Graph_free(Graph G){
    int i,libera_lista=0;
    link v,next;

    if(Graph_list_present(G))
        libera_lista=1;

    for(i=0;i<G->V;i++){
        free(G->mAdj[i]);
        if(libera_lista){
            for(v=G->lAdj[i];v!=G->z;v=next){
                next=v->next;
                free(v);
            }
        }
    }
    free(G->mAdj);
    if(libera_lista){
        free(G->lAdj);
        free(G->z);
    }
    free(G);
}
