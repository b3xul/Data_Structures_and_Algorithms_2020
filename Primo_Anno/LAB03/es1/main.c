#include <stdio.h>
#include <stdlib.h>

int main()
{
    int int_1,int_2;
    float float_1,float_2;

    printf("Inserisci 2 interi e 2 flottanti:\n");
    scanf("%d%d%f%f",&int_1,&int_2,&float_1,&float_2);

    printf("int_1 int_2 \t%05d %05d\nfloat_1 \t%05.2f\nfloat_2 /t%0.3f",int_1,int_2,float_1,float_2);
    //printf("int_1 int_2 \t%05d %05d\n", int_1,int_2);//
    //printf("float_1 \t%05.2f", float_1);//
    //printf("float_2 \t%0.3f", float_2);//

    return 0;
}
