#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_TRATTE 1000
#define MAX_RIGA 31
//<codice_tratta><partenza><destinazione><data><ora_partenza><ora_arrivo><ritardo>

typedef enum comando_e{
    date_c, partenza_c, capolinea_c, ritardo_c, ritardo_tot_c, stampa_log_video_c, stampa_log_file_c, ordina_data_c, ordina_codice_c, ordina_partenza_c, ordina_destinazione_c, ricerca_partenza_c, fine_c, errore_c
} sceltaMenu;

struct{ sceltaMenu codice; char* prompt; char* comando; } scelte[]= {
        {date_c,"Elencare tutte le corse partite in un certo intervallo di date",  "date"},
        {partenza_c,"Elencare tutti le corse partite da una certa fermata",  "partenza"},
        {capolinea_c,"Elencare tutti le corse che fanno capolinea in una certa fermata",   "capolinea"},
        {ritardo_c,"Elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date","ritardo"},
        {ritardo_tot_c,"Elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta","ritardo_tot"},
        {stampa_log_video_c,"Stampa video dei contenuti del log", "stampa_video"},
        {stampa_log_file_c,"Stampa su file dei contenuti del log", "stampa_file"},
        {ordina_data_c,"Ordinamento del vettore per data, e a parità di date per ora", "ordina_data"},
        {ordina_codice_c,"Ordinamento del vettore per codice di tratta", "ordina_codice"},
        {ordina_partenza_c,"Ordinamento del vettore per stazione di partenza", "ordina_partenza"},
        {ordina_destinazione_c,"Ordinamento del vettore per stazione di destinazione", "ordina_destinazione"},
        {ricerca_partenza_c,"Ricerca di una tratta per stazione di partenza (anche parziale)","ricerca_partenza"},
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
    Tratta log[MAX_TRATTE];
    Tratta *log_codice[MAX_TRATTE],*log_partenza[MAX_TRATTE],*log_destinazione[MAX_TRATTE],*log_data[MAX_TRATTE];
    unsigned int n;
}Tabella;

typedef enum ordinamento{
    o_nessuno,o_data,o_codice,o_partenza,o_destinazione
}Ordinamento_e;

void leggiFile(Tabella* t_p);
void stampaLog(Tabella* tab, char* nomefile);
void stampaLog_Puntato(Tratta* vista[MAX_TRATTE], int n, char* nomefile);
void stampaTratta(Tratta* t, FILE* fp);
sceltaMenu leggiComando(void);
void selezionaDati(Tabella t, Ordinamento_e ord, sceltaMenu cmd);
int confrontaDate(Data d1,Data d2);
void ordina_struct(Tabella* tab, Ordinamento_e o);
void ordina_P(Tratta** t, int n, Ordinamento_e o);
int ricerca(Tabella tab, Ordinamento_e ord, Ordinamento_e campo, char* str);
int ricerca_lineare(Tabella tab, Ordinamento_e campo, char* str);
int ricerca_binomiale(Tabella tab, Ordinamento_e campo, char* str);
int confrontaTratte_Stringa(Tratta* a, char* str, Ordinamento_e o);
void stampa_confinanti(Tabella tab,int i,Ordinamento_e campo,FILE *fp);

#define DBG 0

int main(){
    Tabella t;          /*Struct con vettore di Tratta e numero di elementi*/
    Tabella* t_p=&t;       /*Puntatore alla struct di sopra*/

    sceltaMenu cmd;
    int i;
    Ordinamento_e ord;

    leggiFile(t_p);

#if DBG

    stampaLog(&t,NULL);
    printf("\n");
    stampaLog_Puntato(t.log_codice,t.n,NULL);
    printf("\n");
    stampaLog_Puntato(t.log_partenza,t.n,NULL);
    printf("\n");
    stampaLog_Puntato(t.log_data,t.n,NULL);
    printf("\n");
    stampaLog_Puntato(t.log_destinazione,t.n,NULL);
    printf("\n");
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
            case stampa_log_video_c:
            case stampa_log_file_c:
            case ricerca_partenza_c:
                selezionaDati(t,ord,cmd);
                break;
            case ordina_data_c:
                ord=o_data;
                ordina_struct(&t,ord);
                break;
            case ordina_codice_c:
                ord=o_codice;
                ordina_struct(&t,ord);
                break;
            case ordina_partenza_c:
                ord=o_partenza;
                ordina_struct(&t,ord);
                break;
            case ordina_destinazione_c:
                ord=o_destinazione;
                ordina_struct(&t,ord);
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
    //Ordinamento_e ord;

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

        /*Inizializzo anche vettori di puntatori*/
        t_p->log_codice[i]=&(t_p->log[i]);
        t_p->log_partenza[i]=&(t_p->log[i]);
        t_p->log_destinazione[i]=&(t_p->log[i]);
        t_p->log_data[i]=&(t_p->log[i]);
    }
    /*Ordino i vettori di puntatori*/
    ordina_P(t_p->log_data,t_p->n,o_data);
    ordina_P(t_p->log_codice,t_p->n,o_codice);
    ordina_P(t_p->log_partenza,t_p->n,o_partenza);
    ordina_P(t_p->log_destinazione,t_p->n,o_destinazione);
}

void stampaLog(Tabella* tab, char* nomefile){
    int i;
    FILE* fp;

    if(nomefile==NULL)
        fp=stdout;
    else{
        fp=fopen(nomefile,"w");
        if(fp==NULL){
            fprintf(stderr,"Errore apertura file");
            exit(-1);
        }
    }

    for(i=0;i<tab->n;i++){
        stampaTratta(&(tab->log[i]),fp);
    }
}

void stampaLog_Puntato(Tratta* vista[MAX_TRATTE], int n, char* nomefile){
    int i;
    FILE* fp;

    if(nomefile==NULL)
        fp=stdout;
    else{
        fp=fopen(nomefile,"w");
        if(fp==NULL){
            fprintf(stderr,"Errore apertura file");
            exit(-1);
        }
    }

    for(i=0;i<n;i++){
        stampaTratta(vista[i],fp);
    }
}

void stampaTratta(Tratta* t, FILE* fp){
    fprintf(fp,"Tratta [%s] da %s a %s del %s (dalle %s alle %s, con ritardo di %d minut%c)\n", t->codice, t->partenza, t->destinazione, t->data_str, t->h_partenza, t->h_arrivo, t->ritardo, ((t->ritardo == 1) ? 'o' : 'i'));
}

sceltaMenu leggiComando(void){
    int i;
    char cmd[20];       //lunghezza di "ordina_destinazione\0"
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

void selezionaDati(Tabella t, Ordinamento_e ord, sceltaMenu cmd){
    Ordinamento_e campo;
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
                    stampaTratta(&(t.log[i]),NULL);
            }
            break;
        case partenza_c:
            printf("Inserire luogo di partenza: ");
            scanf("%s", target);
            for(i=0;i<t.n;i++){
                if(strcmp(t.log[i].partenza,target)==0)
                    stampaTratta(&(t.log[i]),NULL);
            }
            break;
        case capolinea_c:
            printf("Inserire luogo di destinazione: ");
            scanf("%s", target);
            for(i=0;i<t.n;i++){
                if(strcmp(t.log[i].destinazione,target)==0)
                    stampaTratta(&(t.log[i]),NULL);
            }
            break;
        case ritardo_c:
            printf("Inserire prima data [gg/mm/aaaa]: ");
            scanf("%d/%d/%d", &d1.giorno,&d1.mese,&d1.anno);
            printf("Inserire seconda data [gg/mm/aaaa]: ");
            scanf("%d/%d/%d", &d2.giorno,&d2.mese,&d2.anno);

            for(i=0;i<t.n;i++){
                if(confrontaDate(t.log[i].data,d1)>=0 && confrontaDate(t.log[i].data,d2)<=0 && t.log[i].ritardo>0)
                    stampaTratta(&(t.log[i]),NULL);
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
        case stampa_log_video_c:
            stampaLog(&t,NULL);
            break;
        case stampa_log_file_c:
            printf("Inserire nome file: ");
            scanf("%s", target);
            stampaLog(&t,target);
            break;
        case ricerca_partenza_c:
            printf("Inserire luogo di partenza: ");
            scanf("%s", target);
            campo=o_partenza;
            if(ricerca(t,ord,campo,target)==0)
                printf("Tratta non trovata\n");
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

int confrontaTratte(Tratta a, Tratta b, Ordinamento_e o){
    int diff;
    switch(o){
        case o_data:
            diff=confrontaDate(a.data,b.data);
            return (diff==0)?strcmp(a.h_partenza,b.h_partenza):diff;
        case o_codice:
            return strcmp(a.codice,b.codice);
        case o_partenza:
            return strcmp(a.partenza,b.partenza);
        case o_destinazione:
            return strcmp(a.destinazione,b.destinazione);
        default:
            break;
    }
    return -1;
}

int confrontaTratte_Stringa(Tratta* a, char* str, Ordinamento_e o){
    int length=strlen(str);
    //int diff;

    switch(o){
        case o_data:
            return -2;
            /*diff=confrontaDate(a.data,b.data);
            return (diff==0)?strcmp(a.h_partenza,a.h_arrivo):diff;*/
        case o_codice:
            return strncmp(a->codice,str,length);
        case o_partenza:
            return strncmp(a->partenza,str,length);
        case o_destinazione:
            return strncmp(a->destinazione,str,length);
        default:
            break;
    }
    return -1;
}

void ordina_struct(Tabella* tab, Ordinamento_e o){   //Ordina struct
    int i,j;
    Tratta tmp;

    for(i=1;i<tab->n;i++){
        tmp=tab->log[i];
        j=i-1;
        while(j>=0 && confrontaTratte(tmp,tab->log[j],o)<0 ){  //tmp che sto guardando ora è minore di chi c'era prima
            tab->log[j+1]=tab->log[j];
            j--;
        }
        tab->log[j+1]=tmp;
    }
}

void ordina_P(Tratta** t, int n, Ordinamento_e o){
    int i,j;
    Tratta* tmp;

    for(i=1;i<n;i++){
        tmp=t[i];
        j=i-1;
        while(j>=0 && confrontaTratte(*(tmp),*(t[j]),o)<0 ){  //tratta puntata da tmp che sto guardando ora è minore di chi c'era prima
            t[j+1]=t[j];    //Confronto le tratte ma scambio i puntatori!
            j--;
        }
        t[j+1]=tmp;
    }

}

int ricerca(Tabella tab, Ordinamento_e ord, Ordinamento_e campo, char* str){
    int res;
    if(campo==ord){
        res=ricerca_binomiale(tab,campo,str);
    }
    else{
        res=ricerca_lineare(tab,campo,str);
    }
    return res;
}

int ricerca_lineare(Tabella tab, Ordinamento_e campo, char* str){
    int i,trovato=0;

    for(i=0;i<tab.n;i++){
        if(confrontaTratte_Stringa(&(tab.log[i]),str,campo)==0){
            stampaTratta(&(tab.log[i]),stdout);
            trovato=1;
        }
    }
    return trovato;
}

int ricerca_binomiale(Tabella tab, Ordinamento_e campo, char* str){
    int l=0, r=tab.n-1, m=(l+r)/2,cmp;

    while(l<=r){
        m=(l+r)/2;
        cmp=confrontaTratte_Stringa(&(tab.log[m]),str,campo);      //Se str è prima-> cmp>0
        if(cmp==0){
            stampa_confinanti(tab,m,campo,stdout);
            return 1;
        }
        else if(cmp>0)  //str è nella prima metà
            r=m-1;
        else //cmp<0
            l=m+1;
    }
    return 0;
}


void stampa_confinanti(Tabella tab,int i,Ordinamento_e campo,FILE *fp){
    int j;
    stampaTratta(&(tab.log[i]),fp);

    j=i-1;
    while(j>=0 && confrontaTratte(tab.log[j],tab.log[i],campo)==0){
        stampaTratta(&(tab.log[j]),fp);
        j--;
    }
    j=i+1;
    while(j<tab.n && confrontaTratte(tab.log[j],tab.log[i],campo)==0){
        stampaTratta(&(tab.log[j]),fp);
        j++;
    }
}
