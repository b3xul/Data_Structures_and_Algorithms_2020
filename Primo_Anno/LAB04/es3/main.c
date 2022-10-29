#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    int i=0; //zero è l'elemento neutro della somma per cui non ne influenza il risultato//

    while(x!=0){
    printf("Inserisci un numero: (prima o poi dammi zero): ");
    scanf("%d",&x);
    i=x+i;
    }



    printf("La somma dei valori da te inseriti e' %d",i);

    return 0;
}
