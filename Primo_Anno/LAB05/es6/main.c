#include <stdio.h>
#include <stdlib.h>
#define N 5

int main()
{
    int x,y,i,fine,trovato;
    int v1[N]={0};
    int v2[N]={0};

    printf("Inserisci dati: ");

    fine=0;
/*inutile, basta scanf...,&v[i]*/
    for(i=0;i<N&&fine==0;i++){
        scanf("%d",&x);
            if(x>0){
                v1[i]=x;
            }
            else fine=1;
    }

    for(i=0;i<N;i++){
        printf("%d ",v1[i]);
    }

    printf("\n");
    printf("Inserisci il valore da ricercare: ");
    scanf("%d",&y);

    trovato=0;
    for(i=0;i<N;i++){
        if(y==v1[i]){
            v2[i]=i;
            }
    }
    for(i=0;i<N&&trovato==0;i++){
        if (v2[i]!=0){
            trovato=1;
        }
    }
    printf("\n");
    if(trovato==1){
    printf("L'abbiamo trovato nelle seguenti posizioni:\n");
           if(v2[0]==y){
            printf("0 ");
           }

           for(i=1;i<N;i++){
                if(v2[i]!=0){
                printf("%d ",v2[i]);
                }

                else{
                    printf("Qua no ");
                }
           }
    }
    else
    printf("Non l'abbiamo trovato..");

    return 0;
}
