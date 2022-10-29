#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x0=0, x1=1, i,x,somma,somma_precedente;



    somma=x0+x1;
    somma_precedente=0;
    x=somma_precedente+somma;

    printf("%d %d ",x0,x1);

    for(i=2;i<20;i++){

        somma=x;
        x=somma+somma_precedente;
        somma_precedente=somma;

        printf("%d ",x);
    }
/*

    int value,valueprec,precprec;
    precprec=0;
    printf(",%d ",precprec);
    valueprec=1;
    printf(",%d ",valueprec);
    value=valueprec+precprec;
    printf(",%d ",value);
    for (i=0;i<10;i++)
    {
        precprec=valueprec;
        valueprec=value;
        value=valueprec+precprec;
        printf(",%d ",value);
    }
*/
    return 0;
}
