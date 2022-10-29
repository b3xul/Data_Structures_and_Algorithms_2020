#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#define P 1000  //NUMERO PAROLE
#define S 15    //LUNGHEZZA PAROLE

typedef struct Voce_{
    char parola[S];
    int occ;
}Voce;

typedef struct Dizionario_{
    Voce vett[P];
    int dim;
}Dizionario;

char *addch(char *string, char ch);

int main(int argc, char *argv[])
{
    if(argc!=2)
        printf("Errore nel numero di argomenti.\n");

    FILE *fi=fopen(argv[1],"r");
    if(fi==NULL)
        printf("Errore nell'apertura del file di input.\n");

    FILE *fp=fopen("particelle.txt","r");
    if(fp==NULL)
        printf("Errore nell'apertura del file di particelle.\n");

    Dizionario diz;
    diz.dim=0;
    Dizionario part;
    part.dim=0;

    char buff[S],ch;
    int i,trovato,particella;

    while(fscanf(fp,"%s",buff)!=EOF){
        trovato=0;
        for(i=0;i<part.dim&&!trovato;i++)
            if(stricmp(buff,part.vett[i].parola)==0){
                part.vett[i].occ++;
                trovato=1;
            }
        if(!trovato){
            strcpy(part.vett[i].parola,buff);
            part.vett[i].occ=1;
            part.dim++;
        }
    }
    strcpy(buff,"\0");

    while(fscanf(fi,"%c",&ch)!=EOF){
        if(isalnum(ch)){
            strcpy(buff,addch(buff,ch));
        }
        else if(strcmp(buff,"\0")!=0){
            trovato=0;
            particella=0;
            for(i=0;i<part.dim;i++) //buff è una particella?
                if(stricmp(buff,part.vett[i].parola)==0)
                    particella=1;

            if(!particella){
                for(i=0;i<diz.dim&&!trovato;i++)
                    if(stricmp(buff,diz.vett[i].parola)==0){
                        diz.vett[i].occ++;
                        trovato=1;
                    }
                if(!trovato){
                    strcpy(diz.vett[i].parola,buff);
                    diz.vett[i].occ=1;
                    diz.dim++;
                }
            }
            buff[0]='\0';
        }

    }

    for(i=0;i<diz.dim;i++)
        printf("%s %d occorrenze\n",diz.vett[i].parola,diz.vett[i].occ);

    fclose(fi);
    fclose(fp);
    return 0;
}

char *addch(char *string, char ch){

    char temp[2];
    temp[0]=ch;
    temp[1]='\0';

    strcat(string,temp);

    return string;

}
