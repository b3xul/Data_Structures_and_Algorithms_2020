#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char c1;
    char c2;

    printf("Give me roba: ");
    c1=getchar();

    while (getchar() != '\n');


    printf("Give me other roba: ");
    c2=getchar();
    while (getchar() != '\n');

    if(isalpha(c1)&&isalpha(c2)){
        if(c1<c2){
            printf("%c %c",c1,c2);
        }
        if(c1>c2){
            printf("%c %c",c2,c1);
        }
    }
    else{
        if(isdigit(c1)||isdigit(c2)){
            printf("Se almeno uno dei due caratteri e' una cifra");
        }
    }
    return 0;
}
