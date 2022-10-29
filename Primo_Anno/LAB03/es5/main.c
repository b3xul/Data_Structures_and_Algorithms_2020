#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a,b,c;
    printf("Inserisci la lunghezza dei tuoi 3 lati: ");
    scanf("%f%f%f",&a,&b,&c);

    if(a<0||b<0||c<0) {
        printf("Un vero triangolo ha dei lati positivi!!");
    }

    else if(a>(b+c)||b>(a+c)||c>(a+b)) {
        printf("Mi dispiace ma non sei valido..");
    }

    else if(a==(b+c)||b==(a+c)||c==(a+b)) {
        printf("SEI UN DEGENERATO!");
    }

    else if (a<(b+c)&&b<(a+c)&&c<(a+b)) {
        printf("Complimenti, sei vaido, ci sei quasi!\n");

        if(a==b&&b==c) {
            printf("Sei equilatero!\n");
        }
        else if(a==b||a==c||b==c) {
            printf("Sei isoscele!\n");
        }
        else {
            printf("Mi spiace ma ho delle cattive notizie.. Lei e' scaleno!\n");
        }

        if ((a*a)==(b*b+c*c)||(b*b)==(a*a+c*c)||(c*c)==(a*a+b*b)) {
            printf("MA SONO VERAMENTE EUFORICO!! SEI UN TRIANGOLO RETTANGOLO!!");
        }

        }
    return 0;
}
