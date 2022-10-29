#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 6

int main()
{
    int tessere[N];
    int denaro_iniziale;
    int giusto;
    int i,t1,t2;
    int finito;
    int finitototale;
    int costo;

    printf("Comincia il gioco!\n");
    printf("Inserisci l'importo iniziale (un numero intero per cortesia): ");

    do{
        giusto=fscanf(stdin,"%d",&denaro_iniziale);
    }
    while(!giusto);

    for(i=0;i<N;i++){
        tessere[i]=denaro_iniziale;
    }

    finito=0;
    finitototale=0;
    while(!finitototale){
        printf("Indica il numero della tessera da cui prendere i soldi e poi quella a cui darli (zero per indicare nessuna tessera, doppio zero per terminare il gioco): ");
        giusto=fscanf(stdin,"%d%d",&t1,&t2);

        finito=0;
        while(!finito&&giusto==2){

            if(t1>N||t2>N) printf("Ehi ci sono solo %d tessere!\n",N);
            else if(t1<0||t2<0) printf("I numeri negativi non saranno accettati.\n");
            else{
                if(t1==0&&t2==0){
                        finito=1;
                        finitototale=1;
                        printf("Partita terminata.\n");
                }
                else if(t1==0&&t2!=0){
                    printf("Indica la quantità di soldi magici (interi) da trasferire alla tessera %d: ",t2);
                    do{fscanf(stdin,"%d",&costo);}
                    while(!costo);

                    tessere[t2-1]=tessere[t2-1]+costo;
                    printf("Il saldo attuale è di %d\n",tessere[t2-1]);
                    finito=1;
                }
                else if(t1!=0&&t2==0){
                    printf("Indica la quantità di soldi magici (interi) da trasferire dalla tessera %d: ",t1);
                    do{fscanf(stdin,"%d",&costo);}
                    while(!costo);

                    tessere[t1-1]=tessere[t1-1]-costo;
                    printf("Il saldo attuale è di %d\n",tessere[t1-1]);
                    finito=1;
                }
                else{
                    printf("Indica la quantità di soldi magici (interi) da trasferire dalla tessera %d alla tessera %d: ",t1,t2);
                    do{fscanf(stdin,"%d",&costo);}
                    while(!costo);

                    tessere[t1-1]=tessere[t1-1]-costo;
                    tessere[t2-1]=tessere[t2-1]+costo;
                    printf("Il saldo attuale di %d è di %d\n",t2,tessere[t2-1]);
                    printf("Il saldo attuale di %d è di %d\n",t1,tessere[t1-1]);
                    finito=1;
                }

            }
        }

    }
    //printf("I primi tre classificati sono:\n1. Tessera %d!\n2. Tessera %d\n3. Tessera %d\nGrazie a tutti per la partecipazione vi voglio bene ciao",primo,secondo,terzo);
    return 0;
}
