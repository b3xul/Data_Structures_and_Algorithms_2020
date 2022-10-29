#include <stdio.h>
#include <stdlib.h>

int somma(int n);

int main()
{
    int n,s;

    printf("Inserisci un numero: ");
    scanf("%d",&n);

    s=somma(n);

    printf("La somma delle cifre di cui e' composto %d vale %d",n,s);

    return 0;
}

int somma(int n){
    int s=0;

    if(n/10==0){
        return n;
    }
    s=somma(n/10)+somma(n%10);

    return s;
}
