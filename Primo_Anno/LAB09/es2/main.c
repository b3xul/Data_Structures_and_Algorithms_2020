#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2
#define M 30+1

int insert_product(char warehouse[][M], float price[], int n);

void print_all(char warehouse[][M], float price[], int n, float *avg, float *max);

int main()
{
    char warehouse [N][M];
    float price[N];
    int i;
    int scelta;
    float avg; float max=0;

    for(i=0;i<N;i++){
        price[i]=-2;
    }
while(scelta!=EOF){
    printf("Seleziona l'operazione che intendi eseguire:\n1.Inserisci un nuovo prodotto con relativo prezzo\n2.Stampa il listino attuale\n3.Esci dal programma\n");
    scanf("%d",&scelta);

    switch(scelta){
    case 1:
        switch(insert_product(warehouse,price,N)){
        case 0:
            printf("Il prodotto era gia' presente nel listino\n");
            break;
        case 1:
            printf("Il prodotto e' stato inserito correttamente\n");
            break;
        case 2:
            printf("Il listino e' pieno\n");
            break;
        }
        break;

    case 2:
        print_all(warehouse,price,N, &avg, &max);
        printf("Il prezzo massimo tra quelli presenti in listino vale %f euro\n",max);
        printf("La media dei prezzi dei prodotti presenti in listino e' %f euro\n",avg);
        break;

    case 3: return 0;
        break;
    default:
        printf("L'opzione selezionata non e' disponibile. Forse col DLC...");
    }
    printf("\n");
}
    return 0;
}

int insert_product(char warehouse[][M], float price[], int n){
    int i,j;
    int scritto=0;

    for(i=0;i<n&&!scritto;i++){
        if(price[i]==-2){
            printf("Inserisci il nome del prodotto: ");
            scanf("%s",warehouse[i]);
            for(j=0;j<i;j++){
                if(!strcmp(warehouse[i],warehouse[j])){
                    return 0;
                }
            }
            printf("Inserisci il relativo prezzo: ");
            scanf("%f",&price[i]);
            scritto=1;
        }
    }
    if(scritto){
        return 1;
    }
    if(!scritto){
        return 2;
    }
}

void print_all(char warehouse[][M], float price[], int n, float *avg, float *max){
    int i=0;
    float sum=0;
    int elements=0;


    while(price[i]!=-2&&i<N){
        printf("%30s   %4f euro\n",warehouse[i],price[i]);
        sum=sum+price[i];
        elements++;
        if(price[i]>*max){
            *max=price[i];
        }
        i++;
    }
    *avg=sum/elements;

    return;
}
