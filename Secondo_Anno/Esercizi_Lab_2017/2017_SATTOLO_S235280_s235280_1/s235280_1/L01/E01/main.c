#include <stdio.h>
#include <stdlib.h>
#define NMAX 20

void stampavettore(int v[],int n);

int ordinavettore(int vp[],int n);

int unione(int v1[],int n,int v2[],int m,int u[]);

int differenza(int v1[],int n,int v2[],int m,int d[]);

int intersezione(int v1[],int n,int v2[],int m,int in[]);

int main()
{
    int v1[NMAX]; int vp1[NMAX];
    int v2[NMAX]; int vp2[NMAX];
    int u[NMAX*2];
    int d[NMAX];
    int in[NMAX*2];

    int i,n,m,luno,ldue,lu,ld,li;

    printf("Dimensione v1 (max 20): ");
    scanf("%d",&n);

    printf("Inserisci primo vettore di interi: ");
    for(i=0;i<n;i++){
        scanf("%d",&v1[i]);
    }

    stampavettore(v1,n);

    printf("Dimensione v2 (max 20): ");
    scanf("%d",&m);

    printf("Inserisci secondo vettore di interi: ");
    for(i=0;i<m;i++){
        scanf("%d",&v2[i]);
    }

    stampavettore(v2,m);

    for(i=0;i<n;i++){
        vp1[i]=v1[i];
    }
    luno=ordinavettore(vp1,n); //Creo vettore interno vp in ordine e senza ripetizioni

    stampavettore(vp1,luno);

    for(i=0;i<m;i++){
        vp2[i]=v2[i];
    }
    ldue=ordinavettore(vp2,m);

    stampavettore(vp2,ldue);


    lu=unione(vp1,luno,vp2,ldue,u);
    printf("Vettore unione: ");
    stampavettore(u,lu);

    ld=differenza(vp1,luno,vp2,ldue,d);
    printf("Vettore differenza: ");
    stampavettore(d,ld);

    li=intersezione(vp1,luno,vp2,ldue,in);
    printf("Vettore intersezione: ");
    stampavettore(in,li);

    return 0;
}


void stampavettore(int v[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    printf("\n");

    return;
}

int ordinavettore(int vp[],int n){
    int i,j,k,x;

    for(i=1;i<n;i++){
        x=vp[i];
        j=i-1;
        while(j>=0&&x<vp[j]){
            vp[j+1]=vp[j];
            j--;
        }
        vp[j+1]=x;
    }
    for(i=0;i<n;i++){ //controlla ripetizioni all'interno del vettore appena ordinato
        for(j=i+1;j<n;j++){
            if(vp[i]==vp[j]){
                k=j;
                while(k<n){
                    vp[k]=vp[k+1];
                    k++;
                }
                j--;//per rifare controllo con nuovo vp[j]
                n--;//riduci dimensione totale vettore

            }
        }
    }
    return n;
}

int unione(int v1[],int n,int v2[],int m,int u[]){
    int i=0,j=0,k=0;

    //gestione in parallelo
    while(i<n&&j<m){
        if(v1[i]<=v2[j]){
            u[k]=v1[i];
            if(v1[i]==v2[j]) j++;
            i++;
            k++;
        }
        else{
            u[k]=v2[j];
            j++;
            k++;
        }
    }
    //gestione coda
    if(i<n){ //è finito prima il secondo vettore
        while(i<n){
            u[k]=v1[i];
            i++;
            k++;
        }
    }
    else if(j<m){ //è finito prima il primo vettore
        while(j<m){
            u[k]=v2[j];
            j++;
            k++;
        }
    }

    return k;
}

int differenza(int v1[],int n,int v2[],int m,int d[]){
    int i=0,j=0,k=0;

    while(i<n&&j<m){
        if(v1[i]<v2[j]){
            d[k]=v1[i];
            i++;
            k++;
        }
        else if(v1[i]>v2[j]){
            d[k]=v2[j];
            j++;
            k++;
        }
        else{
            i++;
            j++;
        }
    }
    if(i<n){
        while(i<n){
            d[k]=v1[i];
            i++;
            k++;
        }
    }
    else if(j<m){
        while(j<m){
            d[k]=v2[j];
            j++;
            k++;
        }
    }
    return k;
}

int intersezione(int v1[],int n,int v2[],int m,int in[]){
    int i=0,j=0,k=0;

    while(i<n&&j<m){
        if(v1[i]<=v2[j]){
            if(v1[i]==v2[j]){
                in[k]=v1[i];
                j++;
                k++;
            }
            i++;
        }
        else if(v1[i]>=v2[j]){
            if(v1[i]==v2[j]){
                in[k]=v2[j];
            i++;
            k++;
            }
            j++;
        }
    }
    return k;
}
