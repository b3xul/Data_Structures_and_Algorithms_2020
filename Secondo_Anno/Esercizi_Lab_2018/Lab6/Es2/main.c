#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_STR 51

typedef struct data_s{
    int giorno;
    int mese;
    int anno;
}data_t;

typedef struct item{
    char* codice;
    char* nome;
    char* cognome;
    char* via;
    char* citta;
    char* data_nascita_str;
    data_t data_nascita;
    int cap;
}Item;

typedef struct nodo_s* link;
typedef struct nodo_s{
    Item val;
    link next;
}nodo_t;

Item newItem(FILE* fp);
link newNode(Item val, link next);
/*Sentinelle
void list_sorted_insert(Item val, link h, link z);
void leggiFile(link h, link z, FILE* fp);
void stampa_anagrafica(link h, link z, FILE* fp);*/

link list_sorted_insert(Item val, link h);
link leggiFile(link h, FILE* fp);
void stampa_anagrafica(link h, FILE* fp);
int compare_date(data_t d1,data_t d2);
void stampa_nodo(link x, FILE* fp);
void stampa_item(Item x, FILE* fp);
Item item_set_void(void);
int item_check_void(Item d);
link ricerca_codice(link h, char* str);
Item estrai_codice(link* hp, char* str);
Item estrai_date(link* hp, data_t d1, data_t d2);

//A0002 Lucia Verdi 07/11/1989 ViaTorino Milano 20123
int main(){
    /*Sentinelle, non veri nodi
    link h=(link)malloc(sizeof(nodo_t));
    link z=(link)malloc(sizeof(nodo_t));
    h->next=z;    //Lista vuota
    z->next=z;*/

    link h=NULL;    //Lista tradizionale

    char* prompt[]={"Acquisizione ed inserimento ordinato di un nuovo elemento in lista (da tastiera)",
                    "acquisizione ed inserimento ordinato di nuovi elementi in lista (da file)",
                    "ricerca, per codice, di un elemento",
                    "cancellazione (con estrazione del dato) di un elemento dalla lista, previa ricerca per codice",
                    "cancellazione (con estrazione del dato) di tutti gli elementi con date comprese tra 2 date lette da tastiera",
                    "stampa della lista su file",
                    "termina il programma"};
    int i,cmd;
    Item val;
    link x;
    char target[MAX_STR];
    data_t d1,d2;
    FILE* fp;

    do{
        for(i=0; i<7; i++){
            printf("%d: %s\n", i, prompt[i]);
        }
        printf("Inserire comando> ");
        scanf("%d",&cmd);
        switch(cmd){
            case 0:
                printf("Inserire elemento nel formato <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>:\n");
                val=newItem(stdin);
                h=list_sorted_insert(val,h);
                stampa_anagrafica(h,stdout);
                break;
            case 1:
                printf("Inserire nome file: ");
                scanf("%s",target);
                fp=fopen(target,"r");
                if(fp==NULL){
                    fprintf(stderr,"Impossibile aprire file\n");
                    break;
                }
                h=leggiFile(h,fp);
                stampa_anagrafica(h,stdout);
                break;
            case 2:
                printf("Inserire codice da ricercare: ");
                scanf("%s",target);
                x=ricerca_codice(h,target);
                if(x!=NULL)
                    stampa_nodo(x,stdout);
                else
                    printf("Codice non trovato\n");
                break;
            case 3:
                printf("Inserire codice dell'elemento da estrarre: ");
                scanf("%s",target);
                val=estrai_codice(&h,target);   //Devo per forza passare h by reference perchè la funzione deve ritornarmi l'Item
                if(item_check_void(val))
                    printf("Codice non trovato\n");
                else{
                    printf("Estraggo: ");
                    stampa_item(val,stdout);
                    printf("Nuova anagrafica: \n");
                }
                stampa_anagrafica(h,stdout);
                break;
            case 4:
                printf("Inserire la data di inizio degli elementi da estrarre (gg/mm/aaaa): ");
                scanf("%s",target);
                sscanf(target,"%d/%d/%d",&d1.giorno,&d1.mese,&d1.anno);

                printf("Inserire la data di fine degli elementi da estrarre (gg/mm/aaaa): ");
                scanf("%s",target);
                sscanf(target,"%d/%d/%d",&d2.giorno,&d2.mese,&d2.anno);

                //Finchè estrai date non ritorna un item nullo, stampa gli item che trova
                while(item_check_void(val=estrai_date(&h,d1,d2))!=1)    //Funziona continuare a chiamare la stessa funzione perchè man mano elimino date
                    stampa_item(val,stdout);
                printf("Fine delle date comprese\n");
                printf("Nuova anagrafica: \n");
                stampa_anagrafica(h,stdout);
                break;
            case 5:
                printf("Inserire nome file: ");
                scanf("%s",target);
                fp=fopen(target,"w");
                if(fp==NULL)
                    fprintf(stderr,"Impossibile aprire file\n");
                stampa_anagrafica(h,fp);
            case 6:
                break;
            default:
                printf("Comando non riconosciuto\n");
                break;
        }
        printf("\n");
    }
    while(cmd!=6);

    return 0;
}

Item newItem(FILE* fp){
    char buffer[MAX_STR];
    Item d;

    if(fscanf(fp,"%s",buffer)==EOF)
        return item_set_void();

    d.codice=strdup(buffer);

    fscanf(fp,"%s",buffer);
    d.nome=strdup(buffer);

    fscanf(fp,"%s",buffer);
    d.cognome=strdup(buffer);

    fscanf(fp,"%s",buffer);
    d.data_nascita_str=strdup(buffer);

    sscanf(d.data_nascita_str,"%d/%d/%d",&d.data_nascita.giorno,&d.data_nascita.mese,&d.data_nascita.anno);

    fscanf(fp,"%s",buffer);
    d.via=strdup(buffer);

    fscanf(fp,"%s",buffer);
    d.citta=strdup(buffer);

    fscanf(fp,"%d",&d.cap);

    return d;
}

link list_sorted_insert(Item val, link h){
    link x, p;
    data_t data = val.data_nascita;

    if (h==NULL || compare_date(data, h->val.data_nascita) < 0)
        return newNode(val, h);     //Head= nuovo nodo che punta al vecchio valore di h: NULL se lista vuota o h_old se c'erano già nodi

    /*Serve puntatore al predecessore per fare bypass!*/
    for (x=h->next, p=h;
         x!=NULL && compare_date(data, x->val.data_nascita) >= 0;
         p=x, x=x->next);

    p->next = newNode(val, x);

    return h;
}

link newNode(Item val, link next){
    link x=(link)malloc(sizeof(nodo_t));
    if(x==NULL){
        fprintf(stderr,"Allocazione nodo fallita");
        return NULL;
    }
    x->val=val;
    x->next=next;
    return x;
}

int compare_date(data_t d1, data_t d2){
    if (d1.anno != d2.anno)
        return (d1.anno-d2.anno);
    else if (d1.mese != d2.mese)
        return (d1.mese-d2.mese);
    else if (d1.giorno != d2.giorno)
        return (d1.giorno-d2.giorno);
    else return 0;
}

void stampa_anagrafica(link h, FILE* fp){
    link x;
    for(x=h; x!=NULL; x=x->next)
        stampa_nodo(x,fp);
}

void stampa_nodo(link x, FILE* fp){
    fprintf(fp,"%s %s %s %s %s %s %d\n",x->val.codice, x->val.nome, x->val.cognome, x->val.data_nascita_str, x->val.via, x->val.citta, x->val.cap);
}

void stampa_item(Item x, FILE* fp){
    fprintf(fp,"%s %s %s %s %s %s %d\n",x.codice, x.nome, x.cognome, x.data_nascita_str, x.via, x.citta, x.cap);
}

link leggiFile(link h, FILE* fp){
    Item d;
    int prosegui=1;

    while(prosegui){
        d=newItem(fp);
        if(item_check_void(d))
            prosegui=0;
        else
            h=list_sorted_insert(d,h);
    }
    return h;
}

Item item_set_void(void){
    Item d;
    d.cap=-1;
    return d;
}

int item_check_void(Item d){
    return (d.cap==-1);     //Ritorna 1 se d vuota
}

link ricerca_codice(link h, char* str){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(!strcmp(str,x->val.codice))
            return x;
    }
    return NULL;
}

Item estrai_codice(link* hp, char* str){
    link* xp;
    link tmp;
    Item d;

    for(xp=hp; *xp!=NULL; xp=&((*xp)->next)){
        if(!strcmp(str,(*xp)->val.codice)){
            tmp=*xp;    //tmp:link corrispondente al nodo trovato
            *xp=(*xp)->next;  //nodo attuale viene eliminato dalla lista
            d=tmp->val;     //salvo item del nodo attuale
            free(tmp);        //libero nodo attuale
            return d;
        }
    }
    return item_set_void();
}

Item estrai_date(link* hp, data_t d1, data_t d2){
    link* xp;
    link tmp;
    Item d;

    for(xp=hp; *xp!=NULL; xp=&((*xp)->next)){
        if(compare_date(d2,(*xp)->val.data_nascita)>0){         //Data di xp è prima di d2
            if(compare_date(d1,(*xp)->val.data_nascita)<0){     //Data di xp è dopo di d1
                tmp=*xp;    //tmp:link corrispondente al nodo trovato
                *xp=(*xp)->next;  //nodo attuale viene eliminato dalla lista
                d=tmp->val;     //salvo item del nodo attuale
                free(tmp);        //libero nodo attuale
                return d;
            }
        }
        else        //Se la data di xp è dopo la seconda data esco
            break;
    }
    return item_set_void();
}

/*Sentinelle
void stampa_anagrafica(link h, link z, FILE* fp){
    link x;
    for(x=h->next; x!=z; x=x->next)
        stampa_nodo(x,fp);
}
void leggiFile(link h, link z, FILE* fp){
    Item d;
    int prosegui=1;

    while(prosegui){
        d=newItem(fp);
        if(item_check_void(d))
            prosegui=0;
        else
            list_sorted_insert(d,h,z);
    }
}
void list_sorted_insert(Item val, link h, link z){
    link *xp;

    if(h->next==z || compare_date(val.data_nascita, h->next->val.data_nascita) < 0){
        h->next=newNode(val,h->next);
        return;
    }

    for( xp=&(h->next);
        ( (*xp)!=z ) && ( compare_date(val.data_nascita, (*xp)->val.data_nascita) >=0 );
         xp=&((*xp)->next) );
    //Finchè data di nascita dell'item da inserire è maggiore di quella del nodo che sto guardando continuo a iterare
    //Quando sono uscito vuol dire che lì devo inserire il nuovo item;
    (*xp)->next=newNode(val,(*xp)->next);
    return;
}*/
