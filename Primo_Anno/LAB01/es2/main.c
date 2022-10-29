#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    printf("Inserisci un numero:");
    scanf("%d", &x);
    if(x>=0) {    }
    else {
        x=-x;
    };

    printf("Il valore assoluto del numero selezionato e' %d", x);
    return 0;
}
