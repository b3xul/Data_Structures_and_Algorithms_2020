#include <stdio.h>
#include <stdlib.h>

int main()
{
    int g,m,a;

    printf("Inserisci una data nella forma gg/mm/aaaa: ");
    scanf("%d/%d/%d",&g,&m,&a);

    if(g<1||g>31){
        printf("Non e' un giorno valido!");
    }
    else if(m<1||m>12){
        printf("Non e' un mese valido!");
    }

    else{
        switch(m){
        case 1: printf("%d Gennaio %d",g,a); break;
        case 2: printf("%d Febbraio %d",g,a); break;
        case 3: printf("%d Marzo %d",g,a); break;
        case 4: printf("%d Aprile %d",g,a); break;
        case 5: printf("%d Maggio %d",g,a); break;
        case 6: printf("%d Giugno %d",g,a); break;
        case 7: printf("%d Luglio %d",g,a); break;
        case 8: printf("%d Agosto %d",g,a); break;
        case 9: printf("%d Settembre %d",g,a); break;
        case 10: printf("%d Ottobre %d",g,a); break;
        case 11: printf("%d Novembre %d",g,a); break;
        case 12: printf("%d Dicembre %d",g,a); break;
                  }
        }

    return 0;
}
