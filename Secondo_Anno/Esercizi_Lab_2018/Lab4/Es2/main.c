#include <stdio.h>
#include <stdlib.h>

void Swap( int *v, int n1, int n2);
int partition ( int *A, int l, int r );
void QuickSortR( int *A, int l, int r );
void QuickSort(int *A, int N);
int Majority(int* a, int n);

int main()
{
    int a[9]={3,2,2,4,4,4,4,4,1};
    int n=9,i,element;

    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");

    //Permutazione random?
    QuickSort(a,n);

    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");

    element=Majority(a,n);

    printf("Elemento maggioritario %sesiste",(element==-1)?"non ":"");

    if(element!=-1)
            printf(" e vale %d",element);
    return 0;
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

int Majority(int* a, int n){
    int i,x,count;

    count=1;
    x=a[0];
    i=1;
    while(i<n){
        if(a[i]==x){
            count++;
            if(count>(n/2))
                return x;
        }
        else{
            if(i>n/2)   //Sono nella seconda metà e l'elemento è diverso dal precedente, che quindi non è l'elemento maggioritario: posso chiuderla qui perchè sicuramente gli elementi nuovi successivi non saranno maggioritari
                return -1;
            x=a[i];
            count=1;
        }
        i++;
    }
    return -1;
}
