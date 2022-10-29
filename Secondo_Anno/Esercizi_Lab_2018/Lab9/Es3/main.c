#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "inventario.h"
#include "personaggi.h"

#define N_OPERATIONS 8

//PG0016 Braccobaldo Guerriero 10 20 30 40 50 60
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
    tab_inv=tab_inv_init();

    pgList_t* tab_pg;
    tab_pg=tab_pg_init();

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
                leggi_file_pg(tab_pg, fp);
                stampa_players(tab_pg, stdout);
                break;
            case 1:
                printf("Inserire nome file: ");
                scanf("%s",target1);
                fp=fopen(target1,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                leggi_file_obj(tab_inv, fp);
                stampa_inventory(tab_inv, stdout);
                break;
            case 2:
                printf("Inserire nuovo personaggio nel formato <codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>:\n");
                player=new_pg(stdin);
                add_player(&player,tab_pg);
                stampa_players(tab_pg, stdout);
                break;
            case 3:
                printf("Inserire codice del personaggio che si vuole eliminare: ");
                scanf("%s",target1);
                player=estrai_player(target1,tab_pg);
                if(pg_check_void(player))
                    printf("Codice non trovato\n");
                else{
                    printf("Elimino: ");
                    stampa_pg(&player,stdout);
                    printf("Nuova lista personaggi: \n");
                }
                stampa_players(tab_pg, stdout);
                break;
            case 4:
                printf("Inserire codice del personaggio a cui si vuole equipaggiare un oggetto: ");
                scanf("%s",target1);

                printf("Inserire nome dell'oggetto da equipaggiare: ");
                scanf("%s",target2);

                add_equip(target1,target2,tab_pg,tab_inv);
                break;
            case 5:
                printf("Inserire codice del personaggio a cui si vuole rimuovere un oggetto: ");
                                scanf("%s",target1);

                printf("Inserire nome dell'oggetto da equipaggiare: ");
                scanf("%s",target2);

                remove_equip(target1,target2,tab_pg,tab_inv);
                break;
            case 6:
                printf("Inserire codice del personaggio di cui si vuole sapere le statistiche: ");
                scanf("%s",target1);
                player=ricerca_player(target1,tab_pg);
                stampa_pg(&player,stdout);
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
