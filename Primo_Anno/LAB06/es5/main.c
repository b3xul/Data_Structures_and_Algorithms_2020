#include <stdio.h>
#include <stdlib.h>

float power(int,int); //prototipo: tipo risultato_nome(tipi argomenti)//

int main()
{
    int base,exp; //base e exp parametri effettivi//
    float risultato;

    printf("Forniscimi base e esponente grazie: ");
    scanf("%d%d",&base,&exp);

    risultato=power(base,exp);

    printf("%d elevato alla %d = %f",base,exp,risultato);

    return 0;
}


float power(int a,int b){ //a e b parametri formali//
    float R=1.0;
    int i;

    for(i=1;i<=b;i++){
        R=R*a;
        }
    if(b<0){
        for(i=1;i<=-b;i++){
        R=R*a;
        }
        R=(float)1/R;
    }


    return R;
}
