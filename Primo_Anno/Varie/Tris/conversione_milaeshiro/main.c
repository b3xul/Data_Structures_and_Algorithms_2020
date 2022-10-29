#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int numero;
    char s[7+1];
    int i;

    scanf("%d",&numero);
    scanf("%s",s);

    if(strcmp(s,"milioni")){
        numero=numero*1000000;
    }


    printf("%d",numero);
    return 0;
}
/*
n= "678 milioni"
n= n+0
*/
