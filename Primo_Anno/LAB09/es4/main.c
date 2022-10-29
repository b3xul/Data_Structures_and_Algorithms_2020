#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5
#define M 30+1

int insert_product(char warehouse[][M], float price[], int n);

void print_all(char warehouse[][M], float price[], int n, float *avg, float *max);

int update_product(char warehouse[][M], float price[], int n);

int remove_product(char warehouse[][M], float price[], int n);

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
    printf("Seleziona l'operazione che intendi eseguire:\n1.Inserisci un nuovo prodotto con relativo prezzo\n2.Stampa il listino attuale\n3.Aggiorna il prezzo di un prodotto\n4.Rimuovi un prodotto dal listino\n5.Esci dal programma\n");
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

    case 3:
        if(update_product(warehouse,price,N)){
            max=0;
            printf("Il prezzo e' stato aggiornato correttamente\n");
        }
        else{
            printf("Il prodotto selezionato non e' presente in listino\n");
        }
        break;

    case 4:
        if(remove_product(warehouse,price,N)){
                max=0;
            printf("Il prodotto e' stato rimosso correttamente\n");
        }
        else{
            printf("Il prodotto selezionato non e' presente in listino\n");
        }

        break;

    case 5: return 0;
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
    int res=0;

    for(i=0;i<n&&!scritto;i++){
        if(price[i]==-2){
            printf("Inserisci il nome del prodotto: ");
            scanf("%s",warehouse[i]);
            for(j=0;j<i;j++){
                if(!strcmp(warehouse[i],warehouse[j])){
                    res=0;
                }
            }
            printf("Inserisci il relativo prezzo: ");
            scanf("%f",&price[i]);
            scritto=1;
        }
    }
    if(scritto){
        res=1;
    }
    if(!scritto){
        res=2;
    }
    return res;
}

void print_all(char warehouse[][M], float price[], int n, float *avg, float *max){
    int i=0;
    float sum=0;
    int elements=0;

    while(i<N){
        if(price[i]!=-2){
        printf("%30s   %4f euro\n",warehouse[i],price[i]);
        sum=sum+price[i];
        elements++;
        if(price[i]>*max){
            *max=price[i];
        }
        }
        i++;
    }
    if(elements>0){*avg=sum/elements;}
    else{*avg=0;}

    return;
}

int update_product(char warehouse[][M], float price[], int n){

    char product[M];
    int i;

    printf("Inserisci il nome del prodotto di cui aggiornare il prezzo: ");
    scanf("%s",product);
    for(i=0;i<n;i++){
        if(!strncmp(product,warehouse[i],strlen(product))&&price[i]!=-2){
            printf("Inserisci il nuovo prezzo del prodotto: ");
            scanf("%f",&price[i]);
            return 1;
        }
    }
    return 0;
}

int remove_product(char warehouse[][M], float price[], int n){

    char product [M];
    int i;

    printf("Inserisci il nome del prodotto che vuoi rimuovere: ");
    scanf("%s",product);
    for(i=0;i<n;i++){
        if(!strncmp(product,warehouse[i],strlen(product))){
            price[i]=-2;
            return 1;
        }
    }
    return 0;
}
