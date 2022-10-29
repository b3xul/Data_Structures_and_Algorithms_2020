#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int main()
{
    int a,b,c,D;
    int overflow;
    int terna_trovata;
    int eccede_limite;

    int val_max=sqrt(INT_MAX);

    for(a=1;a<=val_max;a++){
            overflow=0;

            for(b=a;b<val_max&&overflow==0;b++){
                terna_trovata=0;
                eccede_limite=0;    //c^2>a^2+b^2//
                D=a*a+b*b;


                    for(c=b;(c<=val_max) && (overflow==0) && (terna_trovata==0) && (eccede_limite==0) ;c++){

                        if(D<0){
                            overflow=1;
                        }
                        else if(c*c==D){
                            terna_trovata=1;
                            printf("La terna %d^2+%d^2=%d^2 e' pitagorica.\n",a,b,c);
                        }
                        else if(c*c>D){
                            eccede_limite=1;
                        }
                    }
            }
        }

    return 0;
}
