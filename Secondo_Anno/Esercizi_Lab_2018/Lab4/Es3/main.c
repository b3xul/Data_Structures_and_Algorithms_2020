#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MIN_STR 10
#define LETTERS 26

typedef struct possible{
    char** array;
    int size;
}Possible_t;

Possible_t buildRegexStructure(char* regexp);
char* cercaRegexp(char* src, char* regexp,Possible_t pos);
char* checkRegex(char* src, Possible_t pos);
int find_char(char c, char* str);

int main()
{
    char text[50]={"Questa e' un unica stringa, giusto? unaca. unOca"};
    char regex[10]={"un[^O]c"};
    //scanf("%s",regex);
    int trovato=0;
    char* occorrenza;

    Possible_t pos=buildRegexStructure(regex);

    char* text_p=strdup(text);

    do {
        occorrenza=cercaRegexp(text_p,regex,pos);
        if (occorrenza) {
            printf("<%.*s> (posizione %d (indirizzo: %p))\n", pos.size, occorrenza,(int)(occorrenza-text_p)+1,occorrenza);
            /* salta parola trovata. Cercane un'altra (con eventuali sovrapposizioni)*/
            text_p = occorrenza + 1;
            trovato++;
        }
    } while (occorrenza!=NULL);

    printf("Trovat%c %d match di <%s> in <%s>.\n",(trovato==1)?'o':'i',trovato,regex,text);

    return 0;
}

Possible_t buildRegexStructure(char* regexp){
    int i,j,k,m,negate,Rsize=strlen(regexp),Bsize;
    char first;
    char buffer[MIN_STR];

    Possible_t pos;
    pos.size=0;

    /*Creo vettore che in ogni posizione contiene la stringa di caratteri che quella posizione può contenere nella stringa cercata*/
    pos.array=(char**)malloc(MIN_STR*sizeof(char));  //Alloco dimensione minima per una stringa sensata da cercare, se ho bisogno rialloco, altrimenti cambio define se so già che avrò stringhe più grandi
    if(pos.array==NULL){
        fprintf(stderr,"Impossibile allocare\n");
        exit(-1);
    }

    for(i=0,k=0;i<Rsize;i++){    //Per ogni elemento di regexp (indice i: lettere di regex) riempio il vettore possibile di stringhe (o singoli caratteri) (indice k= pos[k] lettere in posizione k della stringa)
    j=0;
    switch(regexp[i]){
        case '.':
            pos.array[k]=(char*)malloc(sizeof(char)+1);
            pos.array[k][j++]=(char)0;
            break;
        case '[':
            i++;
            negate=(regexp[i]=='^');

            j=0;
            /*Creo buffer contenente quello che sta dentro alle parentesi*/
            while(regexp[i]!=']'){
                /*Realloc buffer*/
                buffer[j]=regexp[i];
                i++;
                j++;
            }
            //i++;    Saltare ] non necessario, i++ avviene dopo il ciclo
            Bsize=j;    //ai=2

            pos.array[k]=(char*)malloc(2*LETTERS*sizeof(char)+1);

            /*Riempio pos.array*/
            if(negate){
                m=0;
                for(j=0;j<LETTERS;j++){
                    if(!find_char('a'+j,buffer))
                        pos.array[k][m++]='a'+j;
                    if(!find_char('A'+j,buffer))
                        pos.array[k][m++]='A'+j;
                }
            }
            else{
                for(j=0;j<Bsize;j++){
                    pos.array[k][j]=buffer[j];
                }
            }
            break;
        case '\\':
            pos.array[k]=(char*)malloc(LETTERS*sizeof(char)+1);
            first=(regexp[i+1]=='a')?'a':'A';
            for(j=0;j<LETTERS;j++){
                pos.array[k][j]=first+j;
            }
            i=i+1;  //La 'a' fa parte del metacarattere, non è una lettera a s
            break;
        default:
            pos.array[k]=(char*)malloc(sizeof(char)+1);
            pos.array[k][j++]=regexp[i];
    }
    pos.array[k++][j]='\0';
    pos.size++;
    /*TODO:Realloc*/
    }

    return pos;
}
char* cercaRegexp(char* src, char* regexp, Possible_t pos){

    int i, SrcSize=strlen(src);
    char* res=NULL;

    for(i=0;i<SrcSize;i++){
        res=checkRegex(src+i,pos);
        if(res!=NULL){
            break;
        }
    }

    return res;
}

char* checkRegex(char* str, Possible_t pos){
    int i;

    for(i=0;i<pos.size;i++){    //Scorrere linearmente un vettore è più efficiente di ricalcolare ogni volta se l'elemento soddisfa la regex, nel caso di regex complicate
        if(!find_char(str[i],pos.array[i]))   //pos.array[i] (lista caratteri possibili in posizione i) non contiene str[i] (carattere in posizione i della stringa che sto valutando)
            return NULL;
    }


    return str;
}

int find_char(char c, char* str){
    int i,size=strlen(str);

    if(str[0]==0)
        return 1;

    for(i=0;i<size;i++){
        if(str[i]==c)
            return 1;
    }

    return 0;
}
