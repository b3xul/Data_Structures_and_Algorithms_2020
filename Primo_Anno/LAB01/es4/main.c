#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a,b,x;
    char segno;

    printf("Inserisci un'equazione nella forma ax+b=0\n");
    scanf("%fx%c%f=0",&a,&segno,&b);

    x=(-b)/a;
    printf("x=%f", x);


    return 0;
}
