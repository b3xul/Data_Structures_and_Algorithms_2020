#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *message=fopen("Message.txt","w");
    int i;
    char ch=2;
    fprintf(message,"Questo e' il mio tentativo!\n");
    /*for(i=0;i<256;i++){
        ch=i;
        fprintf(message,"%d: |%c|\n",i,ch);
    }*/
    for(i=0;i<2000;i++)
        fprintf(message,"%c",ch);
    fprintf(message,"Ha funzionato? no, lol");

    return 0;
}
