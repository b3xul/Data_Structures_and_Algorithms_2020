#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int val1,val2;
    float res;
    char ch;

    if(argc!=4){
        printf("Errore nel numero di argomenti!\n");
        return -4;
    }
    if(sscanf(argv[1],"%d",&val1)!=1){
        printf("Errore nel primo numero!");
        return -1;
    }
    if(sscanf(argv[2],"%d",&val2)!=1){
        printf("Errore nel secondo numero!");
        return -2;
    }
    if(sscanf(argv[3],"%c",&ch)!=1){
        printf("Errore nel carattere inserito!");
        return -3;
    }

    switch(ch){
        case 'a':res=val1+val2;
            break;
        case 'b':res=val1-val2;
            break;
        case 'c':res=val1*val2;
            break;
        case 'd':
            if(val2!=0)res=(float)val1/val2;
            break;
        default:
            printf("Carattere sbagliato!\n");
            return -5;
    }
    printf("Il risultato e' %f",res);
    return 0;
}
