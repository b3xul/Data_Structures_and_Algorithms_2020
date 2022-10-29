#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nambero;
    printf("Escimi un numero romano: ");
    scanf("%c",&nambero);

    switch(nambero) {
    case 'I':nambero=(int)1;
    break;
    case 'V':nambero=(int)5;
    break;
    case 'X':nambero=(int)10;
    break;
    case 'L':nambero=(int)50;
    break;
    case 'C':nambero=(int)100;
    break;
    default:printf("Per le altre funzioni compra il DLC :)");
    }

    printf("%d", nambero);
    return 0;
}
