#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,j;

    do{
    printf("Inserisci n dispari e maggiore di zero: ");
    scanf("%d",&n);
    }
    while(n<0||n%2==0);

    for(i=0;i<n/2+1;i++){ //conta le righe//

            for(j=0;j<=i;j++){ //stampa gli spazi//
                printf(" ");
            }
            for(j=0;j<n-2*i;j++){ //stampa gli asterischi//
                printf("*");
            }
            for(j=0;j<=i;j++){ //stampa gli spazi//
                printf(" ");
            }
        printf("\n");

    }


    return 0;
}
