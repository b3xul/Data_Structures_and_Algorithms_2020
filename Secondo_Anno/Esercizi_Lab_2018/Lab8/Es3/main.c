#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "inventario.h"
#include "personaggi.h"

#define N_OPERATIONS 8

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

    tabInv tab_inv;
    tab_inv.inventory=NULL;
    tab_inv.maxInv=tab_inv.nInv=0;

    tabPg tab_pg;
    tab_pg.head=tab_pg.tail=NULL;
    tab_pg.nPg=0;

    int i,cmd;
    char target[MAX_STR];
    FILE* fp;
    pg_t player;
    link pg_link;
    obj_t* obj_p;

    do{
        for(i=0; i<N_OPERATIONS; i++){
            printf("%d: %s\n", i, prompt[i]);
        }
        printf("Inserire comando> ");
        scanf("%d",&cmd);
        switch(cmd){
            case 0:
                printf("Inserire nome file: ");
                scanf("%s",target);
                fp=fopen(target,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                tab_pg.nPg+=leggi_file_pg(&tab_pg.head, &tab_pg.tail, fp);
                stampa_players(tab_pg.head, tab_pg.tail, stdout);
                break;
            case 1:
                printf("Inserire nome file: ");
                scanf("%s",target);
                fp=fopen(target,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                leggi_file_obj(&tab_inv, fp);
                stampa_inventory(tab_inv, stdout);
                break;
            case 2:
                printf("Inserire nuovo personaggio nel formato <codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>:\n");
                player=new_pg(stdin);
                list_insert_tail(&player,&tab_pg.head,&tab_pg.tail);
                stampa_players(tab_pg.head, tab_pg.tail, stdout);
                break;
            case 3:
                printf("Inserire codice del personaggio che si vuole eliminare: ");
                scanf("%s",target);
                player=estrai_codice(target,&tab_pg.head,&tab_pg.tail); //Inconsistente! main crea personaggio ma poi lo libera indirettamente! (Non fa free)
                if(pg_check_void(player))
                    printf("Codice non trovato\n");
                else{
                    printf("Elimino: ");
                    stampa_pg(&player,stdout);
                    printf("Nuova lista personaggi: \n");
                }
                stampa_players(tab_pg.head, tab_pg.tail, stdout);
                break;
            case 4:
                printf("Inserire codice del personaggio a cui si vuole equipaggiare un oggetto: ");
                scanf("%s",target);
                pg_link=ricerca_codice(target,tab_pg.head);
                if(pg_link==NULL){
                    printf("Codice non trovato\n");
                    break;
                }

                printf("Inserire nome dell'oggetto da equipaggiare: ");
                scanf("%s",target);
                obj_p=ricerca_nome(target,tab_inv);
                if(obj_p==NULL){
                    printf("Nome non trovato\n");
                    break;
                }

                equip(pg_link,obj_p);
                stampa_pg_node_t(pg_link,stdout);
                break;
            case 5:
                printf("Inserire codice del personaggio a cui si vuole rimuovere un oggetto: ");
                scanf("%s",target);
                pg_link=ricerca_codice(target,tab_pg.head);
                if(pg_link==NULL){
                    printf("Codice non trovato\n");
                    break;
                }

                printf("Inserire nome dell'oggetto da rimuovere: ");
                scanf("%s",target);
                obj_p=ricerca_nome(target,tab_inv);
                if(obj_p==NULL){
                    printf("Nome non trovato\n");
                    break;
                }

                unequip(pg_link,obj_p);
                stampa_pg_node_t(pg_link,stdout);
                break;
                break;
            case 6:
                printf("Inserire codice del personaggio di cui si vuole sapere le statistiche: ");
                scanf("%s",target);
                pg_link=ricerca_codice(target,tab_pg.head);
                stampa_pg_node_t(pg_link,stdout);
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
