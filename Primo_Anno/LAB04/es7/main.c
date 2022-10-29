#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int intero,intero_max;
    long int lungo,lungo_max;
    unsigned int senza_segno,senza_segno_max;

    intero=1;

    while(intero>=0){
        intero_max=intero;
        intero++;
    }

    printf("Il massimo int rappresentabile e': %d\n",intero_max);

    printf("The maximum value of INT = %d\n", INT_MAX);


    lungo=1;

    while(lungo>=0){
        lungo_max=lungo;
        lungo++;
    }

    printf("Il massimo long int rappresentabile e': %ld\n",lungo_max);

    printf("The maximum value of LONG = %ld\n", LONG_MAX);

    senza_segno=0;
    senza_segno_max=1;

    while(senza_segno<senza_segno_max){
        senza_segno++;
        senza_segno_max++;
    }
    printf("Il massimo unsigned int rappresentabile e': %u\n",senza_segno);

    printf("The maximum value of UNSIGNED INT = %u\n", UINT_MAX);

    return 0;
}
