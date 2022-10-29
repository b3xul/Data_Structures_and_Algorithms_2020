#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x;
    printf("Inserisci un numero: ");
    scanf("%f", &x);
    if(x>=0) {
        printf("Il valore assoluto del numero scelto e': %f", x);
    }
    else  {
        x=-x;
        printf("Il valore assoluto del numero scelto e': %f", x);
    }
    return 0;
}
