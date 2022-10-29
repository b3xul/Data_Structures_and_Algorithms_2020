#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a;
    float x,y;

    printf("Inserisci una temperatura in Celsius (C) o in Fahrenheit (F): ");
    scanf("%f%c",&x,&a);

    if (a=='F'||a=='f'){
        //da Fahrenheit a Celsius//
        y=(x-32)/1.8;
        printf("La temperatura in Celsius sarebbe %f °C", y);
    }
    else if (a=='C'||a=='c'){
        //da Celsius a Fahrenheit//
        y=(x*1.8)+32;
        printf("La temperatura in Fahrenheit sarebbe %f F", y);
    }
    else {
        printf("Scala di temperatura non valida");
    }

    return 0;
}
