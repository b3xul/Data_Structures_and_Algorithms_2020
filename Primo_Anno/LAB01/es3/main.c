#include <stdio.h>
#include <stdlib.h>

int main()
{
    double operand1,operand2,result;
    printf("Ti sommo questi 2 numeri:");
    scanf("%lf%lf",&operand1,&operand2);
    result=operand1+operand2;
    printf("%g + %g = %g",operand1, operand2, result);

    return 0;
}
