#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define B 200   //buffer cognome_nome
#define S 20    //dim max stringa

typedef struct studente{
    char *cognome_nome;
    int matricola;
    int voto;
} Studente;

typedef struct Database_{
    Studente *studenti;
    int n;
    int max_dim;
}Database;

int Insert_Student(Database *database_P,FILE *nomefile);
int Converti_stringa(char *buff);
int Insert_in_database(Database *database_P,char *cognome_nome);
void Check_database_size(Database *database_P);
void Print_Database(Database *database_P, FILE *nomefile);
void Visualizza(Database *database_P);
void Cancella(Database *database_P);
int CBinary_Search(Database *database_P, int l, int r, char *cognome_nome);
int IBinary_Search(Database *database_P, int l, int r, int matricola);
void Libera(Database *database_P);

int main()
{
    int finito=0;
    char scelta;
    char nomefile[S];
    FILE *fi,*fo;
    Database *database_P=(Database *)malloc(sizeof(Database));
    database_P->studenti=(Studente *)malloc(sizeof(Studente));
    database_P->n=0;
    database_P->max_dim=1;

    while(!finito){
        printf( "Inserire comando:\n");
            printf( "I <Cognome_Nome> <Matricola> <Voto> per inserire i dati di uno studente.\n");
            printf( "C <Cognome_Nome> per cancellare i dati dello studente con quel nome.\n");
            printf( "C <Matricola> per cancellare i dati dello studente con quella matricola.\n");
            printf( "V <Cognome_Nome> per visualizzare i dati dello studente con quel nome.\n");
            printf( "V <Matricola> per visualizzare i dati dello studente con quella matricola.\n");
            printf( "P per stampare tutto il data-base.\n");
            printf( "L <Nomefile> per leggere i dati (gia' ordinati) dal file con quel nome.\n");
            printf( "S <Nomefile> per salvare i dati del data-base nel file con quel nome.\n");
            printf( "T per terminare il programma\n");

        scanf(" %c",&scelta);

        switch(scelta){
            case 'I':
                Insert_Student(database_P,stdin);
                printf("\n");
                break;
            case 'C':
                Cancella(database_P);
                printf("\n");
                break;
            case 'V':
                Visualizza(database_P);
                printf("\n");
                break;
            case 'P':
                Print_Database(database_P,stdout);
                printf("\n");
                break;
            case 'L':
                scanf("%s",nomefile);
                if((fi=fopen(nomefile,"r"))==NULL)
                    fprintf(stderr,"File di input non trovato.");
                else{
                    while(Insert_Student(database_P,fi));
                }
                printf("\n");
                break;
            case 'S':
                scanf("%s",nomefile);
                if((fo=fopen(nomefile,"w"))==NULL)
                    fprintf(stderr,"Errore nell'apertura del file di output.");
                else{
                    Print_Database(database_P,fo);
                }
                printf("\n");
                break;
            case 'T':
                finito=1;
                printf("\n");
                break;
            default:
                printf("Comando non riconosciuto!\n");
                printf("\n");
                break;
        }
    }

    Libera(database_P);

    return 0;
}

int Insert_Student(Database *database_P,FILE *nomefile){

    char buff[S];
    char cognome_nome[B]="\0";
    int flag=0;
    int pos;
    int finito=0;
    int cont=0;

    while(!finito){
        if(fscanf(nomefile,"%s",buff)==EOF)
            return 0;
        else{
            if(isalpha(buff[0])){
                if(cont!=0)
                    strcat(cognome_nome," ");
                cont++;
                strcat(cognome_nome,buff);
            }
            else if(flag==0){
                pos=Insert_in_database(database_P,cognome_nome);
                database_P->studenti[pos].matricola=Converti_stringa(buff);
                flag=1;
            }
            else{
                database_P->studenti[pos].voto=Converti_stringa(buff);
                finito=1;
            }
        }

    }


    return 1;
}

int Converti_stringa(char *buff){
    int i,res=0;
    int length=strlen(buff);

    for(i=0;i<length;i++){
        res=10*res+buff[i]-'0';
    }

    return res;
}

int Insert_in_database(Database *database_P,char *cognome_nome){

    int i;

    Check_database_size(database_P);

    for(i=database_P->n; (i>0&&(strcmp(database_P->studenti[i-1].cognome_nome,cognome_nome)>0));i--)
        database_P->studenti[i]=database_P->studenti[i-1];

    database_P->studenti[i].cognome_nome=strdup(cognome_nome);
    database_P->n++;

    return i;
}

void Check_database_size(Database *database_P){

    if((database_P->n+1)>database_P->max_dim){
        database_P->max_dim=2*database_P->max_dim;
        database_P->studenti=(Studente *)realloc(database_P->studenti,database_P->max_dim*sizeof(Studente));

        if(database_P->studenti==NULL)
            exit(-1);
    }

    return;
}

void Print_Database(Database *database_P,FILE *nomefile){
    int i;
    for(i=0;i<database_P->n;i++)
        fprintf(nomefile,"%s %d %d\n",database_P->studenti[i].cognome_nome,database_P->studenti[i].matricola,database_P->studenti[i].voto);

    return;
}

void Visualizza(Database *database_P){
    char buff[S];
    char cognome_nome[B]="\0";
    int i,pos=-1,matricola,finito=0,cont=0;
    char ch;

    while(!finito){
        scanf("%s%c",buff,&ch);

        if(isalpha(buff[0])){
            if(cont!=0)
                strcat(cognome_nome," ");
            cont++;
            strcat(cognome_nome,buff);

            if(ch=='\n')
                finito=1;
        }
        else{
            matricola=Converti_stringa(buff);
            for(i=0;i<database_P->n&&pos==-1;i++)
                if(database_P->studenti[i].matricola==matricola)
                    pos=i;
            finito=1;
        }
    }

    if(isalpha(buff[0]))
        pos=CBinary_Search(database_P, 0,database_P->n,cognome_nome);

    if(pos==-1){
        printf("Studente non presente.\n");
    }
    else
        printf("%s %d %d\n",database_P->studenti[pos].cognome_nome,database_P->studenti[pos].matricola,database_P->studenti[pos].voto);

    return;
}

int CBinary_Search(Database *database_P, int l, int r, char *cognome_nome)
{
	int m;

	while(l<=r){
		m =  l + (r-l)/2;
		if(strcmp(database_P->studenti[m].cognome_nome,cognome_nome)==0)
            return(m);
        if(strcmp(database_P->studenti[m].cognome_nome,cognome_nome)<0)
            l = m+1;
		else
            r = m-1;
	}

	return(-1);
}


void Cancella(Database *database_P){
    char buff[S];
    char cognome_nome[B]="\0";
    int i,pos=-1,matricola,finito=0,cont=0;
    char ch;

    while(!finito){
        scanf("%s%c",buff,&ch);

        if(isalpha(buff[0])){
            if(cont!=0)
                strcat(cognome_nome," ");
            cont++;
            strcat(cognome_nome,buff);

            if(ch=='\n')
                finito=1;
        }
        else{
            matricola=Converti_stringa(buff);
            for(i=0;i<database_P->n&&pos==-1;i++)
                if(database_P->studenti[i].matricola==matricola)
                    pos=i;
            finito=1;
        }
    }


    if(isalpha(buff[0]))
        pos=CBinary_Search(database_P, 0,database_P->n,cognome_nome);

    if(pos==-1){
        printf("Studente non presente.\n");
    }
    else{
        free(database_P->studenti[pos].cognome_nome);
        database_P->n--;
        for(i=pos;i<database_P->n;i++){
            database_P->studenti[i]=database_P->studenti[i+1];
        }
    }

    return;
}

void Libera(Database *database_P){
    int i;

    for(i=0;i<database_P->n;i++)
        free(database_P->studenti[i].cognome_nome);

    free(database_P->studenti);
    free(database_P);

    return;
}
