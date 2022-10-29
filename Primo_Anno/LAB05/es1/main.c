#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,max,min,resto;

    do {printf("Inserisci 2 numeri interi positivi: ");
    scanf("%d%d",&a,&b);
    }
    while(a<0||b<0);

    if(a>=b){
        max=a;
        min=b;
    }
    else if(a<b){
        max=b;
        min=a;
    }

    while(resto!=0){
        resto=max%min;
        if(resto!=0){
            max=min;
            min=resto;
        }
    }
        printf("L'MCD vale %d",min);


  /*  if(a>b){

    while(resto!=0){
        resto=a%b;
        if(resto!=0){
            a=b;
            b=resto;
        }
        printf("L'MCD vale %d",b);
    }
    }
    else{
        while(resto!=0){
        resto=b%a;
            if(resto!=0){
            b=a;
            a=resto;
        }
        }
        printf("L'MCD vale %d",a);
    }

    */
    return 0;
}
