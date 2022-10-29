#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c=1;
    int occhio_c=0;
    int exc='\0';

    printf("Inserisci qualche riga di testo:\n");

    while(c!=EOF){

        c=getchar();

        if(occhio_c==1){
            if(c=='h'){
                putchar('k');
                occhio_c=0;
            }
            else{
                putchar(exc);
                putchar(c);
                occhio_c=0;
            }
        }
        else if(c=='c'){
            occhio_c=1;
        }
        else if(exc==c){

        }
        else{
            putchar(c);
        }

        exc=c;
    }

    return 0;
}
