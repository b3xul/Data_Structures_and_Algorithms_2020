#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    float c;

    printf("Inserisci 2 numeri interi: ");
    scanf("%d%d",&a,&b);

    c=(float)(a+b)/2;

    printf("La media tra i tuoi 2 valori e': %f",c);

    return 0;
}
