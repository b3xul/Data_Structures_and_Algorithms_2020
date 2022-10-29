#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int K=2;
    int a,b,c,d;
    float x;

    printf("Dammi 4 parametri gentilmente cosi' facciamo ax+bcx+dK\n");
    scanf("%d%d%d%d",&a,&b,&c,&d);
    x=(float)(-d*K)/(a+b*c);
    if(a+b*c==0)
        printf("Non si puo' fare!");
    else
    printf("x vale= %f", x);

    return 0;
}
