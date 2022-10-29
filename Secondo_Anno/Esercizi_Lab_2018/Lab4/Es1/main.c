#include <stdio.h>
#include <stdlib.h>

int gcd(int a,int b);

int main()
{
    int a=26,b=15;
    printf("Gcd tra %d e %d=%d",a,b,gcd(a,b));

    return 0;
}

int gcd(int a,int b){
    /*Casi terminali*/
    if(a==1||b==1)  //Non evitabile
        return 1;
    if(a==b)
        return a;

    /*Ricorsione*/
    if(a%2==0){  //a pari
        if(b%2==0)  //entrambi pari
            return 2*gcd(a/2,b/2);
        else    //a pari e b dispari Inverte a e b (b diventa maggiore di a e si rompe se non ci fosse la condizione a==1||b==1) Alternativamente all'inizio di ogni ricorsione faccio sì che a sia > b
            return gcd(b,a/2);
    }
    // a dispari
    if(b%2==0)  //a dispari, b pari
        return gcd(a,b/2);
    //entrambi dispari
    return gcd((a-b)/2,b);

}
