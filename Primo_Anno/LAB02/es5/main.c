#include <stdio.h>
#include <stdlib.h>

int main()
{
    float price,tax,receipt;

    printf("Inserisci price e tax:");
    scanf("%f%f",&price,&tax);
    receipt=price+price*tax/100;

    printf("%f",receipt);
    return 0;
}
