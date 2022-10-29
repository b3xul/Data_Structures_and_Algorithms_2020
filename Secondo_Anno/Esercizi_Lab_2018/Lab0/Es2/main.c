#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#define MAX_S 21

int conta(char S[20], int n);
int isvocal(char c);
void print_substring(char S[20],int l,int r);

int n_vocals=2;

int main()
{

    char filename[MAX_S];
    char word[MAX_S];
    FILE* fi;
    int n_words,i,n,tot_substrings=0,i_substrings;


    printf("Inserire nome file (max 20): ");
    scanf("%s",filename);

    if((fi=fopen(filename,"r"))==NULL){
        fprintf(stderr,"Impossibile aprire %s",filename);
        exit(-1);
    }

    printf("Inserire dimensione sottostringhe cercate: ");
    scanf("%d",&n);

    fscanf(fi,"%d",&n_words);

    for(i=0;i<n_words;i++){
        fscanf(fi,"%s",word);
        i_substrings=conta(word,n);
        printf("Line %d: %d substrings\n\n",i,i_substrings);
        tot_substrings+=i_substrings;
    }
    printf("Nel file sono presenti %d sottostringhe di dimensione %d con %d vocali",tot_substrings,n,n_vocals);

    return 0;
}

int conta(char S[20], int n){
    printf("Eseguendo conta...\n");
    int i,l,r,length,partial_vocals,tot_substrings=0;
    int vocals[20];
    /*while(S[i]!='\0'){
        S[i]=toupper(S[i]);
        i++;
    }*/
    printf("%s\n",S);
    length=strlen(S);
    if(length<n)
        return 0;
    //creo vettore ausiliario 1-0 con vocali-consonanti e lavoro su quello
    for(i=0;i<length;i++){
        vocals[i]=isvocal(S[i]);
        printf("%d",vocals[i]);
    }

    printf("\n");

    l=r=partial_vocals=0;
    //primi n caratteri
    while(r<n){
        partial_vocals+=vocals[r];
        r++;
    }
    if(partial_vocals==n_vocals){
        tot_substrings++;
        print_substring(S,l,r);     //r valore dell'indice successivo
    }
    //tutti gli altri caratteri
    l++;
    while(r<length){
        partial_vocals-=vocals[l-1];    //tolgo vocale della lettera appena superata
        partial_vocals+=vocals[r];      //aggiungo vocale della lettera appena aggiunta
        if(partial_vocals==n_vocals){
            tot_substrings++;
            print_substring(S,l,r+1);     //r valore dell'indice attuale
        }
        l++;
        r++;
    }
    return tot_substrings;
}

int isvocal(char c){
    if(c=='A'||c=='E'||c=='I'||c=='O'||c=='U'||c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
        return 1;
    return 0;
}

void print_substring(char S[20],int l,int r){
    int i;
    for(i=l;i<r;i++)
        printf("%c",S[i]);
    printf("\n");
}
