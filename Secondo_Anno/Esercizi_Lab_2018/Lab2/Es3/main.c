#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

/*3 strategie:
1. per ogni sequenza rileggo il file da capo e man mano che scorro le parole vedo se contengono la sequenza data
2. salvo tutte le parole e per ogni sequenza cerco se la parola contiene la sequenza
3. scorro il file carattere per carattere, man mano confronto e salvo matrice con i=sequenza e contenente posizioni delle parole che la contengono
Scelgo strategia 2 per ottimizzare il tempo impiegato, vantaggioso se voglio ricercare tante sequenze, a fronte di alto costo in termini di memoria
*/

#define MAX_SEQ 6
#define N_SEQ 20
#define MAX_PAROLA 26
#define MAX_RIGA 201
#define N_PAROLE 100

int leggiParole(FILE *fp,char parole[N_PAROLE][MAX_PAROLA]);
void stampaPosizioni(char seq[MAX_SEQ],char parole[N_PAROLE][MAX_PAROLA],int n_parole);
char* strstr_i(char* str1,char* str2);
#define DBG 1

int main()
{

    int i,n_seq,n_parole;
    char sequenze[N_SEQ][MAX_SEQ];
    char parole[N_PAROLE][MAX_PAROLA];
    FILE *fp;

    /*Leggo parole*/
    if((fp=fopen("testo.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file testo\n");
        exit(-1);
    }
    n_parole=leggiParole(fp,parole);
#if DBG
    for(i=0;i<n_parole;i++){
        printf("%s\n",parole[i]);
    }
#endif // DBG

    /*Leggo sequenze*/
    if((fp=fopen("sequenze.txt","r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file sequenze\n");
        exit(-1);
    }
    fscanf(fp,"%d",&n_seq);
    for(i=0;i<n_seq;i++){
        fscanf(fp,"%s",sequenze[i]);
    }

#if DBG
    for(i=0;i<n_seq;i++){
        printf("%s\n",sequenze[i]);
    }
#endif // DBG

    for(i=0;i<n_seq;i++){
        printf("La sequenza %s e' contenuta in:\n",sequenze[i]);
        stampaPosizioni(sequenze[i],parole,n_parole);
    }
    return 0;
}

int leggiParole(FILE *fp,char parole[N_PAROLE][MAX_PAROLA]){
    char c;
    int i=0,j=0;

    while(fscanf(fp,"%c",&c)!=EOF){
        if(isalnum(c))
            parole[i][j++]=c;   //Ogni carattere alnum viene aggiunto alla parola corrente
        else if(j!=0){           //Ogni carattere non alnum se è il primo dopo la fine della parola allora passo alla parola successiva
            parole[i][j]='\0';
            i++;
            j=0;
        }                       //Altrimenti lo ignoro
    }

    return i;   //numero di parole
}

void stampaPosizioni(char seq[MAX_SEQ],char parole[N_PAROLE][MAX_PAROLA],int n_parole){
    int i;
    for(i=0;i<n_parole;i++){
        if(strstr_i(parole[i],seq)!=NULL)     //Parole[i] contiene seq (N.B. Stesso lavoro di strcasestr)
            printf("%s (posizione %d)\n",parole[i],i+1);
    }
}

char* strstr_i(char* s1,char* s2){
    int l1=strlen(s1);
    int l2=strlen(s2);
    int i;
    char str1[l1+1];
    char str2[l2+1];

    for(i=0;i<l1;i++)
        str1[i]=toupper(s1[i]);
    for(i=0;i<l2;i++)
        str2[i]=toupper(s2[i]);
    /*basta strnicmp*/

    for(i=0;i<=l1-l2;i++){
        if(strncmp(&str1[i],str2,l2)==0)
            return &s1[i];
    }
    /*Es: casa, as
    l1-l2=2 -> for scorre su 'c', su 'a' e su 's'
    ad ogni posizione passa alla strncmp la sottostringa che inizia nella posizione corrente: 'casa', 'asa', 'sa'
    e compara le prime 2 lettere di questa sottostringa con 'as'
    se trova un match ritorna l'indirizzo di inizio della sottostringa &str1[i]
    */
    return NULL;
}
