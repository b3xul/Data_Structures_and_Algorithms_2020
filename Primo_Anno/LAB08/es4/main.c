#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 60
#define M 5

int main()
{
    char s[N+1];
    char words[M][N+1];
    int i;
    int parole=M;
    int tot=0;
    int counter[N]={0};

    for(i=0;i<M;i++){
        words[i][0]='\0';
    }

    printf("Perche' non inserire qualche parola? Prego: \n");
    gets(s);

   /* int dentro=0;
    for(i=0;i<N&&parole<5;i++){
        if(isalpha(s[i])&&dentro==0){
           dentro=1;

           }
        if(isspace(s[i])&&dentro==1){
            parole++;
            dentro=0;
           }
    }
    */

    sscanf(s,"%s%s%s%s%s",words[0],words[1],words[2],words[3],words[4]);
    for(i=0;i<M;i++){
        if(words[i][0]=='\0'){
            parole--;
        }
    }

    printf("La stringa contiene %d parole\n",parole);

    for(i=0;i<parole;i++){
        tot=strlen(words[i])+tot;
        counter[strlen(words[i])]++;
    }

    printf("La lunghezza media delle parole e' %f caratteri\n",(float)tot/parole);

    printf("La stringa contiene:\n");

    for(i=0;i<N;i++){
        if(counter[i]!=0){
        printf("\t%d parola/e da %d carattere/i\n",counter[i],i);
        }
    }



    return 0;
}
