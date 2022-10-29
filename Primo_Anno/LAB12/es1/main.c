#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char *argv[])
{
    if(argc!=2)
        printf("Errore nel numero di argomenti.\n");

    FILE *fi=fopen(argv[1],"r");
    if(fi==NULL)
        printf("Errore nell'apertura del file di input.\n");

    Dizionario diz;
    diz.dim=0;
    char buff[S];
    int i,trovato;

    while(fscanf(fi,"%s",buff)!=EOF){
        trovato=0;
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

    for(i=0;i<diz.dim;i++)
        printf("%s %d occorrenze\n",diz.vett[i].parola,diz.vett[i].occ);

    fclose(fi);
    return 0;
}

