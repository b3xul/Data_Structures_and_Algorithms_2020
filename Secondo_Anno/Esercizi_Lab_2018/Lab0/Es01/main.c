#include <stdio.h>
#include <stdlib.h>

#define MAXN 30
#define RUN 0

int append(int* res,int* buffer,int k);

int main(int argc,char *argv[]) {
	int v[MAXN]={1,2,0,3,4,5,0,1,0,6,7,8};
	int buffer[MAXN+1];
	int res[MAXN+1];
	int i,j,k,q,n,dim_max;

	//i:indice di v
	//j:indice di buffer e dimensione attuale
	//k:indice di res
	//n:dimensione di v
	//dim_max:dimensione massima del sottovettore
	//q:indice per copiare buffer

	n=12;
	//Ottengo vettore
#if RUN
	printf("Inserire numero di elementi effettivi del vettore: ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",&v[i]);
#endif

	//scorro vettore ottenuto
	j=k=q=dim_max=0;

	/*Sto facendo buffer che è la copia delle sequenze di v che costituiscono la soluzione, spreco memoria!
	  Più efficiente vettore di interi di dimensione MAXN/2 rappresentanti gli indici di v di inizio delle sottosequenze con dimensione dim_max
	  E una variabile conteggio della dimensione del vettore di indici, da resettare in caso di j>dim_max
	  */
	for(i=0;i<n;i++){
		if(v[i]!=0)
			buffer[j++]=v[i];

		if( v[i]==0 || i==n-1 ){
			if(j==dim_max){
				buffer[j]=0;
				k=append(res,buffer,k);
			}
			else if(j>dim_max){
				buffer[j]=0;
				dim_max=j;
				k=append(res,buffer,0);
			}
			//if(j<dim_max) solo j=0
			//resetto buffer
			j=0;
		}
	}

	//Stampa risultato
	printf("I sottovettori di dimensione maggiore sono:\n");
	for(i=0;i<k;i++){
		if(res[i]==0)
			printf("\n");
		else
			printf("%d ",res[i]);
	}
	return EXIT_SUCCESS;
}

int append(int* res,int* buffer,int k){
	int i=0;

	while(buffer[i]!=0)
		res[k++]=buffer[i++];

	res[k++]=0;

	return k;
}
