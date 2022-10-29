#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c;
    float x;

    printf("Inserisci a,b,c: ");
    scanf("%d%d%d",&a,&b,&c);

    if(a==0){
        x=(float)-c/b;
        printf("x vale %f",x);
        if (b==0){
            printf("Quella roba non e' un'equazione!");
        }
    }
    else{
        if((b*b-4*a*c)>0){
            printf("L'equazione ha due soluzione REALI distinte");
        }
        else if ((b*b-4*a*c)==0){
            printf("L'equazione ha due soluzione REALI coincidenti");
        }
        else{
            printf("L'equazione non ha soluzioni reali");
        }
    }
    return 0;
}
