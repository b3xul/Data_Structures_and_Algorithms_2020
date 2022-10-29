#include <stdio.h>
#include <stdlib.h>

int main()
{

    int A=1,B=0,C;

    C = ( (A && B) || (!B) ) && (!A);

    if(C==0) {
        printf("C e' falso");
    }
    else{
        printf("C e' vero");
    }
    return 0;
}
