#include <stdio.h>
#include <stdlib.h>
#define N 5

int main()
{
    int v[N];
    int nr1[N]={0};
    int i,j;

    printf("Inserisci dei valori: ");

    for(i=0;i<N;i++){
        scanf("%d",&v[i]);
    }

    for(i=0;i<N;i++){ //quante volte si ripetono//

        for(j=0;j<N;j++){
                if(j!=i){
                        if(v[i]==v[j]){
                        nr1[i]++;
                        }
                    }
                }
    }
    for(i=0;i<N;i++){ //quante volte si ripetono//


                if(nr1[i]>0){
                printf("Si ripete il numero %d per %d volte\n",v[i],nr1[i]+1);
                    for(j=0;j<N;j++){
                        if(v[j]==v[i]){
                            nr1[j]=0;
                        }
                    }
                }

    }


    return 0;
}
