#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLLERANZA 0.001

double invsin(double, double,double)
int main()
{
    double a,b,c;
    double x;
    double y;

    printf("Inserisci i due estremi dell'intervallo su cui vuoi trovare l'arcsin: ");
    scanf("%lf%lf",&a,&b);

    while(a<-1||a>1||b<-1||b>1){
        printf("Ascisse non buone!");
        scanf("%lf%lf",&a,&b);
    }

    printf("Inserisci il passo: ");
    scanf("%lf",&c);

    while(c<0){
        printf("Passo non buono!");
        scanf("%lf",&c);
    }

    for(x=a;x<=b;x=x+c){ //calcola tutti i valori di arcsin in quell'intervallo con quel passo//
        y=invsin(-M_PI_2,M_PI_2,x);

    printf("x: %9f  invsin(x)=%9f  arcsinf(x)=%9f  error=%9f\n", x, y, arcsin(x), asin(x)-res );
    }
    return 0;
}
double invsin(double z1,double z2, double k){
        double resto;
        double zm;

        zm=(z1+z2)/2;
        resto=sin(zm)-k;

    while (resto<=-TOLLERANZA||resto>=TOLLERANZA){
            if(sen(zm)>0){
                z1=zm;
            }
            else{
                z2=zm;
            }

    }
    return resto;
}
