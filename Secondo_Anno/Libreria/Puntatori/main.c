#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_DIM 30
#define CMD_SIZE 255

void swap(int* a,int* b);
int leggi(int* A,int max_dim,FILE* fp);
void ordinaVettore(char* v[], int n);

int main()
{
    /*Dichiarazione e inizializzazione separate*/
    int var=8,var2=2;
    int* var_p; //Dichiara che il dato puntato da var2_p sarà un intero

    var_p=&var; //Da questo momento var_p=indirizzo di var per cui applicandovi l'operatore di dereferenziazione *
                //vedrò il contenuto dell'indirizzo contenuto in var_p
    //scanf("%d",var_p);   //==scanf("%d",&var);
    printf("Valore di var_p: %p\n",var_p);
    printf("Contenuto di var_p: %d\n",*var_p); //==printf("%d",var);

    /*Dichiarazione e inizializzazione insieme*/
     int* var2_p=&var;  //N.B. Funziona esattamente come prima: dichiara che il dato puntato da var2_p sarà un intero
                        //e poi assegna a var2_p l'indirizzo di var
    printf("Valore di var2_p: %p\n",var2_p);
    printf("Contenuto di var2_p: %d\n",*var2_p); //==printf("%d",var);

    /*Assegnazioni*/
    int* var3_p;
    var3_p=var_p;  //E' possibile assegnare alla variabile puntatore
    printf("Valore di var3_p: %p\n",var_p);
    *var3_p=5;     //E' possibile assegnare anche al dato puntato dal puntatore
    printf("Contenuto di var3_p: %d\n",*var3_p);

    /*Aritmetica dei puntatori*/
    printf("Valore di var3_p+1 (sizeof(*p)=%d): %p\n",sizeof(*var3_p),var3_p+1);

    /*Passaggio di parametri*/
    printf("var=%d, var2=%d\n",var,var2);
    swap(&var,&var2);   //Quando viene richiamata swap si effettua a=&var e b=&var2
                        //per cui usando *a e *b potrò accedere ai dati puntati da a e b,
                        //pur non essendo a e b visibili alla funzione (non vengono copiati),
                        //ma copiando solo le variabili puntatori contenenti i loro indirizzi
    printf("var=%d, var2=%d\n",var,var2);

    /*Dualità Puntatori-Vettori*/
    int v[10];
    int i;
    for(i=0;i<10;i++)
        v[i]=i;
    int* v_p=&v[0];
    printf("v_p=&v[0]\nv=%p, v_p=%p, *v=%d, *v_p=%d\n",v,v_p,*v,*v_p);

    /*Creazione di sottovettori*/
    int* sv;
    int l=3,r=6,n;
    sv=&v[l];    //Indirizzo di inizio del sottovettore
    n=r-l+1;    //Dimensione del sottovettore= 6-3+1=4 (passare da differenza di indici a lunghezza)
    for(i=0;i<n;i++)
        printf("%d ",sv[i]);    //Notazione for classico ma su un puntatore, è come se sv fosse un nuovo vettore
                                //ma in realtà lavora sui dati di v
    printf("\n");

    /*Passaggio di vettori come parametri*/
    /*int dim1,dim2;
    int A[MAX_DIM];
    dim1=leggi(A,MAX_DIM,stdin);
    printf("dim_effettiva vettore A=%d\n",dim1);
    fflush(stdin);
    dim2=leggi(&A[8],MAX_DIM,stdin);
    printf("dim_effettiva sottovettore che parte da A[8]=%d\n",dim2);
    fflush(stdin);
    for(i=0;i<MAX_DIM;i++)
        printf("%d ",A[i]);
    printf("\n");
    */
    /*Manipolazione di stringhe 1:Cercare sottostringa */
    char S[12]="Testo lungo";
    char C[4]="ung";    //Stringa da cercare
    char* char_p;
    char_p=strstr(S,C);
    printf("Indirizzo S=%p\nIndirizzo S+7=%p, Contenuto S+7=%s\nIndirizzo C=%p, contenuto C=%s\nIndirizzo char_P=%p, , contenuto char_P=%s\n",S,S+7,S+7,C,C,char_p,char_p);

    /*Manipolazione di stringhe 2:Acquisire numero non noto di interi*/
    int x,cnt=0;
    char riga_da_parsificare[CMD_SIZE];
    char* line;
    //fgets(riga_da_parsificare,CMD_SIZE,stdin);
    line=riga_da_parsificare;

    while(sscanf(line,"%d%n",&x,&i)>0){
        line=line+i;    //sscanf legge a partire dal puntatore passato come primo parametro, per cui
                        //dopo aver letto %n caratteri (ossia i caratteri di cui è composto il dato letto nel %d)
                        //devo spostare il puntatore da cui deve partire la sscanf di i posizioni (aritmetica dei puntatori)
        cnt++;  //conto numero di interi effettivamente letti
    }

    /*Vettori di puntatori*/
    int ns;
    char* vettore_di_stringhe[20];  //20 puntatori a char (= 20 stringhe)
    char buf[520];      //conviene rispetto a una matrice di 20*50 se so che al massimo la somma delle lunghezze delle stringhe sarà 500 (+20 \0)
    for(i=ns=0;ns<20;ns++){
        vettore_di_stringhe[ns]=buf+i;  //il vettore di stringhe contiene solo puntatori interni a un vettore che le contiene tutte: risparmio spazio rispetto a una matrice
        gets(vettore_di_stringhe[ns]);
        if(strlen(vettore_di_stringhe[ns])==0)    //stringa vuota termina inserimento
            break;
        i=i+strlen(vettore_di_stringhe[ns])+1;    //punta all'indirizzo successivo in cui inizierà la prossima stringa (buf+i)
    }
    ordinaVettore(vettore_di_stringhe,ns);
    printf("Stringhe ordinate:\n");
    for(i=0;i<ns;i++)
        printf("%s\n",vettore_di_stringhe[i]);

    /*Possibili errori*/
    //*var2_p=&var;   //*var2_p è un intero, mentre &var non è un intero, è un HEX!

    return 0;
}

void swap(int* a,int* b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

int leggi(int* A,int max_dim,FILE* fp){
    int i,fine=0;
    for(i=0;i<max_dim&&!fine;i++){
        if(fscanf(fp,"%d",&A[i])!=1)
            fine=1;
    }
    return i-1;     //ritorna numero di valori effettivamente letti
}

void ordinaVettore(char* v[], int n){
    //Selection sort con puntatori (stringhe)
    int i,j,min;
    char* tmp;

    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            if(strcmp(v[min],v[j])>0)
                min=j;
        }
        tmp=v[i];
        v[i]=v[min];
        v[min]=tmp;
    }
}
