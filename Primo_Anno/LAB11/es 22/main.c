#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct nomi{
    char nome[20+1];
    char cognome[20+1];
    char fisso[20+1];
    char mobile[20+1];
}nomi; //<-- attento con la typedef//



int main()
{
    nomi utenti[100];
    char choice1='z';
    char choice2='z';
    int n=0;
    int i;

    while (choice1!='\0'){
    printf("Scegli l'operazione da eseguire:\na. A: Inserisci nuovo nominativo\nb. B: Stampa rubrica\nc. C: Esci dal programma.\n");
    choice1=getchar();

    choice1=toupper(choice1);


        switch(choice1){
            case 'A':   printf("Inserisci il nome del tuo amico: ");
                        scanf("%s",utenti[n].nome);
                        printf("\n");
                        printf("Inserisci il cognome del tuo amico: ");
                        scanf("%s",utenti[n].cognome);
                        printf("\n");
                        printf("Inserisci il numero fisso del tuo amico: ");
                        scanf("%s",utenti[n].fisso);
                        printf("\n");
                        printf("Inserisci il numero di cellulare del tuo amico: ");
                        scanf("%s",utenti[n].mobile);
                        printf("\n");



                        for(i=0;i<n;i++){
                            if(strcmp(utenti[n].nome,utenti[i].nome)==0&&strcmp(utenti[n].cognome,utenti[i].cognome)==0){
                                printf("E' gia' presente %s %s in rubrica, sei sicuro di volerne cambiare il numero? Y per procedere, N per annullare l'operazione: ",utenti[n].nome,utenti[n].cognome);
                                getchar();
                                scanf("%c",&choice2);

                                choice2=toupper(choice2);

                                switch(choice2){
                                    case 'Y':   strcpy(utenti[i].fisso,utenti[n].fisso);
                                                strcpy(utenti[i].mobile,utenti[n].mobile);
                                                printf("Operazione eseguita con successso.");
                                                n--;
                                                break;

                                    case 'N':   printf("Operazione annullata");
                                                break;

                                    default:    printf("Scelta non disponibile.");
                                    }
                            }
                        }
                        n++;
                        break;
            case 'B':   for(i=0;i<=n;i++){
                            printf("%s ",utenti[i].nome);//per passare vettore di struct (nomi *user, int dim)//
                            printf("%s ",utenti[i].cognome);
                            printf("%s ",utenti[i].fisso);
                            printf("%s ",utenti[i].mobile);
                            printf("\n");
                        }
                        break;

            case 'C':   return 0;
                        break;

            default:    printf("Scelta non disponibile\n");

            }
    getchar();
    }
    return 0;
}


