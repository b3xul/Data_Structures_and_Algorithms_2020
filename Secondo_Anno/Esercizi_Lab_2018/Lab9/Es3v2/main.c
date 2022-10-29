#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "inventario.h"
#include "pg.h"
#include "personaggi.h"

#define N_OPERATIONS 8

//
int main()
{
    char* prompt[N_OPERATIONS]={"Caricare l'elenco di personaggi (da file)",
                    "Caricare l'elenco di oggetti (da file)",
                    "Aggiungere un nuovo personaggio",
                    "Eliminare un personaggio",
                    "Aggiungere un oggetto dall'equipaggiamento di un personaggio",
                    "Rimuovere un oggetto dall'equipaggiamento di un personaggio",
                    "Mostrare le statistiche di un personaggio",
                    "Termina il programma"};

    invArray_t* tab_inv;    //N.B. invArray_t è un tipo incompleto per cui non posso fare *tab_inv perchè non so cosa contiene!
    tab_inv=inventario_init();

    pgList_t* tab_pg;
    tab_pg=personaggi_init();

    int i,cmd;
    char target1[MAX_STR],target2[MAX_STR];
    FILE* fp;
    pg_t player;

    do{
        for(i=0; i<N_OPERATIONS; i++){
            printf("%d: %s\n", i, prompt[i]);
        }
        printf("Inserire comando> ");
        scanf("%d",&cmd);
        switch(cmd){
            case 0:
                printf("Inserire nome file: ");
                scanf("%s",target1);
                fp=fopen(target1,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                personaggi_leggi(tab_pg, fp);
                personaggi_stampa(tab_pg, stdout);
                break;
            case 1:
                printf("Inserire nome file: ");
                scanf("%s",target1);
                fp=fopen(target1,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                inventario_leggi(tab_inv, fp);
                inventario_stampa(tab_inv, stdout);
                break;
            case 2:
                printf("Inserire nuovo personaggio nel formato <codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>:\n");
                player=pg_new(stdin);
                personaggi_add_player(&player,tab_pg);
                personaggi_stampa(tab_pg, stdout);
                break;
            case 3:
                printf("Inserire codice del personaggio che si vuole eliminare: ");
                scanf("%s",target1);
                player=personaggi_estrai_player(target1,tab_pg);
                if(pg_check_void(player))
                    printf("Codice non trovato\n");
                else{
                    printf("Elimino: ");
                    pg_stampa(&player,stdout);
                    printf("Nuova lista personaggi: \n");
                }
                personaggi_stampa(tab_pg, stdout);
                break;
            case 4:
                printf("Inserire codice del personaggio a cui si vuole equipaggiare un oggetto: ");
                scanf("%s",target1);

                printf("Inserire nome dell'oggetto da equipaggiare: ");
                scanf("%s",target2);

                personaggi_add_equip(target1,target2,tab_pg,tab_inv);
                break;
            case 5:
                printf("Inserire codice del personaggio a cui si vuole rimuovere un oggetto: ");
                scanf("%s",target1);

                printf("Inserire nome dell'oggetto da equipaggiare: ");
                scanf("%s",target2);

                personaggi_remove_equip(target1,target2,tab_pg,tab_inv);
                break;
            case 6:
                printf("Inserire codice del personaggio di cui si vuole sapere le statistiche: ");
                scanf("%s",target1);
                player=personaggi_ricerca_player(target1,tab_pg);
                pg_stampa(&player,stdout);
                break;
            case 7:
                break;
            default:
                printf("Comando non riconosciuto\n");
                break;
        }
        printf("\n");
    }
    while(cmd!=7);

    return 0;
}
