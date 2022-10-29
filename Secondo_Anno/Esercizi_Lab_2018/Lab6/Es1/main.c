#include <stdio.h>
#include <stdlib.h>

typedef struct arco{int u; int v;}Arco;

void leggi_file(int* N, int* E, Arco** archi, int** grafo, int** sol);
int vertex_cover(int pos, int E, Arco* archi, int k, int N, int* grafo, int* sol, int start, int count);

void Swap( int *v, int n1, int n2);
int partition ( int *A, int l, int r );
void QuickSortR( int *A, int l, int r );
void QuickSort(int *A, int N);
int ricerca_binomiale(int* v, int l, int r, int k);

int main()
{
    int* grafo,*sol;
    Arco* archi;
    int k,N,E,count=0;

    leggi_file(&N,&E,&archi,&grafo,&sol);

    for(k=1;k<=N;k++){
        printf("Vertex cover con k= %d\n",k);
        count+=vertex_cover(0,E,archi,k,N,grafo,sol,0,0);
    }
    printf("Ci sono %d vertex cover.\n",count);
    return 0;
}


void leggi_file(int* N, int* E, Arco** archi, int** grafo, int** sol){
    FILE* fp;
    fp=fopen("grafo.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file.\n");
        exit(-1);
    }
    int i,j;

    fscanf(fp,"%d%d",N,E);
    int* g=(int*)malloc((*N)*sizeof(int));
    Arco* a=(Arco*)malloc((*E)*sizeof(Arco));
    int* s=(int*)malloc((*N)*sizeof(int));
    int temp[(*E)*2];

    for(i=0,j=0; i<(*N); i++){
        fscanf(fp,"%d%d",&a[i].u,&a[i].v);

        temp[j++]=a[i].u;
        temp[j++]=a[i].v;
    }

    QuickSort(temp,j);
    g[0]=temp[0];
    for(i=1,j=0; i<(*E)*2; i++){
        if(temp[i]!=g[j]){  //Se l'elemento che guardo è diverso dall'ultimo inserito nel vettore allora lo aggiungo
            j++;
            g[j]=temp[i];
        }
    }

    (*archi)=a;
    (*grafo)=g;
    (*sol)=s;
}

int vertex_cover(int pos, int E, Arco* archi, int k, int N, int* grafo, int* sol, int start, int count){  //start: vertice di inizio powerset  N:numero di elementi in grafo    E:numero di elementi in archi
    int i;
    /*Valuto tutti gli N elementi del grafo, ma mi trovo al caso terminale ogni volta che raggiungo cardinalità k, scorrendo esternamente tutte le cardinalità da 1 a N*/
    if(pos>=k){   //Sono all'ultimo dei vertici da guardare
        /*Vincolo sul powerset, per ogni arco verificare che almeno 1 dei 2 vertici sia contenuto*/
        for(i=0; i<E; i++){     //vertex cover ordinato, posso fare ricerca dicotomica
            if(!ricerca_binomiale(sol,0,pos-1,archi[i].u) && !ricerca_binomiale(sol,0,pos-1,archi[i].v))  //Nè u nè v all'interno di sol: soluzione non valida
                return count;
        }
        //Se per tutti gli archi almeno 1 dei 2 vertici era in sol allora la soluzione è valida
        count++;
        printf("Soluzione %d: ",count);
        for(i=0;i<pos;i++)
            printf("%d ",sol[i]);
        printf("\n");
        return count;
    }
    for(i=start; i<N; i++){
        sol[pos]=grafo[i];
        count=vertex_cover(pos+1,E,archi,k,N,grafo,sol,i+1,count);
    }

    return count;
}

void Swap( int *v, int n1, int n2) {
  int	temp;

  temp  = v[n1];
  v[n1] = v[n2];
  v[n2] = temp;
  return;
}

int partition ( int *A, int l, int r ) {
  int i, j;
  int x = A[r];
  i = l-1;
  j = r;
  for ( ; ; ) {
    while(A[++i]<x);
    while(A[--j]>x)
        if (j == l)
          break;

    if (i >= j)
      break;
    Swap(A, i, j);
  }
  Swap(A, i, r);
  return i;
}

void QuickSortR( int *A, int l, int r ) {
  int q;
  if (r <= l)
    return;
  q = partition(A, l, r);
  QuickSortR(A, l, q-1);
  QuickSortR(A, q+1, r);
  return;
}

void QuickSort(int *A, int N) {
  int l=0, r=N-1;
  QuickSortR(A, l, r);
}

int ricerca_binomiale(int* v, int l, int r, int k){
    int m=(l+r)/2;

    while(l<=r){
        m=(l+r)/2;
        if(v[m]==k)
            return 1;
        else if(k<v[m])
            r=m-1;
        else
            l=m+1;
    }
    return 0;
}
