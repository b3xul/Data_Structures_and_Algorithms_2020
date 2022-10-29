#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "Graph.h"

/**************************************************************************
  Struttura dati su misura vertex
***************************************************************************/
typedef struct vertex {
	char nome[MAXS];
	int grado;
	int valido;
} Vertex;   /**Rimosso indice**/

struct myGraph {
	int V;
	int E;
	int **madj;
	Vertex* vertici;
};

static int get_index(Vertex* vertici, int V, char* id);                         /**Aggiunto parametro V**/
static int powerset(int pos, int start, int k, Graph G, Edge* Edges, int* sol); /**Aggiunto parametro start**/
static void stampa_sol(Graph G, Edge* Edges, int* sol, int k);                  /**Aggiunto intero k**/

/**Aggiunti prototipi standard**/
static Edge EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void insertE(Graph G, Edge e);
static void removeE(Graph G, Edge e);
static int connesso(Graph G);
static void dfsRcc(Graph G, int v, int id, int *cc);
/**/

/**************************************************************************
  Funzioni standard
***************************************************************************/
/**Ricerca standard in un vettore di stringhe*/
static int get_index(Vertex* vertici, int V, char* id) {
	int i;

	/*Assume formato del file corretto e omette controllo di errore per vettore vuoto*/
	for (i = 0; i  < V; i++)
		if ( strcmp(id, vertici[i].nome) == 0)
			return i;

	return -1;
}

static Edge EDGEcreate(int v, int w) {
	Edge e;
	e.v = v;
	e.w = w;
	return e;
}

static int **MATRIXint(int r, int c, int val) {
	int i, j;
	int **t = malloc(r * sizeof(int *));
	if (t==NULL)
		return NULL;

	for (i=0; i < r; i++) {
		t[i] = malloc(c * sizeof(int));
		if (t[i]==NULL)
			return NULL;
	}
	for (i=0; i < r; i++)
		for (j=0; j < c; j++)
			t[i][j] = val;
	return t;
}

Graph GRAPHinit(int V) {
	Graph G = malloc(sizeof *G);
	if (G == NULL)
		return NULL;
	G->V = V;
	G->E = 0;
	G->madj = MATRIXint(V, V, 0);
	if (G->madj == NULL)
		return NULL;
	return G;
}

static void insertE(Graph G, Edge e) {
	int v = e.v, w = e.w;

	if (G->madj[v][w] == 0)
		G->E++;
	G->madj[v][w] = 1;
	G->madj[w][v] = 1;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
	insertE(G, EDGEcreate(id1, id2));
}

static void removeE(Graph G, Edge e) {
	int v = e.v, w = e.w;
	if (G->madj[v][w] == 1)
		G->E--;
	G->madj[v][w] = 0;
	G->madj[w][v] = 0;
}

void GRAPHremoveE(Graph G, int id1, int id2) {
	removeE(G, EDGEcreate(id1, id2));
}

void GRAPHedges(Graph G, Edge *a) {
	int v, w, E = 0;
	for (v=0; v < G->V; v++)
		for (w=v+1; w < G->V; w++)
			if (G->madj[v][w] == 1)
				a[E++] = EDGEcreate(v, w);
}

static void dfsRcc(Graph G, int v, int id, int *cc) {
	int w;
	cc[v] = id;

	for (w=0; w<G->V; w++) {
		if (G->madj[v][w] != 0) {
			if ( cc[w] == -1 ) {
				dfsRcc(G, w, id, cc);
			}
		}
	}
	return;

}
/*************************************************************************
  Funczioni standard modificate: GRAPHload, HRAPHfree, GRAPHcc->connesso
**************************************************************************/

Graph GRAPHload (FILE* fin) {
	Graph G;

	/** RIMOSSA **/
	/*char nome[MAXS];*/

	char id1[MAXS];
	char id2[MAXS];
	int i, v, w;

	/**AGGIUNTA standard**/
	int V;
	fscanf(fin,"%d",&V);
	G=GRAPHinit(V);
	/**/
	G->vertici = (Vertex*) calloc(G->V, sizeof(Vertex));

	for(i=0; i<G->V; i++) {
		fscanf(fin, "%s",G->vertici[i].nome);   /**AGGIUNTA "fin" **/
		G->vertici[i].valido=1;
	}

	while( fscanf(fin,"%s %s", id1,id2) == 2 ) {
		v=get_index(G->vertici, V, id1);
		w=get_index(G->vertici, V, id2);

		/*Aggiorno gradi in lettura*/
		if (id1 >= 0 && id2 >=0) {  /**Aggiunto controllo di errore**/
			G->vertici[v].grado++;
			G->vertici[w].grado++;

			GRAPHinsertE(G,v,w);
		}
	}

	return G;
}

void GRAPHfree(Graph G) {
	int i;
	for (i=0; i<G->V; i++)
		free(G->madj[i]);
	free(G->madj);
	/**STfree(G->tab);**/
	free(G->vertici);     /**Aggiunta**/
	free(G);
}

/**GraphCC semplificata: invece di ricercare tutte le componenti connnesse, ritorna 1 se la dfs ha toccato tutti i vertici (grafo connesso) e 0 in caso contrario**/
static int connesso(Graph G) {
	int v, *cc;
	cc = malloc(G->V * sizeof(int));

	if (cc == NULL)
		return -1;

	for (v = 0; v < G->V; v++)
		cc[v] = -1;

	dfsRcc(G, 0, 1, cc);

	for (v = 0; v < G->V; v++)
		if (cc[v] == -1) {
			free(cc);
			return 0;
		}

	free(cc);
	return 1;
}

/**************************************************************************
  Funzione di calcolo e visualizzazione del k-core del grafo (richiesta 1)
***************************************************************************/
void cerca_k_core (Graph G, int k) {
	int grado, i, rimosso, j;

	/**Aggiunta per mantenere grafo letto senza rimuovere davvero gli archi**/
	Edge* Edges=(Edge*) malloc(G->E*sizeof(Edge));
	GRAPHedges(G,Edges);
	int E=G->E;
	/**/

	grado=1;
	while(grado<=k) {
		while(1) {
			/*Ciclo sui vertici*/
			for(i=0; i<G->V; i++) {
				if( G->vertici[i].grado < grado) {
					/**G->vertici[i].grado--;    Spostata dopo**/
					G->vertici[i].valido=0;
				}
			}

			rimosso=0;

			/*Ciclo sulla matrice*/
			for(i=0; i<G->V; i++) {
				for(j=0; j<G->V; j++) {
					if( G->madj[i][j]!=0 && ( G->vertici[i].valido==0 || G->vertici[j].valido==0)) {    /**Sostituito 'm' con G->madj**/
						/*Rimuovo archi incidenti su vertici con grado<k*/
						GRAPHremoveE(G,i,j);
						GRAPHremoveE(G,i,j);
						/**Aggiunta**/
						G->vertici[i].grado--;
						G->vertici[j].grado--;
						/**/
						rimosso=1;
					}
				}
			}
			/*Se non ho rimosso alcun arco ho trovato il "grado-core" del grafo e passo al grado successivo fino a trovare il k-core*/
			if(!rimosso)
				break;
		}
		grado++;
	}

	/*Stampa soluzione*/
	printf("%d-core:\n",k);
	for(i=0; i<G->V; i++) {
		if(G->vertici[i].valido) {
			printf("%s ",G->vertici[i].nome);
		}
	}
	printf("\n");

	/**Aggiunta Ripristina grafo originario**/
	for(i=0; i<E; i++) {
		insertE(G, Edges[i]);
	}
	free(Edges);
	/**/
	return;
}

/**************************************************************************
  Funzione di verifica di j-edge-connection (richiesta 2)
***************************************************************************/
/**Aggiunta**/
static void stampa_sol(Graph G, Edge* Edges, int* sol, int k) {
	int i;
	Edge arco;

	if(k==0)
		printf("Il grafo e' gia' sconnesso\n");
	else {
		printf("Il grafo e' %d-edge-connected:\n",k);
		printf("Rimuovendo il seguente sottoinsieme di archi, il grafo verra' sconnesso:\n");
		for(i=0; i<k; i++) {
			arco=Edges[ sol[i] ];
			printf("%s - %s\n", G->vertici[ arco.v ].nome, G->vertici[ arco.w ].nome);
		}
	}
}
/**/

static int powerset(int pos, int start, int k, Graph G, Edge* Edges, int* sol) {
	/** Genero sottoinsiemi di archi di cardinalita' k.
	    Idea originale: Questi sottoinsiemei saranno indicati da un vettore sol di interi (0,1) di dimensione E in cui k elementi sono a 1. Disposizioni ripetute associate a una funzione che controlli quanti elementi sono a 1.
	    Idea corretta: Questi sottoinsiemi saranno indicati da un vettore sol di dimensione k contenente l'indice dell'arco/degli archi che, se rimossi, sconnettono il grafo. Combinazioni semplici.
	**/
	/**int isAcyclic=0; rimossa**/
	int i;  /**Aggiunta**/

	if(pos>=k) {
		if(!connesso(G)) {   /**Modificata**/
			stampa_sol(G, Edges, sol, k);
			return 1;
		} else
			return 0;
	}

	/**Originale
	for(i=0; i<G->E; i++) {
		sol[i]=0;
		if(powerset(pos+1, k, G, Edges, sol))
			return 1;

		sol[i]=1;
		removeE(G, Edges[i]);
		if(powerset(pos+1, k, G, Edges, sol))
			return 1;
		insertE(G, Edges[i]);
	}
	**/

	/**Modificato**/
	for(i=start; i<G->E; i++) { /**Cambiato indice di partenza start**/

		sol[pos]=i;
		removeE(G, Edges[i]);   /**Aggiunto 'G'**/
		if(powerset(pos+1, start+1, k, G, Edges, sol))
			return 1;
		insertE(G, Edges[i]);   /**Aggiunto 'G'**/

	}

	return 0;
}

void verifica_j_edge (Graph G, int j) {
	/** Genero sottoinsiemi di archi di cardinalita' i crescente tra 0 e j.**/
	Edge* Edges;
	Edges=(Edge*)calloc(G->E, sizeof(Edge));    /**Aggiunta**/
	GRAPHedges(G, Edges);

	int i, res=0, *sol;

	for(i=0; i<=j; i++) {   /**Modificato indice di partenza a 0 per considerare grafo gia' sconnesso in partenza**/
		sol=(int*)calloc(i, sizeof(int));
		res=powerset(0, 0, i, G, Edges, sol);
		if( (res!=0 && i<j) || (i==j && res==0) ) {
			printf("Il grafo non e' %d-edge-connected",j);
			free(sol);
			break;
		}
		free(sol);
	}

	free(Edges);  /**Aggiunta**/

	return;
}
