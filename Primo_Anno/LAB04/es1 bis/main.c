#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int a,b,c,d;
    float x,x1,x2;
    double radice;

    printf("Inserisci a,b,c: ");
    scanf("%d%d%d",&a,&b,&c);

    d=(b*b-4*a*c);
    radice=sqrt(d);

    if(a==0){
        x=(float)-c/b;
        printf("x vale %f",x);
        if (b==0){
            printf("Quella roba non e' un'equazione!");
        }
    }
    else{
        if(d>0){
            printf("L’equazione ha due soluzione REALI distinte\n");

            x1=(-b+radice)/2*a;
            x2=(-b+radice)/2*a;

            printf("x1 vale %g\n", x1);
            printf("x2 vale %g", x2);
        }
        else if (d==0){
            printf("L’equazione ha due soluzione REALI coincidenti\n");

            x=(-b-radice)/2*a;
            printf("x vale %g", x);
        }
        else{
            printf("L'equazione non ha soluzioni reali");
        }
    }
    return 0;
}
