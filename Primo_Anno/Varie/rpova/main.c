#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>

int main()
{
    float a=FLT_MAX;
    printf("%f\n",a);
    float e= 10000000000000000000000.0;
    float b=a+e;

    printf("%f\n",b);
    printf("Aggiungendo %f\n",e);

    int c=INT_MAX;
    printf("%d\n",c);
    int d=c+1;
    printf("%d\n",d);

    float pmax= 3.5e38;
    float nmin=-3.3e38f;
    float min= 1.0e-38f;
    printf("%f  %f  %f",pmax,nmin,min);

    return 0;
}
