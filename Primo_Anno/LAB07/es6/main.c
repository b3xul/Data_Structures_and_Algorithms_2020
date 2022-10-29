#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 100
WHAT
int main()
{
    char s[N+1];
    int i=0;

    printf("Inserisci un testo:\n\n");

    do{
        s[i]=getchar();
        i++;
    }
    while((s[i]!='\n'&&s[i-1]!='\n')&&i<N);

    printf("%s\n\n",s);

    s[0]=toupper(s[0]);
    for(i=0;i<N;i++){
        if(isspace(s[i])&&isalpha(s[i+1])){
            s[i+1]=toupper(s[i+1]);
        }
    }
    printf("%s\n\n",s);

    return 0;
}
