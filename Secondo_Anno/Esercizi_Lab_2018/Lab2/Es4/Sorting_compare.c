#include "Item.h"
#include "Sorting_compare.h"


void InsertionSort(Item A[], int N) {
  int i, j, l=0, r=N-1;
  Item x;
  int cicli_esterni=0, cicli_interni=0, scambi=0;

  for(i = l+1; i <= r; i++) {
    cicli_esterni++;
    x = A[i];                               //x=elemento da ordinare
    j = i - 1;                              //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
    while (j >= l && ITEMlt(x, A[j])) {     //finchè x è minore dell'elemento precedente
      cicli_interni++;
      scambi++;
      A[j+1] = A[j];                        //se x è minore di quello che lo precede trasla quest'ultimo avanti di uno
      j--;
    }
    A[j+1] = x;                             //piazza x dopo quello di cui non è minore
  }

  printf("Cicli esterni: %d, Cicli interni: %d, Assegnazioni (non si contano quelle in cui si riassegna lo stesso valore): %d\n",cicli_esterni,cicli_interni,scambi);
}


void InsertionSortReversed(Item A[],int N){
    int i,j,l=0,r=N-1;
    Item x;

    for(i = l+1; i <= r; i++) {
        x = A[i];                               //x=elemento da ordinare
        j = i - 1;                              //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
        while (j >= l && ITEMgt(x, A[j])) {     //finchè x è maggiore dell'elemento precedente
          A[j+1] = A[j];                        //se x è maggiore di quello che lo precede trasla quest'ultimo avanti di uno
          j--;
        }
        A[j+1] = x;                             //piazza x dopo quello di cui non è maggiore
    }
}

void InsertionSortPartial(Item A[],int N,int l,int r){
    int i, j;
    Item x;

    if(l<0 || l>r || r>=N){
        fprintf(stderr,"Indici errati\n");
        exit(-1);
    }
    for(i = l+1; i <= r; i++) {
        x = A[i];                               //x=elemento da ordinare
        j = i - 1;                              //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
        while (j >= l && ITEMlt(x, A[j])) {     //finchè x è minore dell'elemento precedente
            A[j+1] = A[j];                      //se x è minore di quello che lo precede trasla quest'ultimo avanti di uno
            j--;
        }
        A[j+1] = x;                             //piazza x dopo quello di cui non è minore
    }
}

void InsertionSortPartialReversed(Item A[],int N,int l,int r){
        int i, j;
    Item x;

    if(l<0 || l>r || r>=N){
        fprintf(stderr,"Indici errati\n");
        exit(-1);
    }
    for(i = l+1; i <= r; i++) {
        x = A[i];                               //x=elemento da ordinare
        j = i - 1;                              //confronta con i valori da quello precedente al primo del vettore e man mano se c'e bisogno trasla
        while (j >= l && ITEMgt(x, A[j])) {     //finchè x è maggiore dell'elemento precedente
            A[j+1] = A[j];                      //se x è maggiore di quello che lo precede trasla quest'ultimo avanti di uno
            j--;
        }
        A[j+1] = x;                             //piazza x dopo quello di cui non è maggiore
    }
}

void BubbleSort(Item A[], int N) {
  int i, j, l=0, r=N-1;
  Item temp;
  int cicli_esterni=0, cicli_interni=0, scambi=0;

  for(i = l; i < r; i++) {
    cicli_esterni++;
    for (j = l; j <  r - i + l; j++) {
        cicli_interni++;
	  if (ITEMgt(A[j], A[j+1])) {
	      scambi++;
        temp = A[j];
        A[j] = A[j+1];
		A[j+1] = temp;
      }
    }
  }

  printf("Cicli esterni: %d, Cicli interni: %d, Scambi: %d\n",cicli_esterni,cicli_interni,scambi);
  return;
}

void OptBubbleSort(Item A[], int N) {
  int i, j, l=0, r=N-1, flag;
  Item temp;
  int cicli_esterni=0, cicli_interni=0, scambi=0;

  flag = 1;
  for(i = l; i < r && flag == 1; i++) {
    flag = 0;
    cicli_esterni++;
    for (j = l; j < r - i + l; j++){
        cicli_interni++;
      if (ITEMgt(A[j],A[j+1])) {
        scambi++;
        flag = 1;
        temp = A[j];
        A[j] = A[j+1];
		A[j+1] = temp;
      }
    }
  }

  printf("Cicli esterni: %d, Cicli interni: %d, Scambi: %d\n",cicli_esterni,cicli_interni,scambi);
  return;
}

void SelectionSort(Item A[], int N) {
  int i, j, l=0, r=N-1, min;
  Item temp;
  int cicli_esterni=0, cicli_interni=0, scambi=0;

  for(i = l; i < r; i++) {
    cicli_esterni++;
    min = i;
	for (j = i + 1; j <= r; j++){
        cicli_interni++;
      if (ITEMlt(A[j],A[min]))
        min = j;
	}
	if (min != i) {
        scambi++;
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
	}
  }

  printf("Cicli esterni: %d, Cicli interni: %d, Scambi: %d\n",cicli_esterni,cicli_interni,scambi);
  return;
}

void ShellSort(Item A[], int N) {
  int i, j, h=1, l=0, r= N-1;
  Item tmp;
  int cicli_esterni_totali=0, cicli_esterni=0, cicli_interni=0, scambi=0;

  while (h < N/3)
    h = 3*h+1;
  while(h >= 1) {
    cicli_esterni=0;
    for (i = l + h; i <= r; i++) {
        cicli_esterni++;
      j = i;
      tmp = A[i];
      while(j >= l + h  && ITEMlt(tmp,  A[j-h])) {
        cicli_interni++;
        scambi++;
        A[j] = A[j-h];
        j -=h;
      }
      A[j] = tmp;
    }
    /*printf("h = %d, h-sorted array is: \n", h);
    for (i = 0; i <(r-l+1); i++)
      ITEMshow(A[i]);
    printf("\n");
    */
    h = h/3;
    printf("Cicli esterni parziali: %d\n",cicli_esterni);
    cicli_esterni_totali+=cicli_esterni;
  }

  printf("Cicli esterni totali: %d, Cicli interni: %d, Assegnazioni (non si contano quelle in cui si riassegna lo stesso valore): %d\n",cicli_esterni_totali,cicli_interni,scambi);
}

/*void CountingSort(Item A[], int l, int r int k) {
    ... wrapper
}

void CountingSortReal(Item A[], Item B[], int C[], int N, int k) {
  int i, l=0, r=N-1;

  for (i = 0; i < k; i++)
    C[i] = 0;

  for (i = l; i <= r; i++)
    C[A[i]]++;

  for (i = 1; i < k; i++)
    C[i] += C[i-1];

  for (i = r; i >= l; i--) {
    B[C[A[i]]-1] = A[i];
    C[A[i]]--;
  }

  for (i = l; i <= r; i++)
    A[i] = B[i];
}
*/
