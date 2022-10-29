#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 73

int main()
{
    char s[N+1];
    int i;
    int parole=1;
    int righe=1;
    float length=0;
    int spazi=0;

    printf("Inserisci un testo:\n\n");

    for(i=0;i<N;i++){
        s[i]=getchar();
    }
    printf("%s\n\n",s);

    s[0]=toupper(s[0]);
    for(i=0;i<N;i++){
        if(isspace(s[i])&&isalpha(s[i+1])){
            s[i+1]=toupper(s[i+1]);
            parole++;
        }
        if(s[i]=='\n'){
            righe++;
        }
        if(s[i]==' '){
            spazi++;
        }
    }
    printf("%s\n\n",s);
    length=(float)(N-spazi)/parole;

    printf("Numero di righe: %d\n",righe);
    printf("Numero di parole: %d\n",parole);
    printf("Lunghezza media di una parola: %f\n",length);

    return 0;
}
