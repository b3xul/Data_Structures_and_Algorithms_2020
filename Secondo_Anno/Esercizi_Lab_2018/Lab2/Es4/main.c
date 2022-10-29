#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "Sorting_compare.h"

#define DBG 0

void stampaVettore(int A[], int N);

int main()
{

    FILE* fp;
    int i,j,n,S;
    Item* a;


    printf("INSERTION_SORT:\n");
    fp=fopen("sort.txt","r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&S);

    for(i=0;i<S;i++){
        /*Acquisisco vettore*/
        fscanf(fp,"%d",&n);
        a=(Item*)malloc(n*sizeof(Item));
#if DBG
        printf("Sequenza: ");
#endif // DBG
        for(j=0;j<n;j++){
            fscanf(fp,"%d",&a[j]);
#if DBG
            printf("%d ",a[j]);
#endif // DBG
        }
        printf("\n");
        /*Ordino vettore*/
        InsertionSort(a,n);
        //stampaVettore(a,n);
        free(a);
    }
    fclose(fp);
printf("*************************************************\n");
    printf("SELECTIONSORT:\n");
    fp=fopen("sort.txt","r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&S);
    for(i=0;i<S;i++){
        /*Acquisisco vettore*/
        fscanf(fp,"%d",&n);
        a=(Item*)malloc(n*sizeof(Item));
#if DBG
        printf("Sequenza: ");
#endif // DBG
        for(j=0;j<n;j++){
            fscanf(fp,"%d",&a[j]);
#if DBG
            printf("%d ",a[j]);
#endif // DBG
        }
        printf("\n");
        /*Ordino vettore*/
        SelectionSort(a,n);
        //stampaVettore(a,n);
        free(a);
    }
    fclose(fp);

printf("*************************************************\n");

    printf("BUBBLESORT:\n");
    fp=fopen("sort.txt","r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&S);
    for(i=0;i<S;i++){
        /*Acquisisco vettore*/
        fscanf(fp,"%d",&n);
        a=(Item*)malloc(n*sizeof(Item));
#if DBG
        printf("Sequenza: ");
#endif // DBG
        for(j=0;j<n;j++){
            fscanf(fp,"%d",&a[j]);
#if DBG
            printf("%d ",a[j]);
#endif // DBG
        }
        printf("\n");
        /*Ordino vettore*/
        BubbleSort(a,n);
        //stampaVettore(a,n);
        free(a);
    }
    fclose(fp);
printf("*************************************************\n");

    printf("OPTBUBBLESORT:\n");
    fp=fopen("sort.txt","r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&S);
    for(i=0;i<S;i++){
        /*Acquisisco vettore*/
        fscanf(fp,"%d",&n);
        a=(Item*)malloc(n*sizeof(Item));
#if DBG
        printf("Sequenza: ");
#endif // DBG
        for(j=0;j<n;j++){
            fscanf(fp,"%d",&a[j]);
#if DBG
            printf("%d ",a[j]);
#endif // DBG
        }
        /*Ordino vettore*/
        OptBubbleSort(a,n);
        //stampaVettore(a,n);
        free(a);
    }

    fclose(fp);
printf("*************************************************\n");

    printf("SHELLSORT:\n");
    fp=fopen("sort.txt","r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&S);

    for(i=0;i<S;i++){
        /*Acquisisco vettore*/
        fscanf(fp,"%d",&n);
        a=(Item*)malloc(n*sizeof(Item));
#if DBG
        printf("Sequenza: ");
#endif // DBG
        for(j=0;j<n;j++){
            fscanf(fp,"%d",&a[j]);
#if DBG
            printf("%d ",a[j]);
#endif // DBG
        }
        printf("\n");
        /*Ordino vettore*/
        ShellSort(a,n);
        //stampaVettore(a,n);
        free(a);
    }
    fclose(fp);
printf("*************************************************\n");

    return 0;
}

void stampaVettore(int A[], int N) {
  int i;
  for(i=0;i<N;i++) printf("%d ", A[i]);
  printf("\n");
}
