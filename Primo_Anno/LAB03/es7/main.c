#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,d,m,M,diff;

    printf("Inserisci 4 valori interi positivi minori di 1000: ");
    scanf("%d%d%d%d",&a,&b,&c,&d);

    if((a>=0&&b>=0&&c>=0&&d>=0)&&(a<1000&&b<1000&&c<1000&d<1000)){
        if(a>b) {
            if (a>c) {
                if(a>d){
                    printf("A e' il massimo valore\n");
                    M=a;
                }
                else {
                    printf("D e' il massimo valore\n");
                    M=d;
                }
            }
            else {if(c>d) {
                    printf("C e' il massimo valore\n");
                    M=c;
                }
                else {
                    printf("D e' il massimo valore\n");
                    M=d;
                }
            }
        }
        else {
            if(b>c) {
                if(b>d) {
                    printf("D e' il massimo valore\n");
                    M=b;
                }
                else{
                    printf("D e' il massimo valore\n");
                    M=d;
                }
            }
            else if(c>d){
                printf("C e' il massimo valore\n");
                M=c;
            }
                else {
                    printf("D e' il massimo valore\n");
                    M=d;
                }
        }


        if(a<b) {
            if (a<c) {
                if(a<d){
                    printf("A e' il minimo valore\n");
                    m=a;
                }
                else {
                    printf("D e' il minimo valore\n");
                    m=d;
                }
            }
            else if(c<d) {
                    printf("C e' il minimo valore\n");
                    m=c;
                }
                else {
                    printf("D e' il minimo valore\n");
                    m=d;
                }
        }
        else {
            if(b<c) {
                if(b<d) {
                    printf("B e' il minimo valore\n");
                    m=b;
                }
                else{
                    printf("D e' il minimo valore\n");
                    m=d;
                }
            }
            else if(c<d){
                printf("C e' il minimo valore\n");
                m=c;
            }
                else{
                    printf("D e' il minimo valore\n");
                    m=d;
                }
        }

        diff=M-m;
        printf("La massima differenza tra i valori e' %d", diff);
    }
    else {
        printf("ZERO! ERRRORE! BIP!");
    }

    return 0;
}
