#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define N 4     //Numero di tipi di gemme

int perm_rip(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int prec);

int main()
{
    FILE* fp=fopen("easy_test_set.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }
    int i,j,k,v,n_sets,max_lun;
    char gemme[N]={'Z','R','T','S'};
    int n_gemme[N];
    char* val;
    char* sol;

    fscanf(fp,"%d",&n_sets);

    for(i=0;i<n_sets;i++){
        printf("Test set #%d: ", i+1);
        max_lun=0;
        v=0;

        /*Inizializzo lunghezza massima della collana e numero di gemme massime disponibili*/
        for(j=0;j<N;j++){
            fscanf(fp,"%d",&n_gemme[j]);
            printf("%d ",n_gemme[j]);
            max_lun+=n_gemme[j];
        }

        /*Inizializzo stringa di valori*/
        val =(char*) malloc(max_lun+1 * sizeof(char));
        if(val==NULL){
            fprintf(stderr,"Errore nell'allocazione\n");
            exit(-2);
        }

        for(k=0;k<N;k++){
            for(j=0;j<n_gemme[k];j++)
                val[v++]=gemme[k];
        }
        val[v++]='\0';
        printf("\n%s\n",val);

        for(k=max_lun;k>=1;k--){
            printf("k=%d\n",k);
            sol = (char*) malloc(k+1 * sizeof(char));
            if(sol==NULL){
                fprintf(stderr,"Errore nell'allocazione\n");
                exit(-2);
            }

            if(perm_rip(0, gemme, sol, n_gemme, max_lun, N, -1))
                break;

            free(sol);
        }
        free(val);
    }

    return 0;
}

int perm_rip(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int prec) {
/*Ha senso solo per trovare combinazioni con k=max_lun, per trovare quelle minori bisognerebbe provare a togliere ogni lettera una per volta e lì la complessità esploderebbe!*/
  int i;
  if (pos >= n) {
    for (i=0; i<n; i++)
      printf("%c", sol[i]);
    printf("\n");
    return 1;
  }

  for (i=0; i<n_dist; i++) {
    if (mark[i] > 0) {
        if(prec!=-1){
                if( ((sol[prec]=='Z') || (sol[prec]=='T')) && (i!=0) && (i!=1) )        //Se non rispetta condizioni non ricorre ma passa al ciclo successivo
                    continue;
                if( ((sol[prec]=='R') || (sol[prec]=='S')) && (i!=2) && (i!=3) )
                    continue;
        }
        mark[i]--;
        sol[pos] = dist_val[i];
        if(perm_rip(pos+1, dist_val, sol, mark, n, n_dist, pos))
            return 1;
        mark[i]++;
    }
  }

  return 0;
}
