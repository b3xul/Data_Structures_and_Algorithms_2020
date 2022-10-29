#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define M 100

typedef struct nomi{
    char nome[20+1];
    char cognome[20+1];
    char fisso[20+1];
    char mobile[20+1];
}nomi; //<-- attento con la typedef//

int inserimento(nomi *,int); //vettore, dimensione vettore, indice riempimento//

int main()
{
    nomi utenti[M];
    char choice;
    int n=0;
    int i;

    printf("Scegli l'operazione da eseguire:\na. A:Inserisci nuovo nominativo\nb. B:Stampa rubrica\nc. C:Esci dal programma.\n");
    scanf("%c",&choice);
    toupper(choice);

    while (choice!='\0'){
        switch(choice){
            case 'A':   inserimento(utenti,M);
                        break;
            case 'B':   for(i=0;i<=n;i++){
                            printf("%s ",utenti[i].nome);//per passare vettore di struct (nomi *user, int dim)//
                            printf("%s ",utenti[i].cognome);
                            printf("%s ",utenti[i].fisso);
                            printf("%s ",utenti[i].mobile);
                            printf("\n");
                        }

            case 'C':   return 0;
                        break;

            default:    printf("Scelta non disponibile\n");

        }
    }
    return 0;
}

int inserimento(nomi *utenti,int M){
    print("Inserisci il nome del tuo amico: ");
    scanf("%s",utenti.nome[n]);
    printf("\n");
    print("Inserisci il cognome del tuo amico: ");
    scanf("%s",utenti.cognome[n]);
    printf("\n");
    print("Inserisci il numero fisso del tuo amico: ");
    scanf("%s",utenti.fisso[n]);
    printf("\n");
    print("Inserisci il numero di cellulare del tuo amico: ");
    scanf("%s",utenti.mobile[n]);
    printf("\n");



    int i;
    char choice;


    for(i=0;i<n;i++){
        if(strcmp(user.nome[n],user.nome[i]==0)&&(strcmp(user.cognome[n],user.cognome[i]==0)){
            printf("E' gia' presente %s %s in rubrica, sei sicuro di volerne cambiare il numero? Y per procedere, N per annullare l'operazione: ",user.nome[n],user.cognome[n]);
            scanf("%c",&choice);
            toupper(choice);

            switch(choice){
                case 'Y':   user.fisso[i]=user.fisso[n];
                            user.mobile[i]=user.mobile[n];
                            n--;
                            break;

                case 'N':   printf("Operazione annullata"); return -1;
                            break;

                default:    printf("Scelta non disponibile.");
                }
        }
    }
    n++;
    return 0;
}
