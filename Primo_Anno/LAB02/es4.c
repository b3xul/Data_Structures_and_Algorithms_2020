#include <stdio.h>
#include <stdlib.h>

int main()
{
   int var1,var2;
    var1=25;
    var2=-53;

    printf("var2 prima vale %d\n", var2);
    printf("var1 prima vale %d\n", var1);

    var1=var1+var2;
    var2=var1-var2;
    var1=var1-var2;


    printf("var2 ora vale %d\n", var2);
    printf("var1 ora vale %d", var1);

    return 0;
}
