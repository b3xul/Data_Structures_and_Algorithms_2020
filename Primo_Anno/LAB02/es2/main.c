#include <stdio.h>
#include <stdlib.h>

int main()
{
    int var1,var2,tmp;
    var1=-3;
    var2=12;
    tmp=var1;
    var1=var2;
    var2=tmp;


    printf("var2 vale %d\n", var2);
    printf("var1 vale %d", var1);

    return 0;
}
