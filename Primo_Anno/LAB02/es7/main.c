#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x,y;

    printf("Inserisci un valore di tensione in mV compreso tra 0 e 100: ");
    scanf("%f", &y);

    if(y>=0 && y<=20) {
        x=(y*3.0)/4;
    }


    else if(y>=20 && y<=55) {
        x=(57.0/7)+12.0/35*y;

    }

    else if(y>=55 && y<=100) {
        x=(8.0/45)*y;
        x=x+(155.0/9);
    }

    else {
        printf("TRA ZERO E CENTO HO DETTO!!");
    }

    printf("%f",x);
    return 0;
}
