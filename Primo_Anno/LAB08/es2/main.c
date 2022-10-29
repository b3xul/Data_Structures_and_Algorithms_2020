#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 50

int main()
{
    int i;int parole=0;
    char s[N];

    printf("Inserisci una stringa!\n");
    gets(s);
    puts(s);
    printf("\n");
    for(i=0;i<strlen(s);i++){

        if(islower(s[i])){
            s[i]=toupper(s[i]);
        }
        if(!isalnum(s[i])){
            s[i]='_';
        }
        if(isdigit(s[i])){
            s[i]='*';
        }
    }
    puts(s);
    printf("\n");

    for(i=0;i<strlen(s);i++){
        if(s[i]=='_'&&s[i+1]!='_'){
            parole++;
        }
    }
    printf("Qua ci sono %d parole",parole);
    return 0;
}
