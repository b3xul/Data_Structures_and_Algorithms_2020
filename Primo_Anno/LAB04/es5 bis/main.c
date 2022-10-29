#include <stdio.h>
#include <stdlib.h>

int main()
{

    int x0=1, x1=2, i,x,prodotto,prodotto_precedente;

    prodotto=x0*x1;
    prodotto_precedente=1;
    x=prodotto_precedente*prodotto;

    printf("%d %d ",x0,x1);

    for(i=2;i<20;i++){

        prodotto=x;
        x=prodotto*prodotto_precedente;
        prodotto_precedente=prodotto;

        printf("%d ",x);
    }

    return 0;
}
