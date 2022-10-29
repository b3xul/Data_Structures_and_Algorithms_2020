#include <stdio.h>
#include <stdlib.h>

typedef struct studente {
    char cognome[MAXS];
    char nome[MAXS];
    int matr;
    float media;
} stud_t;

int main(int argc, char *argv[]) {

    /*Modalità 1: struct intere*/
    stud_t elenco[MAXN];

    int ns = leggiStud(argv[1],elenco,MAXN);    //Riempie il vettore di struct con tutti i dati

    ordStudPerMatr(elenco,ns);
    lavoroSuElencoOrd(elenco,ns);
    scriviStud(argv[2],elenco,ns);

    /*Modalità 2: puntatori a struct*/
    stud_t elenco[MAXN], *elencoRif[MAXN];
    int i;
    int ns = leggiStud(argv[1],elenco,MAXN);    //Riempie il vettore di struct con tutti i dati

    for (i=0; i<ns; i++)                        //Riempie il vettore di puntatori a struct con gli indirizzi di tutte le struct
        elencoRif[i]=&elenco[i];

    ordRifStudPerMatr(elencoRif,ns);            //Passo solo un vettore di puntatori invece che un vettore a struct
    lavoroSuElencoRifOrd(elencoRif,ns);
    scriviRifStud(argv[2],elencoRif,ns);
    /*Estensione: ordinare con più chiavi*/
    stud_t el[MAXN], *elRif0[MAXN],*elRif1[MAXN], *elRif2[MAXN];
    int i;
    int ns = leggiStud(argv[1],el,MAXN);

    for (i=0; i<n; i++)
        elRif0[i] = elRif1[i] = elRif2[i] = &el[i];

    ordRifStudPerMatr(elRif0,ns);
    ordRifStudPerCogn(elRif1,ns);
    ordRifStudPerMedia(elRif2,ns);
    /*Filtrare elenco*/
    ns2 = filtraPerMedia(el,elRif,ns,soglia);   //Scrive in elRif solo quelli che superano il filtro

    return 0;
}

int leggiStud(char *nomeFile, stud_t *el, int nmax) {
    int i;
    FILE *fp = fopen(nomeFile,"r");
    for (i=0; i<nmax; i++) {
        if (fscanf(fp,"%s%s%d%f", el[i].cognome, el[i].nome, &el[i].matr, &el[i].media)==EOF)
            break;
    }
    fclose(fp);
    return i;
}

void scriviStud(char *nomeFile, stud_t *el, int n) {
    int i;
    FILE *fp = fopen(nomeFile,"w");
    for (i=0; i<n; i++) {
        fprintf(fp, "%s %s %d %f\n", el[i].cognome, el[i].nome, el[i].matr, el[i].media);
    }
    fclose(fp);
}

int confrMatrByValue(stud_t s1, stud_t s2) {
    return s1.matricola-s2.matricola;
}

int confrMatrByRef(stud_t *ps1, stud_t *ps2) {
    return ps1->matricola-ps2->matricola;
}

void ordStudPerMatr(stud_t *el, int n) {
    stud_t temp;
    int i, j, imin;

    for (i=0; i<n-1; i++) {
        imin = i;
        for (j = i+1; j < n; j++)
            if (confrMatr(el[j],el[imin])<0)    //CONFRONTA PASSANDO LE INTERE STRUCT BY VALUE O(n) per copiarle
                imin = j;
            //ALTERNATIVA: if (confrMatrByRef(&el[j],&el[imin])<0)  Confronto by reference O(1)
        temp = el[i];                           //SPOSTA INTERE STRUCT O(n) (temp è una stud_t)
        el[i] = el[imin];
        el[imin] = temp;
    }
}

void ordRifStudPerMatr(stud_t **elR, int n) {
    stud_t *temp;
    int i, j, imin;

    for (i=0; i<n-1; i++) {
        imin = i;
        for (j = i+1; j < n; j++)
            if (confrMatrByRef(elR[j],elR[imin])<0) //Confronta passando i puntatori a struct O(1) per copiarli
                imin = j;
        temp = elR[i];                          //Sposta solo i puntatori a struct O(1) (temp è un stud_t* )
        elR[i] = elR[imin];
        elR[imin] = temp;
    }
}

int filtraPerMedia(stud_t *el, stud_t **elR, int n, float s){
    int i, n2;
    for (i=n2=0; i<n; i++)
        if (el[i].media>=s)
            elR[n2++] = &el[i];     //Legge il vettore di struct el e inserisce gli indirizzi delle struct che soddisfano il criterio
                                    //in un vettore di puntatori a struct, così non deve ricopiare ogni struct che soddisfi

    return n2;
}
