#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 50

int main()
{
    char s1[N];char s2[N];
    int i,j,alf=0,num=0,pos=-1;
    int uguali=1;

    printf("Inserisci cose: ");
    scanf("%s",s1);
    printf("%s\n",s1);

    printf("La stringa e' lunga %d\n", strlen(s1));

    for(i=0;i<strlen(s1);i++){
        if(isalpha(s1[i])){
            alf++;
        }
        if(isdigit(s1[i])){
            num++;
        }
    }
    printf("La stringa contiene %d caratteri alfabetici\n", alf);
    printf("La stringa contiene %d caratteri numerici\n", num);

    printf("Inserisci altre cose: ");
    scanf("%s",s2);
    for(i=0;i<strlen(s1)&&pos==-1;i++){
            if(s1[i]==s2[0]){
                pos=i;
            }
    }
    for(i=pos,j=0;i<strlen(s1)&&j<strlen(s2)&&uguali==1;i++,j++){

                if(s1[i]!=s2[j]){
                        uguali=0;
                }

    }
    if(uguali==1&&pos!=-1){
        printf("La seconda stringa e' contenuta nella prima");
    }
    else{
        printf("La seconda stringa non e' contenuta nella prima");
    }

    return 0;
}
