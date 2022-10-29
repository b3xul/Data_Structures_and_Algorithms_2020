#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

int main()
{

int wq=2/3;
printf("%d",wq);
int w;
float q[5]={0};
for(w=0;w<5;w++){
    printf("%f ",q[w]);
}
int prova;
	prova=(int)(4.7);
	printf("%d",prova);
FILE *f1;
    f1=fopen("robe.txt","r");

    FILE *fprec;
    fprec=f1;

    char roba[30];
    fscanf(fprec,"%s",roba);
    printf("%s",roba);
    char str[N][29];
    int p;

    scanf("%d",&p); //non si puo' fare,serve stringa ausiliaria!//
    scanf("%s",str[p]);
    printf("%s",str[p]);

    int vet[N]={0};
    unsigned int i;
    for(i=0;i<N;i++)
    printf("%d",vet[i]);

    char c=7;
    printf("%c",c);
    char info [10][60];
    scanf("%s",info[0]);

     char str1[20];
    char str2[20];
    int comp;

    scanf("%s%s",str1,str2);
    comp=strcmp(str1,str2);
    printf("%d",comp); //negativo se 1 viene prima di 2, positivo se 2 viene prima di 1//


    int v[N], value;
    unsigned int n_elements; /* The current number of elements stored in v */


    for (n_elements=0; n_elements<N; n_elements++)
    {

        printf("Insert a value: ");
        scanf("%d", &value);

        for (i=n_elements; i>0; i--)   /* From the last to the second element of the vector */
        {
            if ( value<v[i-1] ) /* If the new value is smaller than the element i-1 of the vector */
            {
                v[i] = v[i-1]; /* Scale the element i-1 of one position */
            }
            else
            {
                break; /* Exit the cycle: the correct position (i) of the new value has been found */
            }
        }
        v[i] = value; /* Insert the new value in the correct position */

    }

    /* Print the vector */
    printf("VEC:");
    for (i=0; i<N; i++)
    {
        printf(" %d", v[i]);
    }
    printf("\n");

    return 0;
}

