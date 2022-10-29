#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 5

int main()
{
    char s1[N+1];
    char s2[N+1];
    int ora1;
    int ora2;
    int diff=0;
    char s3[4+7+1];
    // Per convertire stringa in numeri: 1 in una stringa indica il codice ascii di 1, si possono fare operazioni usando i codici ascii ('5'-'0')=(codice ascii di 5 meno codice ascii di zero=5)//
    // idem per trovare posizione di una lettera: numero della lettera 'D'=('D'-'A')=3 (A e' la cifra zero);
    printf("Dammi il primo orario (hh:mm): ");
    scanf("%s",s1);

    printf("Dammi il secondo orario (hh:mm): ");
    scanf("%s",s2);

    ora1=(s1[4]-'0')+((s1[3]-'0')*10)+((s1[1]-'0')*60)+((s1[0]-'0')*600);
    ora2=(s2[4]-'0')+((s2[3]-'0')*10)+((s2[1]-'0')*60)+((s2[0]-'0')*600);

    while(s1[2]!=':'||s2[2]!=':'||s1[5]!='\0'||s2[5]!='\0'){
        printf("Formato ora non valido (hh:mm)");
        scanf("%s",s1);
        scanf("%s",s2);
        ora1=(s1[4]-'0')+((s1[3]-'0')*10)+((s1[1]-'0')*60)+((s1[0]-'0')*600);
        ora2=(s2[4]-'0')+((s2[3]-'0')*10)+((s2[1]-'0')*60)+((s2[0]-'0')*600);
    }
    while(ora1>24*60||ora2>24*60){
        printf("Ehhhhh troppo!");
        scanf("%s",s1);
        scanf("%s",s2);
        ora1=(s1[4]-'0')+((s1[3]-'0')*10)+((s1[1]-'0')*60)+((s1[0]-'0')*600);
        ora2=(s2[4]-'0')+((s2[3]-'0')*10)+((s2[1]-'0')*60)+((s2[0]-'0')*600);
    }
    while(s1[3]-'0'>5||s2[3]-'0'>5){
        printf("I minuti! Qualcuno pensi ai minuti!!");
        scanf("%s",s1);
        scanf("%s",s2);
        ora1=(s1[4]-'0')+((s1[3]-'0')*10)+((s1[1]-'0')*60)+((s1[0]-'0')*600);
        ora2=(s2[4]-'0')+((s2[3]-'0')*10)+((s2[1]-'0')*60)+((s2[0]-'0')*600);
    }
    printf("La prima ora corrisponde a %d minuti da mezzanotte\n",ora1);
    printf("La seconda ora corrisponde a %d minuti da mezzanotte\n",ora2);

    if(ora1<ora2){
        diff=ora2-ora1;
        printf("La differenza vale %d\n",diff);
        sprintf(s3,"%d_minuti",diff);
        printf("%s",s3);
    }
    else{
        printf("La prima ora non e' minore della seconda");
    }
    return 0;
}
