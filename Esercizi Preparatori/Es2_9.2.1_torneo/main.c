#include <stdio.h>
#include <stdlib.h>

#include "Item.h"
#include "PQ.h"

#define MAXN 50

void play(PQ pq);

int main()
{
    int cmd;
    int i,N,fine=0;
    char k[MAXS];
    char nomefile[200];
    FILE* in, *out;
    Item val;
    Item* items;

    PQ pq=NULL;
    pq=PQinit(MAXN);

    do{
        printf("0. Exit               \n");
        printf("1. Print ranking      \n");
        printf("2. Insert player      \n");
        printf("3. Delete player      \n");
        printf("4. Play               \n");
        printf("5. Load from file     \n");
        printf("6. Store to           \n");
        scanf("%d",&cmd);
        switch(cmd){
            case 1:
                N=PQsize(pq);
                items=(Item*)calloc(N,sizeof(Item));
                for(i=0;i<N;i++)
                    items[i]=PQextractMin(pq);
                for(i=N-1;i>=0;i--)
                    ITEMstore(items[i]);
                for(i=0;i<N;i++)
                    PQinsert(pq,items[i]);

                break;
            case 2:
                printf("Inserire nome: ");
                PQinsert(pq,ITEMscan(stdin));
                break;
            case 3:
                printf("Inserire nome del giocatore da eliminare: ");
                scanf("%s",k);
                val=PQdelete(pq,k);
                if(ITEMcheckNull( val ))
                    printf("nome non trovato\n");
                else{
                    printf("Ho trovato e eliminato: ");
                    ITEMstore(val);
                    ITEMfree(val);
                    printf("Heap aggiornato:\n");
                    PQdisplay(pq);

                }
                break;
            case 4:
                play(pq);
                break;
            case 5:
                printf("Inserire nome file da cui leggere: ");
                scanf("%s",nomefile);
                in=fopen(nomefile, "r");
                if(in==NULL)
                    break;
                PQfree(pq);
                pq=PQinit(MAXN);
                fscanf(in,"%d",&N);

                for(i=0;i<N;i++)
                    PQinsert(pq,ITEMscan(in));

                fclose(in);
                break;
            case 6:
                printf("Inserire nome file su cui stampare: ");
                scanf("%s",nomefile);
                out=fopen(nomefile, "w");
                if(out==NULL)
                    break;
                PQstore(pq, out);
                fclose(out);
                break;
            case 0:
                fine=1;
                PQfree(pq);
                break;
            default:
                break;
        }
    }while(!fine);

    return 0;
}

void play(PQ pq){
    int R= (rand() < RAND_MAX/2 );

    Item val1=PQextractMin(pq);
    Item val2=PQextractMin(pq);

    printf("Prossima sfida:\n");
    ITEMstore(val1);
    printf("contro\n");
    ITEMstore(val2);
    printf("............");

    if(R==0){   //vince val1
        printf("Vince %s !\n",NAMEget(val1));
        exchange_points(val1,val2);
        if(KEYget(val2)==0){
            ITEMstore(val2);
            printf("E' eliminato!\n");
            printf("Il vincitore ora ha %d punti!\n", KEYget(val1));
        }
        else{
            printf("I valori aggiornati ora sono: \n");
            ITEMstore(val1);
            ITEMstore(val2);
            PQinsert(pq,val2);
        }
        PQinsert(pq,val1);
    }
    else{   //vince val2
        printf("Vince %s !\n",NAMEget(val2));
        exchange_points(val2,val1);
        if(KEYget(val1)==0){
            ITEMstore(val1);
            printf("E' eliminato!\n");
            printf("Il vincitore ora ha %d punti!\n", KEYget(val2));
        }
         else{
            printf("I valori aggiornati ora sono: \n");
            ITEMstore(val1);
            ITEMstore(val2);
            PQinsert(pq,val1);
        }
        PQinsert(pq,val2);
    }



    return;
}
