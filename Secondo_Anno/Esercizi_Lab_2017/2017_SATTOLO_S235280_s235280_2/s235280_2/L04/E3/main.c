#include <stdio.h>
#include <stdlib.h>

void Hofstadter(int n);
int HofstadterR(int n, int v[]);

int main()
{
    int n;

    printf("Inserisci un intero positivo: \n");
    scanf("%d",&n);

    printf("La sequenza di Hofstadter di %d e': ",n);

    Hofstadter(n);

    return 0;
}

void Hofstadter(int n){

    int i;
    int *v;

    v=(int *)malloc(n*sizeof(int));

    for(i=0;i<n;i++)
        v[i]=-1;

    HofstadterR(n,v);

    return;
}

int HofstadterR(int n, int v[]){

    int val;

    if(n==0){
        if(v[0]==-1){ //quando è la primissima esecuzione stammpa lo zero (primo elemnto sequenza)
            v[0]=0;
            printf("0, ");
        }
        return 0;
    }

    if(v[n-1]==-1){
        val=n-HofstadterR(HofstadterR(HofstadterR(n-1,v),v),v);
        printf("%d, ",val);
        v[n-1]=val;
        return val;
    }

    return v[n-1];

}
