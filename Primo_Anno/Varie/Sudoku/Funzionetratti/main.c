#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    printf("Inseriscimi i valori di x: \n:)\n");

    FILE *f1;
    f1=fopen(stdin,"r");
    while(fscanf(stdin,"%d",&x)!=EOF){
        if(x<0) printf("%d ",-2*x);
        else if(x>0) printf("%d ",2*x);
        else printf("0 ");
        printf("\n");
    }

    return 0;
}
