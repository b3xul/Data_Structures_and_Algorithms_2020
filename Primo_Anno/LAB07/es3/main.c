#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char c;
    int num=0;
    int alf=0;
    int maiu=0;
    int deci=0;
    int spac=0;
    int parole=0;
    int words=0;
    printf("Inserisci caratteri: ");
    while(c!='\n'){
        c=getchar();
        num++;                  //numero di caratteri
            if(isalpha(c)){
                alf++;          //numero di caratteri alfabetici
                parole=1;
            }
            if(isupper(c)){     //numero di caratteri alfabetici maiuscoli
                maiu++;
            }
            if(isdigit(c)){     //numero di caratteri numerici
                deci++;
            }
            if(isspace(c)){     //numero di caratteri di spaziatura
                spac++;
            }
            if(parole==1&&!isalpha(c)){
                parole=0;
                words++;
            }


    }
    printf("Hai introdotto %d caratteri di cui %d alfabetici, %d maiuscoli, %d decimali, %d spazi\n",num-1,alf,maiu,deci,spac-1);
    printf("%d sono parole di senso piu' o meno compiuto",words);

    return 0;
}
