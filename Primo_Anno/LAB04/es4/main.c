#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,j;

    printf("Inserisci un valore intero positivo N: ");
    scanf("%d",&n);

    printf("*\n");

    for(i=1;i<=n;i++){ //conta le righe//

        for(j=0;j<=i;j++){ //una riga � fatta cos�//
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
