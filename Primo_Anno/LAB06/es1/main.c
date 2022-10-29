#include <stdio.h>
#include <stdlib.h>
#define N 5

int main()
{
    int v[N]={0};
    int i,j,palindroma;
    printf("Scrivimi qualche numero: ");

    for(i=0;i<N;i++)
    scanf("%d",&v[i]);

    palindroma=1;

    for(i=0,j=N-1;i<j&&palindroma==1;i++,j--){
        if(v[i]!=v[j]){
            palindroma=0;
        }

    }

    if(palindroma==0){
        printf("La serie non e' palindroma");
    }
    else{
        printf("La serie e' palindroma");
    }


/*    for(i=0;i<N;i++)
    printf("%d",v[i]);
*/
    return 0;
}
