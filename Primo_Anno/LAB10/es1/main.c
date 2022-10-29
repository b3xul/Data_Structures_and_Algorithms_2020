#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]) //argc numero di argomenti. argv[0] nome programma. argv[1,2,3...] argomenti inseriti//
//per entrare: bin debug, es1.exe//
//se errore "-static-libgcc" sotto project,build options, linker settings, a destra//
//oppure da codeblocks: project, set program's arguments//

//argomenti sono tutte stringhe, ma come faccio a sapere se sono numeri?//
//per convertirli int n; n=atoi(arg[i]) (argument to integer) ma atoi restituisce zero sia se l'argomento e' zero e sia se non e' un numero!//
//strtoll funzione giusta, noi non la sappiamo, quindi usiamo sscanf("argv[i],"%d",n)!=0 (numero di argomenti letti correttamente)//
//difetto: anche ciao-123 viene letto come -123...//
//N.B. all'esame se dice esplicitamente di controllare allora sscanf, altrimenti se si assume che siano corretti basta atoi. se non dice niente farli alla fine//

{
    int x,y,z;

    if(argc!=3){
        printf("Errore nel numero di argomenti!\n");
        return -3;
    }
    if(sscanf(argv[1],"%d",&x)!=1||x<-10000||x>10000){
        printf("Errore nel primo argomento!\n");
        return -1;
    }

    if(sscanf(argv[2],"%d",&y)!=1||y<-10000||y>10000){
        printf("Errore nel secondo argomento!\n");
        return -2;
    }

    x=atoi(argv[1]);
    y=atoi(argv[2]);

    z=x+y;

    printf("La somma degli argomenti vale: %d",z);
    return 0;
}
