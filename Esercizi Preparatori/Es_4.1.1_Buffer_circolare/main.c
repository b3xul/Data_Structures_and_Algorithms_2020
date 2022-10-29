#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"
#include "queue.h"

typedef enum comando_e{
    crea_c, size_c, inserisci_c, estrai_c, stampa_video_c, stampa_file_c, leggi_file_c, distruggi_c, fine_c, errore_c
} sceltaMenu;

struct{ sceltaMenu codice;
        char* prompt;
        char* comando;      }scelte[]=  {
                                        {crea_c,"Inizializza nuovo buffer",  "inizializza"},
                                        {size_c,"Vedi cardinalita'",  "cardinalita'"},
                                        {inserisci_c,"Inserzione",   "inserisci"},
                                        {estrai_c,"Estrazione","estrai"},
                                        {stampa_video_c,"Visualizza tutto","stampa_video"},
                                        {stampa_file_c,"Salva su file","stampa_file"},
                                        {leggi_file_c,"Leggi da file","leggi_file"},
                                        {distruggi_c,"Distruggi buffer","distruggi"},
                                        {fine_c,"Terminare il programma","fine"},
                                        {errore_c,NULL,NULL}
                                        };

sceltaMenu leggi_comando(char* scelta);

int main()
{
    int i,cmd,termina=0,size;
    char scelta[15];
    QUEUE q=NULL;

    do {
        printf("Quale operazione vuoi eseguire?\n");
        i=0;
        while(i<errore_c){
            printf("%s -> %s\n",scelte[i].prompt, scelte[i].comando);
            i++;
        }
        scanf("%s", scelta);
        cmd=leggi_comando(scelta);

        switch(cmd){
            case crea_c: {
                printf("Inserire dimensione della coda voluta:");
                scanf("%d", &size);
                q = QUEUEinit(size);
            }
            break;
            case size_c: {
                printf("%d\n", QUEUEsize(q));
            }
            break;
            case inserisci_c: {
                Item d;
                d=ITEMscan(stdin);
                if (q == NULL){
                    printf("Non esiste alcuna coda, inserire dimensione della coda voluta:");
                    scanf("%d", &size);
                    q = QUEUEinit(size);
                }
                QUEUEput(q, d);
            }
            break;
            case estrai_c: {
                Item d;
                d=QUEUEget(q);
                /* fai qualcosa col dato... */
            }
            break;
            /*case stampa_video_c: {
                QUEUEshow(stdout, q);
            }
            break;
            case stampa_file_c: {
                char filename[100];
                FILE *out;
                printf("Inserisci nome del file\n");
                scanf("%s", filename);
                out = fopen(filename, "w");
                QUEUEshow(out, q);
                fclose(out);
            }
            break;
            case leggi_file_c: {
                char filename[100];
                FILE *in;
                printf("Inserisci nome del file\n");
                scanf("%s", filename);
                in = fopen(filename, "r");
                if (q != NULL)
                    QUEUEfree(q);

                q = QUEUEread(in);
                fclose(in);
            }
            break;
            case distruggi_c: {
                QUEUEfree(q);
                q = NULL;
            }
            break;*/
            case fine_c: {
                termina = 1;
                QUEUEfree(q);
                q = NULL;
            }
            break;
            default:
                printf("Scelta non valida!\n");
        }
    }
    while(!termina);

    return 0;
}

sceltaMenu leggi_comando(char* scelta){
    int i=0;
    while(i<errore_c){
        if(strcmp(scelta,scelte[i].comando)==0)
            return scelte[i].codice;
        i++;
    }
    return scelte[i].codice;
}
