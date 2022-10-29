#include <stdio.h>
#include <stdlib.h>

int main()
{
    float z;
    int x,y;

    printf("Introduci un numero:");
    scanf("%d", &x);
    y=5;
    z=x/y;

    printf("Il risultato di %d fratto %d e' %f", x, y, z);

    return 0;
}
