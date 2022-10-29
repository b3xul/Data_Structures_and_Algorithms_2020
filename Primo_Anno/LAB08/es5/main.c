#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

int main()
{
    char lista[N][40];
    char need[40];
    int prezzi[N];
    int i;
    int amount;
    int tot;
    int trovato=0;

    for(i=0;i<N;i++){
    printf("Ho bisogno di nome e prezzo di un prodotto: \n");
    scanf("%s%d",lista[i],&prezzi[i]);
    }

    for(i=0;i<N;i++){
    printf("%s\t%d\n",lista[i],prezzi[i]);
    }

    while(trovato==0){
        printf("Ora dimmi cosa devi comprare e quanti ne vuoi: ");
        scanf("%s%d",need,&amount);

        for(i=0;i<N;i++){
            if(!strcmp(lista[i],need)){
                tot=amount*prezzi[i];
                printf("Ti verra' a costare %d euro!",tot);
                trovato=1;
            }
        }
    }

    return 0;
}
