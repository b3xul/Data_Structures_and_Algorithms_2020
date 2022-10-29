#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AMAX 25 //ATLETA
#define CMAX 21 //CATEGORIE
#define EMAX 50 //ESERCIZI

typedef struct Data{
    int giorno;
    int mese;
    int anno;
}Data;

typedef struct tabellaCategorie{
    char **vettCat;
    int nCat;
    int sizeCat;
}tabCategorie;

typedef struct esercizio{
    char *nomeEs;
    char *catEs;
    char *tipoEs;
}esercizio;

typedef struct tabellaEsercizi{
    esercizio *vettEs;
    int nEs;
}tabEsercizi;

typedef struct esercizioPiano *link_e;

typedef struct esercizioPiano{
    esercizio *es;
    int set;
    int rip;
    link_e *next;
}eserPiano;

typedef struct info{
    char *v_codice;
    char *v_cognome;
    char *v_nome;
    char *v_categoria;
    Data data;
    int ore;
    eserPiano *head;
    eserPiano *tail;
}atleta;

typedef struct nodeA *link;

typedef struct nodeA{
    atleta val;
    link next;
}nodeAtleta;

typedef struct tabellaAtleti{
    int nAtleti;
    link head;
    link tail;
}tabAtleti;

typedef enum {
    r_stampaVideo,r_stampaFile,r_stampaAtletiCategoria,r_aggiornaOre,r_ricercaCodice,r_ricercaCognome,r_aggiungiAtleta,r_cancellaAtleta,r_caricaPiano,r_salvaPiano,r_fine,r_errore //da zero a 5
}comando_e;

link NewNode(atleta val, link next);
void InitAnagrafica(tabAtleti *anagrafica,tabCategorie *categorie);
tabEsercizi InitEsercizi(void);
void InsertTail(link *hp,link *tp,atleta val);
void menu(tabAtleti *anagrafica,tabCategorie *categorie);
comando_e leggiComando(void);
void stampaAtleti(int scelta, link h);
char *getCodice(link nodo);
char *getCognome(link nodo);
char *getNome(link nodo);
char *getCategoria(link nodo);
Data getData(link nodo);
int getOre(link nodo);
void stampaAtletiCategoria(link h,tabCategorie *categorie);
void stampaAtleta(link x);
void aggiornaOre(link h,char *codice);
link ricercaCodice(link h,char *codice);
link ricercaCognome(link h,char *cognome);
void aggiungiAtleta(link *hp,link *tp,int *n,tabCategorie *categorie);
void cancellaAtleta(link *hp,link *tp,int *n,tabCategorie *categorie,char *codice);
void liberaNodo(link x);
int caricaPiano(link pos);
void stampaPiano();

int main()
{


    tabAtleti anagrafica;
    tabCategorie categorie;
    tabEsercizi esercizi;

    InitAnagrafica(&anagrafica,&categorie);
    esercizi=InitEsercizi();

    menu(&anagrafica,&categorie);

    return 0;
}

void InitAnagrafica(tabAtleti *anagrafica,tabCategorie *categorie){

    int i,j,trovata;
    atleta x;
    link *hp=&anagrafica->head;
    link *tp=&anagrafica->tail;

    char codice[5+1];
    char nome[AMAX+1];
    char cognome[AMAX+1];
    char categoria[AMAX+1];

    FILE *fi;

    fi=fopen("atleti.txt","r"); //non faccio controllo perchè tanto sarebbe uscito prima
    fscanf(fi,"%d",&(anagrafica->nAtleti));   //butto la prima riga del file perchè non mi serve

    anagrafica->head=anagrafica->tail=NULL;

    categorie->vettCat=(char **)malloc(sizeof(char *));

    for(i=0,categorie->nCat=0,categorie->sizeCat=1;i<anagrafica->nAtleti;i++){

        fscanf(fi,"%s %s %s %s %d/%d/%d %d",codice,cognome,nome,categoria,&x.data.giorno,&x.data.mese,&x.data.anno,&x.ore);
                                        //p_anagrafica[i] puntatore che mi indica una struct intera: avendo nome della struct accedo ai campi tramite ->
        x.v_codice=strdup(codice);

        x.v_cognome=strdup(cognome);

        x.v_nome=strdup(nome);

        x.v_categoria=strdup(categoria);

        x.head=x.tail=NULL;

        InsertTail(hp,tp,x);

        trovata=0;
        for(j=0;j<(categorie->nCat);j++)
            if(strcmp(categoria,(categorie->vettCat[j]))==0){
                trovata=1;
                break;
            }

        if(trovata==0){
            if((categorie->nCat)==(categorie->sizeCat)){
                (categorie->sizeCat)=(categorie->sizeCat)*2;
                categorie->vettCat=(char **)realloc(categorie->vettCat,(categorie->sizeCat)*sizeof(char *));
            }
            categorie->vettCat[(categorie->nCat)++]=strdup(categoria);   //N.B da liberare
        }
    }

    return;
}

link NewNode(atleta val, link next){

    link x=(nodeAtleta *)malloc(sizeof(nodeAtleta));

    if(x==NULL)
        return NULL;

    x->val=val;
    x->next=next;

    return x;
}

void InsertTail(link *hp,link *tp,atleta val){

    if(*hp==NULL)
        (*hp)=(*tp)=NewNode(val,NULL);

    else{
        (*tp)->next=NewNode(val,NULL);  //dove aggiungo il nuovo nodo=dopo la tail
        *tp=(*tp)->next;    //nuova tail è il nodo appena aggiunto
    }
    return;
}

tabEsercizi InitEsercizi(void){

    tabEsercizi esercizi;
    int i;
    char buffer[EMAX+1];

    FILE *fi;
    fi=fopen("esercizi.txt","r");
    fscanf(fi,"%d",&(esercizi.nEs));

    for(i=0;i<esercizi.nEs;i++){
        fscanf(fi,"%s",buffer);
        esercizi.vettEs[i].nomeEs=strdup(buffer);
        fscanf(fi,"%s",buffer);
        esercizi.vettEs[i].catEs=strdup(buffer);
        fscanf(fi,"%s",buffer);
        esercizi.vettEs[i].tipoEs=strdup(buffer);
    }

    return esercizi;
}

void menu(tabAtleti *anagrafica,tabCategorie *categorie){
    comando_e comando;
    char codice[5+1];
    char cognome[AMAX+1];
    link h,*hp;
    link t,*tp;
    link pos;

    int continua=1;
    while(continua){
        printf("Operazioni eseguibili:\n");
        printf("stampaVideo: stampa a video dei contenuti dell'anagrafica\nstampaFile: stampa su file dei contenuti dell'anagrafica\nstampaAtletiCategoria: stampa a video degli atleti, divisi per categoria sportiva\n");
        printf("aggiornaOre: aggiornamento del monte ore settimanali\nricercaCodice: ricerca di un atleta per codice\nricercaCognome: ricerca di un atleta per cognome (anche parziale).\n");
        printf("aggiungiAtleta: aggiunta di un nuovo atleta all'anagrafica\ncancellaAtleta: rimuovi un atleta dall'anagrafica\n");
        printf("caricaPiano: caricare il piano di allenamenti di un atleta\nsalvaPiano: salvare su file il piano di allenamenti\nfine: terminare l'esecuzione del programma\n");

        h=anagrafica->head;
        hp=&h;
        t=anagrafica->tail;
        tp=&t;

        if(anagrafica->nAtleti==0)
            printf("L'anagrafica e' vuota.\n");

        comando=leggiComando();

        switch(comando){
            case r_stampaVideo:
                    stampaAtleti(0,h);
                break;
            case r_stampaFile:
                    stampaAtleti(1,h);
                break;
            case r_stampaAtletiCategoria:
                    stampaAtletiCategoria(h,categorie);
                break;
            case r_aggiornaOre:
                    printf("Inserisci il codice dell'atleta a cui modificare il monte ore:");
                    scanf("%s",codice);
                    aggiornaOre(h,codice);
                break;
            case r_ricercaCodice:
                    printf("Inserisci il codice dell'atleta da cercare:");
                    scanf("%s",codice);
                    ricercaCodice(h,codice);
                break;
            case r_ricercaCognome:
                    printf("Inserire cognome (anche parziale) da cercare: ");
                    scanf("%s",cognome);
                    ricercaCognome(h,cognome);
                break;
            case r_aggiungiAtleta:
                    aggiungiAtleta(hp,tp,&(anagrafica->nAtleti),categorie);
                break;
            case r_cancellaAtleta:
                    printf("Inserisci il codice dell'atleta che vuoi cancellare dalla lista:");
                    scanf("%s",codice);
                    cancellaAtleta(hp,tp,&(anagrafica->nAtleti),categorie,codice);
                    printf("Lista aggiornata:\n");
                    stampaAtleti(0,(*hp));
                break;
            case r_caricaPiano:
                    printf("Inserisci il codice dell'atleta di cui caricare il piano di allenamenti: ");
                    scanf("%s",codice);
                    if(pos=ricercaCodice(h,codice)!=NULL){
                        if(caricaPiano(pos))
                            stampaPiano;
                        else
                            printf("Piano non trovato.");
                    }

            case r_fine:
                continua=0;
                break;
            case r_errore:
            default:
                printf("Scelta non disponibile!\n");
        }
    }
    return;
}

comando_e leggiComando(void){
    comando_e c;
    char input[CMAX+1];
    char comandi[r_errore][CMAX+1]={"stampaVideo","stampaFile","stampaAtletiCategoria","aggiornaOre","ricercaCodice","ricercaCognome","aggiungiAtleta","cancellaAtleta","caricaPiano","salvaPiano","fine"};


    scanf("%s",input);
    c=r_stampaVideo;
    while(c<r_errore&&strcmp(input,comandi[c])!=0) c++;

    return c;
}

void stampaAtleti(int scelta, link h){
    FILE *fo;
    link x;

    switch(scelta){
        case 0:
            fo=stdout;
            for(x=h;x!=NULL;x=x->next)
                fprintf(fo,"%s %s %s %s %d/%d/%d %d\n",getCodice(x),getCognome(x),getNome(x),getCategoria(x),getData(x).giorno,getData(x).mese,getData(x).anno,getOre(x));
            break;
        case 1:
            fo=fopen("Anagrafica.txt","w");
            for(x=h;x!=NULL;x=x->next)
                fprintf(fo,"%s %s %s %s %d/%d/%d %d\n",getCodice(x),getCognome(x),getNome(x),getCategoria(x),getData(x).giorno,getData(x).mese,getData(x).anno,getOre(x));
            break;
    }

    printf("\n");
    return;
}

char *getCodice(link nodo){
    return nodo->val.v_codice;
}

char *getCognome(link nodo){
    return nodo->val.v_cognome;
}

char *getNome(link nodo){
    return nodo->val.v_nome;
}

char *getCategoria(link nodo){
    return nodo->val.v_categoria;
}

Data getData(link nodo){
    return nodo->val.data;
}

int getOre(link nodo){
    return nodo->val.ore;
}

void stampaAtletiCategoria(link h,tabCategorie *categorie){
    int i;
    link x;

    for(i=0;i<categorie->nCat;i++){
            printf("%s\n",categorie->vettCat[i]);
        for(x=h;x!=NULL;x=x->next){
            if(strcmp(getCategoria(x),categorie->vettCat[i])==0)
                stampaAtleta(x);
        }
    }
    printf("\n");
    return;
}

void stampaAtleta(link x){
    printf("%s %s %s %s %d/%d/%d %d\n",getCodice(x),getCognome(x),getNome(x),getCategoria(x),getData(x).giorno,getData(x).mese,getData(x).anno,getOre(x));
    return;
}

void aggiornaOre(link h,char *codice){
    link trovato;

    trovato=ricercaCodice(h,codice);

    if(trovato!=NULL){
        printf("Inserisci il nuovo monte ore: ");
        scanf("%d",&(trovato->val.ore));
        printf("Atleta aggiornato: ");
        stampaAtleta(trovato);
    }
    printf("\n");

    return;
}

link ricercaCodice(link h,char *codice){
    link x;
    link trovato=NULL;


    for(x=h;x!=NULL;x=x->next){
        if(strcmp(getCodice(x),codice)==0){
            printf("Atleta trovato: ");
            stampaAtleta(x);
            trovato=x;
            break;
        }
    }

    if(trovato==NULL)
        printf("Atleta non presente.\n");

    printf("\n");

    return trovato;
}

link ricercaCognome(link h,char *cognome){
    link x;
    link trovato=NULL;
    int length=strlen(cognome);

    for(x=h;x!=NULL;x=x->next){
        if(strncmp(getCognome(x),cognome,length)==0){
            printf("Atleta trovato: ");
            stampaAtleta(x);
            trovato=x;
        }
    }

    if(trovato==NULL)
        printf("Atleta non presente.\n");

    printf("\n");

    return trovato;
}

void aggiungiAtleta(link *hp,link *tp,int *n,tabCategorie *categorie){
    link h=(*hp);
    atleta val;
    int trovata;
    int j;

    char codice[5+1];
    char nome[AMAX+1];
    char cognome[AMAX+1];
    char categoria[AMAX+1];

    printf("Inserisci il codice dell'atleta da aggiungere: ");
    scanf("%s",codice);

    if(ricercaCodice(h,codice)!=NULL){
        printf("Il codice inserito e' gia' presente in lista.\n");
        return;
    }
    val.v_codice=strdup(codice);

    printf("Inserisci cognome e nome dell'atleta da aggiungere: ");
    scanf("%s%s",cognome,nome);
    val.v_cognome=strdup(cognome);
    val.v_nome=strdup(nome);

    printf("Inserisci la categoria dell'atleta da aggiungere: ");
    scanf("%s",categoria);
    val.v_categoria=strdup(categoria);

    trovata=0;
    for(j=0;j<(categorie->nCat);j++)
        if(strcmp(categoria,(categorie->vettCat[j]))==0){
            trovata=1;
            break;
        }
    if(trovata==0){
        if((categorie->nCat)==(categorie->sizeCat)){
            (categorie->sizeCat)=(categorie->sizeCat)*2;
            categorie->vettCat=(char **)realloc(categorie->vettCat,(categorie->sizeCat)*sizeof(char *));
        }
        categorie->vettCat[(categorie->nCat)++]=strdup(categoria);   //N.B da liberare
    }

    printf("Inserisci la data di nascita nel formato (gg/mm/aaaa) dell'atleta da aggiungere: ");
    scanf("%d/%d/%d",&val.data.giorno,&val.data.mese,&val.data.anno);

    printf("Inserisci le ore dell'atleta da aggiungere: ");
    scanf("%d",&val.ore);

    InsertTail(hp,tp,val);

    (*n)++;

    stampaAtleta(*tp);

    printf("\n");

    return;
}

void cancellaAtleta(link *hp,link *tp,int *n,tabCategorie *categorie,char *codice){

    link x,p;
    int scelta;

    if(ricercaCodice((*hp),codice)==NULL){
        printf("Non e' presente nessun atleta con il codice inserito.\n");
        return;
    }
    for(x=(*hp),p=NULL;x!=NULL;p=x,x=x->next){
        if(strcmp(getCodice(x),codice)==0){
            printf("Vuoi eliminarlo? (1 per confermare, 0 per annullare)\n");
            while(1){
                scanf("%d",&scelta);
                switch(scelta){
                    case 0:
                        return;
                    case 1:
                        if((*hp)==NULL)
                            return;
                        if(x==(*hp)){
                            (*hp)=x->next;
/*                            for(i=0;i<(*m);i++){
                                if(strcmp(getCategoria(x),categorie[i])==0){
                                    indicecat=i
                                    for(y=(*hp);y!=NULL;y=y->next){
                                        if(strcmp(getCategoria(y),categorie[i])==0)
                                            conta++
                                        if(conta>1)
                                            break;
                                    }
                                    if (conta==1){
                                        (*m)--;
                                        categorie(indicecat)=categorie(*m)
                                    }
                                }   come rimuovo la cateoforia?*/
                            liberaNodo(x);
                            return;
                        }
                        (*n)--;
                        p->next=x->next;
                        liberaNodo(x);
                        return;
                    default:
                        printf("Scelta non valida.\n");
                }
            }
        }
    }
    return;
}

void liberaNodo(link x){

    free(x->val.v_codice);
    free(x->val.v_cognome);
    free(x->val.v_nome);
    free(x->val.v_categoria);
    free(&(x->next));   //cancellare il puntatore al puntatore next, non il puntatore next (cancella proprio l'indirizzo del nodo successivo)
    free(x);

    return;
}

int caricaPiano(link pos){

    char es[EMAX+1];
    char nomefile[9+1]; //codice+".txt"
    strcpy(nomefile,getCodice(pos));
    strcat(nomefile,".txt");

    FILE *fi;
    if((fi=fopen(nomefile,"r"))==NULL)
        return 0;


    fscanf(fi,"%s %d %d",es,)

    return 1;
}
