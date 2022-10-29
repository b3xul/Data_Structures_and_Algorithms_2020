#include <stdio.h>
#include <stdlib.h>

int main()
{
    int int_1,int_2;
    float float_1,float_2;

    printf("Inserisci 1 valore reale:\n");
    scanf("%f",&float_1);

    int_1=int_2=float_2=float_1;

    printf("%d %d %f %f",int_1,int_2,float_1,float_2);
    return 0;
}
