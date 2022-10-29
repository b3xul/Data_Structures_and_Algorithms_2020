#include <stdio.h>
#include <stdlib.h>
#define P 50
#define W 50

int power(int,int);

int main()
{
    int i,j,k,m,q,N,B,Q,R,N2,N3;
    int v[W]={0};



    for(i=2;i<=P;i++){ //ripeti per ogni numero
            N=i; //numero decimale
            for(j=2;j<P;j++){ //ripeti per ogni base
                    N=i;
                    B=j; //base
                    k=0; //indice vettore resti:posizione e valore della posizione (al contrario)
                    N2=0; //numero riconvertito in decimale
                    while(N!=0){ //numero decimale
                            Q=N/B;
                            R=N%B;
                            v[k]=R; //converte e mette in un vettore volutamente all'inizio invece che alla fine
                            N=Q;
                            N2=v[k]*power(j,k)+N2; //somma dal più piccolo
                            k++;
                        }
            N3=0;
            q=0;
            for(m=k;m>0;m--,q++){
            N3=v[m-1]*power(j,q)+N3; //cifra convertita*base^valore della posizione (somma dal più grande)
            }

            if(N2==N3){
                printf("Il numero %d risulta palindromo in base %d\n",i,B);
                }
        }
    }
    return 0;
}

int power(int a,int b){ //a e b parametri formali//
    int result=1;
    int i;

    for(i=1;i<=b;i++){
        result=result*a;
        }
    return result;
}
