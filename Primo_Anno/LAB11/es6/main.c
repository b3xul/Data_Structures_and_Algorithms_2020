#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char Cognome_Nome[40+1];
    char Matricola[6+1];
    char Voto[2+1];
}dati;

int main()
{
    dati stud[10000];
    char choice='a';
    char info[10][60];
    int i=0,j=0,k,length=0;
    FILE *fin;
    fin=fopen("Backup.txt","r");
    FILE *fout;
    fout=fopen("Data.txt","w");

    while(choice!=EOF){
    choice=getchar();
        if(choice!='\n'){
            switch(choice){
                case 'I':   while(getchar()!='\n'){
                                scanf("%s",info[i]);
                                length++;
                                i++;
                            }
                            if(length>2){strcpy(stud[j].Voto,info[length-1]);
                            strcpy(stud[j].Matricola,info[length-2]);
                            strcpy(stud[j].Cognome_Nome,info[0]);
                            }
                            for(i=1;i<length-2;i++){
                                strcat(stud[j].Cognome_Nome," ");
                                strcat(stud[j].Cognome_Nome,info[i]);
                            }
                            j++;
                            i=0;
                            length=0;
                    break;

                case 'C':   k=0;
                            while(getchar()!='\n'){
                                scanf("%s",info[k]);
                                k++;
                            }
                            if(k==1){ //matricola//
                                for(i=0;i<j;i++){
                                    if((strcmp(stud[i].Matricola,info[0]))==0){
                                        strcpy(stud[i].Cognome_Nome,"Rimosso");
                                    }
                                }
                            }
                            if(k>1){ //cognome_nome//
                                for(i=1;i<k;i++){
                                    strcat(info[0]," ");
                                    strcat(info[0],info[i]);
                                }
                                for(i=0;i<j;i++){
                                    if(strcmp(stud[i].Cognome_Nome,info[0])==0){
                                        strcpy(stud[i].Cognome_Nome,"Rimosso");
                                    }
                                }
                            }
                            i=0;
                    break;

                case 'V':   k=0;
                            while(getchar()!='\n'){
                                scanf("%s",info[k]);
                                k++;
                            }
                            if(k==1){ //matricola//
                                for(i=0;i<j;i++){
                                    if((strcmp(stud[i].Matricola,info[0]))==0){
                                        printf("%s %s %s\n",stud[i].Cognome_Nome,stud[i].Matricola,stud[i].Voto);
                                    }
                                }
                            }
                            if(k>1){ //cognome_nome//
                                for(i=1;i<k;i++){
                                    strcat(info[0]," ");
                                    strcat(info[0],info[i]);
                                }
                                for(i=0;i<j;i++){
                                    if(strcmp(stud[i].Cognome_Nome,info[0])==0){
                                        printf("%s %s %s\n",stud[i].Cognome_Nome,stud[i].Matricola,stud[i].Voto);
                                    }
                                }
                            }
                            i=0;
                    break;

                case 'P':   for(i=0;i<j;i++){
                                if(strcmp(stud[i].Cognome_Nome,"Rimosso")!=0)
                                    printf("%s %s %s\n",stud[i].Cognome_Nome,stud[i].Matricola,stud[i].Voto);
                            }
                    break;

                case 'L':   if(fin==NULL){
                                fprintf(stderr,"Errore nell'apertura del file in lettura");
                                return -1;
                            }
                            i=0;
                            while(fscanf(fin,"%s",info[i])!=EOF&&fgetc(fin)!='\n'){

                                    length++;
                                    i++;

                                if(length>2){strcpy(stud[j].Voto,info[length-1]);
                                strcpy(stud[j].Matricola,info[length-2]);
                                strcpy(stud[j].Cognome_Nome,info[0]);
                                }
                                for(i=1;i<length-2;i++){
                                    strcat(stud[j].Cognome_Nome," ");
                                    strcat(stud[j].Cognome_Nome,info[i]);
                                }
                            }
                                j++;
                                i=0;
                                length=0;

                    break;

                case 'S':
                            if(fout==NULL){
                                fprintf(stderr,"Errore nell'apertura del file in scrittura");
                                return -2;
                            }
                            for(i=0;i<j;i++){
                                if(strcmp(stud[i].Cognome_Nome,"Rimosso")!=0)
                                    fprintf(fout,"%s %s %s\n",stud[i].Cognome_Nome,stud[i].Matricola,stud[i].Voto);
                            }

                            fclose(fout);
                    break;

                default:    printf("Scelta non disponibile.");
            }
        }
    }
    return 0;
}
