#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"
#include "Graph.h"

#define N_OPERAZIONI 4

Graph Graph_read(ST st, FILE* fp);

int main(int arcg, char* argv[])
{
    FILE* fp=fopen(argv[1],"r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file.\n");
        exit(-1);
    }

    char* prompt[N_OPERAZIONI]={"0: Elencare in ordine alfabetico vertici e archi che insistono su di esso\n",
                                "1: Dati 3 vertici i cui nomi sono letti da tastiera, verificare se essi sono adiacenti a coppie\n",
                                "2: Generare la rappresentazione a lista di adiacenza\n",
                                "3: Terminare programma\n"};
    Graph G;
    ST st;
    int i,end,comando,found;
    int id[3];
    char str[MAX_STR];
    Item x;

    st=ST_init(1);

    G=Graph_read(st,fp);

    end=0;
    while(!end){
        printf("Inserire comando:\n");
        for(i=0;i<N_OPERAZIONI;i++){
            printf("%s",prompt[i]);
        }
        scanf("%d",&comando);
        switch(comando){
            case 0:
                Graph_store(G,st);
                //printf("-------------------\n");
                //Graph_store_list(G,st);
                break;
            case 1:
                found=1;
                for(i=0;i<3&&found;i++){
                    printf("Inserire vertice %d: ",i+1);
                    scanf("%s",str);
                    x=Item_load(str,"");
                    id[i]=ST_search(st,x);
                    if(id[i]==-1){
                        printf("Vertice non trovato.\n");
                        found=0;
                    }
                }
                if(found){
                    printf("Il sottografo %se' completo\n", Graph_check_3clique_M(G,id[0],id[1],id[2]) ? "" : "non ");
                    if(Graph_list_present(G))
                        printf("Il sottografo %se' completo\n", Graph_check_3clique_L(G,id[0],id[1],id[2]) ? "" : "non ");
                }
                break;
            case 2:
                Graph_create_list(G);
                break;
            case 3:
                end=1;
                break;
            default:
                break;
        }
    }
    Graph_free(G);
    ST_free(st);
    return 0;
}

Graph Graph_read(ST st, FILE* fp){
    Graph G;
    Item x;
    char nome1[MAX_STR],rete1[MAX_STR],nome2[MAX_STR],rete2[MAX_STR];
    int V,id1,id2,flusso;
    Edge e;

    while(fscanf(fp,"%s%s%s%s%*d",nome1,rete1,nome2,rete2)==4){
        x=Item_load(nome1,rete1);
        if(ST_search(st,x)==-1)
            ST_insert(st,x);
        x=Item_load(nome2,rete2);
        if(ST_search(st,x)==-1)
            ST_insert(st,x);
    }
    V=ST_count(st);
    rewind(fp);

    G=Graph_init(V);
    while(fscanf(fp,"%s%s%s%s%d",nome1,rete1,nome2,rete2,&flusso)==5){

        x=Item_load(nome1,rete1);
        id1=ST_search(st,x);

        x=Item_load(nome2,rete2);
        id2=ST_search(st,x);

        e=Edge_load( id1, id2, flusso );

        Graph_insert_edge(G,e);
    }

    return G;
}
