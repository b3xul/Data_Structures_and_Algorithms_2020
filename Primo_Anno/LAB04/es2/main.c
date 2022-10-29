#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;

    printf("Inserisci un numero intero tra 1 e 12: ");
    scanf("%d",&x);

    if(x<1||x>12){
        printf("Non e' un numero intero tra 1 e 12!");
    }
    else{
        switch(x){
        case 1: printf("Gennaio"); break;
        case 2: printf("Febbraio"); break;
        case 3: printf("Marzo"); break;
        case 4: printf("Aprile"); break;
        case 5: printf("Maggio"); break;
        case 6: printf("Giugno"); break;
        case 7: printf("Luglio"); break;
        case 8: printf("Agosto"); break;
        case 9: printf("Settembre"); break;
        case 10: printf("Ottobre"); break;
        case 11: printf("Novembre"); break;
        case 12: printf("Dicembre"); break;
        }
    }
    return 0;
}
