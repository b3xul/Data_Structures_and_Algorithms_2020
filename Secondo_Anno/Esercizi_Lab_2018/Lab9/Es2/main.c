#include <stdio.h>
#include <stdlib.h>

#define N 4     //Numero di tipi di gemme

//int disp_rip(int pos, char* val, int* sol, int* n_gemme, int n, int k, int prec);
int controlla(int* sol, int* n_gemme, int k);
int**** alloca4d(int z, int r, int t, int s);
int calcolo(int* n_gemme);
int fZ(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s);
int fR(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s);
int fT(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s);
int fS(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s);
int max(int a,int b);

int main()
{
    FILE* fp=fopen("e2_test_set.txt","r");
    if(fp==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }
    int i,j,k,n_sets,max_lun;
    char gemme[N]={'Z','R','T','S'};
    int n_gemme[N];
    int* sol;


    fscanf(fp,"%d",&n_sets);

    for(i=0;i<n_sets;i++){
        printf("Test set #%d: ", i+1);
        max_lun=0;
        /*Inizializzo lunghezza massima della collana e numero di gemme massime disponibili*/
        for(j=0;j<N;j++){
            fscanf(fp,"%d",&n_gemme[j]);
            printf("%d ",n_gemme[j]);
            max_lun+=n_gemme[j];
        }
        printf("\n");

        printf("Ipotizzo la catena sara' lunga %d\n",calcolo(n_gemme));

//        for(k=max_lun;k>=1;k--){
//            //K= lunghezza della collana che vado a guardare E numero massimo di ripetizioni per OGNI elemento di gemme
//            //Nella condizione di terminazione dovrò controllare che i vincoli non eccedano le disponibilità di ogni gemma
//            //ma non che la cardinalità sia massima perchè la prima che trovo è sicuramente quella a cardinalità massima per cui posso già interrompere la ricerca
//            printf("k=%d\n",k);
//            sol=(int*)malloc(k*sizeof(int));
//            if(sol==NULL){
//                fprintf(stderr,"Errore nell'allocazione\n");
//                exit(-2);
//            }
//
//            if(disp_rip(0,gemme,sol,n_gemme,N,k,-1))
//                break;
//        }

    }



    return 0;
}

int**** alloca4d(int z, int r, int t, int s){
    int i,j,m,n;

    int**** X=(int****)malloc((z+1)*sizeof(int));   //1+ perchè accetto come indici X[z] se mancanp ancora z gemme

    for(i=0;i<=z;i++){
        X[i]=(int***)malloc((r+1)*sizeof(int));

        for(j=0;j<=r;j++){
            X[i][j]=(int**)malloc((t+1)*sizeof(int));

            for(m=0;m<=t;m++){
                X[i][j][m]=(int*)malloc((s+1)*sizeof(int));

                for(n=0;n<=s;n++){
                    X[i][j][m][n]=-1;
                }
            }
        }
    }
    return X;
}

int calcolo(int* n_gemme){
    int z=n_gemme[0],r=n_gemme[1],t=n_gemme[2],s=n_gemme[3];
    int**** Z=alloca4d(z,r,t,s);
    int**** R=alloca4d(z,r,t,s);
    int**** T=alloca4d(z,r,t,s);
    int**** S=alloca4d(z,r,t,s);

    return max( fZ(Z,R,T,S,z,r,t,s), max(fR(Z,R,T,S,z,r,t,s), max(fT(Z,R,T,S,z,r,t,s), fS(Z,R,T,S,z,r,t,s))));  //Massimo tra tutte le dimensioni possibili di catene inizianti con Z,R,T,S
}

int fZ(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s){
    if(z==0)    //Finiti gli zaffiri, lunghezza massima catena iniziante con zaffiro=0
        return 0;
    if(Z[z][r][t][s]!=-1)   //Se ho già calcolato una catena iniziante con Z avente z zaffiri, r rubini... uso il risultato già ottenuto
        return Z[z][r][t][s];

    //Scelgo che pietra mettere dopo lo zaffiro in base alla lunghezza delle catene che riuscirò a creare con le pietre cge mi rimangono
    //Ritorno la dimensione della catena più lunga a cui aggiungo lo zaffiro che prendo
    return Z[z][r][t][s]=1+max(fZ(Z,R,T,S,z-1,r,t,s),fR(Z,R,T,S,z-1,r,t,s));
}

int fR(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s){
    if(r==0)
        return 0;
    if(R[z][r][t][s]!=-1)
        return R[z][r][t][s];
    return R[z][r][t][s]=1+max(fS(Z,R,T,S,z,r-1,t,s),fT(Z,R,T,S,z,r-1,t,s));
}

int fT(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s){
    if(t==0)
        return 0;
    if(T[z][r][t][s]!=-1)
        return T[z][r][t][s];
    return T[z][r][t][s]=1+max(fZ(Z,R,T,S,z,r,t-1,s),fR(Z,R,T,S,z,r,t-1,s));;
}

int fS(int**** Z, int**** R, int**** T, int**** S, int z, int r, int t, int s){
    if(s==0)
        return 0;
    if(S[z][r][t][s]!=-1)
        return S[z][r][t][s];
    return S[z][r][t][s]=1+max(fS(Z,R,T,S,z,r,t,s-1),fT(Z,R,T,S,z,r,t,s-1));
}

int max(int a,int b){
    return (a>b)?a:b;
}


//int disp_rip(int pos, char* val, int* sol, int* n_gemme, int n, int k, int prec){
//    int i;
//
//    /*Condizione di terminazione*/
//    if(pos>=k){
//        for(i=0;i<k;i++){
//            printf("%c",val[sol[i]]);
//        }
//        printf("\nE' una soluzione valida e di lunghezza massima=%d\n",k);
//        return 1;
//    }
//
//    /*Ricorsione*/
//    for(i=0;i<n;i++){
//        if(n_gemme[i]>0){   //Pruning sul numero di gemme permette di arrivare a k=18
//            if(prec!=-1){
//                if( ((sol[prec]==0) || (sol[prec]==2)) && (i!=0) && (i!=1) )        //Se non rispetta condizioni non ricorre ma passa al ciclo successivo
//                    continue;
//                if( ((sol[prec]==1) || (sol[prec]==3)) && (i!=2) && (i!=3) )
//                    continue;
//            }
//            n_gemme[i]--;
//            sol[pos]=i;     //Sol conterrà gli indici di val da stampare
//            if(disp_rip_memo(pos+1,val,sol,n_gemme,n,k,pos))
//                return 1;
//            n_gemme[i]++;
//        }
//    }
//    return 0;
//}
