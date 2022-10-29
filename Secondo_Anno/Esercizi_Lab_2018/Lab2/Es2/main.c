#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_TRATTE 1000
#define MAX_RIGA 31
//<codice_tratta><partenza><destinazione><data><ora_partenza><ora_arrivo><ritardo>

/*typedef enum sceltaMenu_e {
  uscita_c, stampa_video_c, stampa_file_c, ordina_data_c, ordina_cod_c,
  ordina_cogn_c, ordina_cat_c, aggiorna_ore_c, cerca_cod_c, cerca_cogn_c, numScelte_c
} sceltaMenu;

// si propone una tabella di conversione tra menu e stringhe, basata su
// vettore di struct, anziche' vettore con accesso diretto
struct {sceltaMenu codice; char *prompt; char *comando;} scelte[] = {
  {uscita_c, "Uscita", "Fine"},
  {stampa_video_c, "Stampa atleti a video", "Video"},
  {stampa_file_c, "Stampa atleti su file", "File"},
  {ordina_data_c, "Ordina per data di nascita", "Od"},
  {ordina_cod_c, "Ordina per codice atleta", "Ocod"},
  {ordina_cogn_c, "Ordina per cognome", "Ocogn"},
  {ordina_cat_c, "Ordina per categoria", "Ocat"},
  {aggiorna_ore_c, "Aggiorna monte ore", "Ore"},
  {cerca_cod_c, "Ricerca per codice", "Codice"},
  {cerca_cogn_c, "Ricerca per cognome", "Cognome"},
  {numScelte_c, NULL, NULL}
};*/

typedef enum comando_e{
    date_c, partenza_c, capolinea_c, ritardo_c, ritardo_tot_c, fine_c, errore_c
} sceltaMenu;

struct{ sceltaMenu codice;
        char* prompt;
        char* comando; } scelte[]= {
                                    {date_c,"Elencare tutte le corse partite in un certo intervallo di date",  "date"},
                                    {partenza_c,"Elencare tutti le corse partite da una certa fermata",  "partenza"},
                                    {capolinea_c,"Elencare tutti le corse che fanno capolinea in una certa fermata",   "capolinea"},
                                    {ritardo_c,"Elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date","ritardo"},
                                    {ritardo_tot_c,"Elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta","ritardo_tot"},
                                    {fine_c,"Terminare il programma","fine"},
                                    {errore_c,NULL,NULL}
                                    };

typedef struct data{
    unsigned int giorno;
    unsigned int mese;
    unsigned int anno;
}Data;

typedef struct tratta{
    char* codice;
    char* partenza;
    char* destinazione;
    char* data_str;
    Data data;
    char* h_partenza;
    char* h_arrivo;
    unsigned int ritardo;
}Tratta;

typedef struct tabella{
    unsigned int n;
    Tratta log[MAX_TRATTE];
}Tabella;

void leggiFile(Tabella* t_p);
void stampaTratta(Tratta t);
sceltaMenu leggiComando(void);
void selezionaDati(Tabella t,sceltaMenu cmd);
int confrontaDate(Data d1,Data d2);

#define DBG 1
int main(){
    Tabella t;
    Tabella* t_p;
    t_p=&t;

    sceltaMenu cmd;
    int i;

    leggiFile(t_p);

#if DBG
    for(i=0;i<t.n;i++){
        stampaTratta(t.log[i]);
    }
#endif // DBG

    do{
        for(i=0; i<errore_c; i++){
            printf("%d. %s: %s\n", i+1, scelte[i].prompt, scelte[i].comando);
        }
        cmd=leggiComando();
        switch(cmd){
            case date_c:
            case partenza_c:
            case capolinea_c:
            case ritardo_c:
            case ritardo_tot_c:
                selezionaDati(t,cmd);
                break;
            case fine_c:
                break;
            case errore_c:
            default:
                printf("Comando non riconosciuto\n");
                break;
        }
        printf("\n");
    }
    while(cmd!=fine_c);
    //cancellaTratta(t);

    return 0;
}

void leggiFile(Tabella* t_p){
    FILE *fp;
    if((fp=fopen("log.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file\n");
        exit(-1);
    }
    int i;
    char buf[MAX_RIGA];

    fscanf(fp,"%d",&t_p->n);

    for(i=0;i<t_p->n;i++){
        fscanf(fp,"%s",buf);
        t_p->log[i].codice=strdup(buf);
        fscanf(fp,"%s",buf);
        t_p->log[i].partenza=strdup(buf);
        fscanf(fp,"%s",buf);
        t_p->log[i].destinazione=strdup(buf);
        fscanf(fp,"%s",buf);
        t_p->log[i].data_str=strdup(buf);
        sscanf(buf,"%d/%d/%d",&t_p->log[i].data.giorno,&t_p->log[i].data.mese,&t_p->log[i].data.anno);
        fscanf(fp,"%s",buf);
        t_p->log[i].h_partenza=strdup(buf);
        fscanf(fp,"%s",buf);
        t_p->log[i].h_arrivo=strdup(buf);
        fscanf(fp,"%d",&t_p->log[i].ritardo);
    }
}

void stampaTratta(Tratta t){
    printf("Tratta [%s] da %s a %s del %s (dalle %s alle %s, con ritardo di %d minut%c)\n", t.codice, t.partenza, t.destinazione, t.data_str, t.h_partenza, t.h_arrivo, t.ritardo, ((t.ritardo == 1) ? 'o' : 'i'));
}

sceltaMenu leggiComando(void){
    int i;
    char cmd[12];       //lunghezza di "ritardo_tot\0"
    sceltaMenu selezione;


    printf("Comando > ");
    scanf("%s",cmd);
    for(i=0; i<errore_c; i++){
        if (strcmp(cmd,scelte[i].comando)==0){
            selezione=scelte[i].codice;
            return selezione;
        }
    }

    return scelte[i].codice;    //errore_c
}

void selezionaDati(Tabella t,sceltaMenu cmd){
    Data d1,d2;
    char target[MAX_RIGA];
    int i,tot;

    switch(cmd){
        case date_c:
            printf("Inserire prima data [gg/mm/aaaa]: ");
            scanf("%d/%d/%d", &d1.giorno,&d1.mese,&d1.anno);
            printf("Inserire seconda data [gg/mm/aaaa]: ");
            scanf("%d/%d/%d", &d2.giorno,&d2.mese,&d2.anno);

            for(i=0;i<t.n;i++){
                if(confrontaDate(t.log[i].data,d1)>=0 && confrontaDate(t.log[i].data,d2)<=0)
                    stampaTratta(t.log[i]);
            }
            break;
        case partenza_c:
            printf("Inserire luogo di partenza: ");
            scanf("%s", target);
            for(i=0;i<t.n;i++){
                if(strcmp(t.log[i].partenza,target)==0)
                    stampaTratta(t.log[i]);
            }
            break;
        case capolinea_c:
            printf("Inserire luogo di destinazione: ");
            scanf("%s", target);
            for(i=0;i<t.n;i++){
                if(strcmp(t.log[i].destinazione,target)==0)
                    stampaTratta(t.log[i]);
            }
            break;
        case ritardo_c:
            printf("Inserire prima data [gg/mm/aaaa]: ");
            scanf("%d/%d/%d", &d1.giorno,&d1.mese,&d1.anno);
            printf("Inserire seconda data [gg/mm/aaaa]: ");
            scanf("%d/%d/%d", &d2.giorno,&d2.mese,&d2.anno);

            for(i=0;i<t.n;i++){
                if(confrontaDate(t.log[i].data,d1)>=0 && confrontaDate(t.log[i].data,d2)<=0 && t.log[i].ritardo>0)
                    stampaTratta(t.log[i]);
            }
            break;
        case ritardo_tot_c:
            printf("Inserire codice della tratta: ");
            scanf("%s", target);
            tot=0;
            for(i=0;i<t.n;i++){
                if(strcmp(t.log[i].codice,target)==0)
                    tot+=t.log[i].ritardo;
            }
            printf("Ritardo totale %d\n", tot);
            break;
        default:
            printf("Errore imprevisto\n");
            break;
    }
}

int confrontaDate(Data d1,Data d2){
    if (d1.anno != d2.anno)
        return (d1.anno-d2.anno);
    else if (d1.mese != d2.mese)
        return (d1.mese-d2.mese);
    else if (d1.giorno != d2.giorno)
        return (d1.giorno-d2.giorno);
    else return 0;
}
