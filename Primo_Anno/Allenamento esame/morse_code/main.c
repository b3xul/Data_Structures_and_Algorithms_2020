#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct{
        char lettera;
        char codice[4+1];
}legenda;

int main(int argc,char *argv[])
{
    if(argc!=3){
        fprintf(stderr,"Errore nel numero di argomenti!\n");
        return -1;
    }
    FILE *f1;
    FILE *f2;

    f1=fopen("morse.txt","r");
    if(f1==NULL){
        fprintf(stderr,"Errore nell'apertura del primo file\n");
        return -2;
    }
    f2=fopen(argv[2],"r");
    if(f2==NULL){
        fprintf(stderr,"Errore nell'apertura del secondo file\n");
        return -3;
    }

    legenda morse[26];
    int i;
    int trovato=0;
    char car;
    char str[4+1];

    for(i=0;i<26;i++){
        fscanf(f1,"%c%s",&morse[i].lettera,morse[i].codice);
        fgetc(f1);
    }
    if(strcmp(argv[1],"-c")==0){
        car=fgetc(f2);
        while(car!=EOF){
            if(isalpha(car)){
                car=toupper(car);
                for(i=0;i<26&&!trovato;i++){
                    if(car==morse[i].lettera){
                        printf("%s ",morse[i].codice);
                        trovato=1;
                    }
                }
            }
            car=fgetc(f2);
            trovato=0;
        }
    }
    else if(strcmp(argv[1],"-d")==0){
        while(fscanf(f2,"%s",str)!=EOF){
            for(i=0;i<26&&!trovato;i++){
                if(strcmp(str,morse[i].codice)==0){
                    printf("%c",morse[i].lettera);
                    trovato=1;
                }
            }
            trovato=0;
        }
    }
    else{
        printf("Argomento errato, inserire -c o -d seguito dal nome del file per codificare o decodificare.");
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
