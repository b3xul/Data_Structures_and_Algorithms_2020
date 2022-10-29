#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "Item.h"
#include "ST.h"
#include "Graph.h"

#define MAXL 31
#define DBG 1

Graph read_file(FILE *in, ST st);

int main(int argc, char **argv) {
  char nodo[MAXL], select[MAXL], *sel;
  Graph g = NULL;
  ST st = STinit(1);
  FILE *in;
  int id1, id2, id3, stop = 0, listgen =0;

  if (argc != 2) {
    printf("Uso: %s <file_in>\n", argv[0]);
    exit(-1);
  }

  in = fopen(argv[1], "r");
  if (in == NULL)
    exit(-1);

  g = read_file(in, st);
  if (g == NULL || st == NULL)
    exit(-1);

  do {
        printf("\nQuale operazione vuoi eseguire?\n");
        printf("\tA: Visualizza grafo\n");
        printf("\tB: Genera liste di adiacenza\n");
        printf("\tC: Controlla 3-clique\n");
        printf("\tZ: Esci\n");
        scanf("%s", select);
        for (sel=select; !isalpha(*sel); sel++);
        *sel = toupper(*sel);
        switch(*sel) {
            case 'A': {
              GRAPHstore(g, st);
            }
            break;

            case 'B': {
                if (!GRAPHmat2list(g))
                  printf("Generazione lista adiacenze avvenuta con successo!\n");
                listgen = 1;
                #if DBG
                GRAPHstore(g, st);
                #endif /* DBG */
            }
            break;

            case 'C': {
                printf("Inserisci nome primo nodo: ");
                KEYscan(nodo);
                id1 = STsearch(st, nodo);
                printf("Inserisci nome secondo nodo: ");
                KEYscan(nodo);
                id2 = STsearch(st, nodo);
                printf("Inserisci nome terzo nodo: ");
                KEYscan(nodo);
                id3 = STsearch(st, nodo);
                if ((id1 != -1) && (id2 != -1) && (id3 != -1))
                  printf("Il sottografo %se' completo\n", GRAPHcheck3clique(g, id1, id2, id3) ? "" : "non ");
            }
            break;

            case 'Z': {
                stop  = 1;
            }
            break;

            default:
                printf("Scelta non valida!\n");
        }
    } while(!stop);

  STfree(st);
  GRAPHfree(g, listgen);
  return 0;
}

Graph read_file(FILE *in, ST st) {
  int i, id1, id2;
  Item x;
  char e1[MAXL], r1[MAXL], e2[MAXL], r2[MAXL];
  Graph g;

  while(fscanf(in, "%s %s %s %s %d\n", e1, r1, e2, r2, &i) == 5) {
    x = ITEMload(e1, r1);
    id1 = STsearch(st, KEYget(&x));
    if (id1 == -1)
      STinsert(st, x);
    x = ITEMload(e2, r2);
    id2 = STsearch(st, KEYget(&x));
    if (id2 == -1)
      STinsert(st, x);
  }

  rewind(in);

  g = GRAPHinit(STcount(st));
  if (g == NULL)
    return NULL;

  while(fscanf(in, "%s %s %s %s %d", e1, r1, e2, r2, &i) == 5) {
    x = ITEMload(e1, r1);
    id1 = STsearch(st, KEYget(&x));
    x = ITEMload(e2, r2);
    id2 = STsearch(st, KEYget(&x));
    if (id1 != id2 && id1 >= 0 && id2 >= 0)
      GRAPHinsertE(g, id1, id2, i);
  }

  return g;
}

