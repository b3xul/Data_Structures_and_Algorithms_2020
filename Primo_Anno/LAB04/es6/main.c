#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n,media;
    int i,somma,x;

    printf("Inserisci n: ");
    scanf("%f", &n);

    somma=0;
    media=n-1;

    for(i=1;(i<=10&&media<=n);i++) {
        printf("Inserisci altri numeri interi: ");
        scanf("%d",&x);

        somma=(float)x+somma;
        media=(float)somma/i;

    }

    printf("La media vale %f",media);


    return 0;
}
