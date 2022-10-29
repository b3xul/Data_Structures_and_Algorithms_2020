#include <stdio.h>
#include <stdlib.h>

int* leggi_file(FILE* fp, int* n);
void solve(int* val, int n);
int solveR(int pos, int n, int* val);
int max(int a,int b);
int solveDP(int* val, int n);
void displaySol(int* val, int n, int* opt);

int main(int argc, char **argv) {
  int n, *val;
  FILE *fp;

  fp = fopen("val3.txt", "r");
  if (fp == NULL)
    exit(-1);

  val = leggi_file(fp, &n);

  solve(val, n);
  solveDP(val, n);

  fclose(fp);
  return 0;
}

int* leggi_file(FILE* fp, int* n){
    int* a;
    int i;

    fscanf(fp,"%d",n);
    printf("n=%d\n",*n);

    a=(int*)malloc((*n+1)*sizeof(int));
    a[0]=0;

    for(i=1;i<=*n;i++){
        fscanf(fp,"%d",&a[i]);
        printf("%d ",a[i]);
    }
    printf("\n");
    return a;
}

void solve(int* val, int n){
    /*Soluzione ricorsiva la uso solo per trovare il VALORE della soluzione, per sfruttarne la logica,
    ma poi implementerò la ricerca sia del valore che della soluzione usando la programmazione dinamica!*/


    int pos=n,tot=0;

    tot=solveR(pos,n,val);
    printf("Soluzione ricorsiva:\n");
    printf("Totale massimo di popolazione coperta: %d\n\n",tot);

}

int solveR(int pos, int n, int* val){
    if(pos==0)
        return 0;

    if(pos==1)
        return val[1];


    return max( solveR(pos-1,n,val) , solveR(pos-2,n,val)+val[pos] );
}

int max(int a,int b){
    return (a>b)?a:b;
}

int solveDP(int* val, int n){
    int i;
    int* opt=(int*)calloc(n+1,sizeof(int));
    opt[0]=0;
    opt[1]=val[1];

    for(i=2;i<n+1;i++){
        opt[i]= max( opt[i-1] , opt[i-2]+val[i]);
    }
    printf("Soluzione iterativa con programmazione dinamica:\n");
    printf("Totale massimo di popolazione coperta:%d\n",opt[n]);
    displaySol(val,n,opt);

    return opt[n];
}

void displaySol(int* val, int n, int* opt){
    int* sol=(int*)malloc((n+1)*sizeof(int));

    int i=n;
    sol[1]=1;   //Se non ho preso l'antenna 2 ho preso la 1 ma dal while non posso segnarlo, se invece ho preso la 2 nel while segno che non ho preso la 1
    while(i>=2){
        if(opt[i]==opt[i-1]){
            sol[i]=0;   //Non ho preso l'antenna i
            i--;
        }
        else if(opt[i]==opt[i-2]+val[i]){
            sol[i]=1;
            sol[i-1]=0;
            i-=2;
        }
    }

    printf("Citta' piazzate:\n");
    for(i=1;i<=n;i++)
        printf("%d ",sol[i]);
}
