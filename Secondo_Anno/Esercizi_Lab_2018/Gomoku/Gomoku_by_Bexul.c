/*
 ============================================================================
 Name        : Gomoku_by_Bexul.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
/*Riprendere una partita a Gomoku e portarla a termine (vince il primo dei 2 giocatori che riesce a mettere in fila 5 pedine del suo colore in orizzontale, verticale o diagonale)
 *1. Ricevo file da linea di comando, leggo e salvo il suo contenuto (matrice 19x19) (.=casella libera, B=pedina bianca, N=pedina nera) OK
 *2. Stabilisco chi debba fare la prossima mossa (conteggio pedine)
 *3. Richiedo mossa da tastiera (CONTROLLO: coordinate 1-19 e casella libera->mossa valida)
 *4. Controllo vittoria: intorno alla pedina inserita ci sono 4 altre pedine?
 *5. Controllo pareggio: conteggio pedine=19*19?
 */
#include <stdio.h>
#include <stdlib.h>

#define DBG 1

#define SIZE 19

void stampa(char map[][SIZE]);
char next_turn(char turn,char map[][SIZE],int* n_bianche,int* n_nere);
char check_move(char map[][SIZE],int r,int c);
int check_win(char map[][SIZE],int r,int c,char turn);

int main(int argc,char* argv[]) {

	/*Apertura file*/
	if(argc!=2){
		fprintf(stderr,"Errore nel numero degli argomenti!\n");
		exit(-1);
	}

	FILE* fi;
	if((fi=fopen(argv[1],"r"))==NULL){
		fprintf(stderr,"Errore nell'apertura del file!\n");
		exit(-2);
	}

	/*Salvo matrice*/
	char map[SIZE][SIZE];
	int i,j;
	int n_bianche=0,n_nere=0;

	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			fscanf(fi,"%c",&map[i][j]);
			if(map[i][j]=='B')
				n_bianche++;
			else if(map[i][j]=='N')
				n_nere++;
		}
		fgetc(fi);		//discard \n
	}

	/*Stampo matrice*/
	stampa(map);

	if(DBG){
		printf("n_bianche=%d\n",n_bianche);
		printf("n_nere=%d\n",n_nere);
	}

	int fine_partita=0;
	char turn='N';
	if(n_nere>n_bianche)
		turn='B';

	while(!fine_partita){
		turn=next_turn(turn,map,&n_bianche,&n_nere);
		if(DBG){
			printf("n_bianche=%d\n",n_bianche);
			printf("n_nere=%d\n",n_nere);
		}
		if(n_bianche+n_nere==361)	//19*19
			fine_partita=1;
	}

	printf("La partita si è conclusa con un pareggio!\n");

	return EXIT_SUCCESS;
}

void stampa(char map[][SIZE]){	//Prima dimensione omissibile: il compilatore lo considera un

	int i,j;

	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			printf("%c",map[i][j]);
		}
		printf("\n");
	}

	return;
}

char next_turn(char turn, char map[][SIZE], int* n_bianche, int* n_nere){
	int r,c;
	char res='i',ret;

	while(res!='o'){
		printf("Giocatore %c inserisca la sua mossa (caselle 1-19): ",turn);
		scanf("%d%d",&r,&c);
		//trasformo in indici
		r-=1;
		c-=1;

		res=check_move(map,r,c);
		if(res=='i')
			printf("Mossa non ammessa! Fuori dai bordi!\n");
		else if(res=='B' || res=='N')
			printf("Mossa non ammessa! Casella occupata!\n");
		else{	//mossa ammessa
			map[r][c]=turn;
			if(turn=='N'){
				(*n_nere)++;
				ret='B';
			}
			else{
				(*n_bianche)++;
				ret='N';
			}
		}
	}

	stampa(map);
	check_win(map,r,c,turn);

	return ret;
}

char check_move(char map[][SIZE],int r,int c){
	if( r>=SIZE || r<0 || c>=SIZE || c<0)
		return 'i';		//illegal
	if( map[r][c]=='B')
		return 'B';
	if( map[r][c]=='N')
		return 'N';
	return 'o';			//ok
}

int check_win(char map[][SIZE],int r,int c,char turn){
	int k,i,j,count,direction1,direction2;
	char res;

	int moves[4][2]={	{1,0},	//N  -S	 |
						{1,1},	//NE -SO /
						{0,1},	//E	 -O  -
						{0,-1}	//SE -NO \        LOL(necessario per chiudere il commento)
	};

	direction1=1;
	direction2=0;
	for(k=0;k<4;k++){
		count=1;	//map[r][c]

		i=r;
		j=c;
		while(direction1){
			//Example run: r=1, c=1, i=1, j=1, k=1, count=1
			i+=moves[k][0];
			j+=moves[k][1];
			//i=2, j=1		//SUD
			res=check_move(map,i,j);

			if(res==turn)
				count++;
				//count=2,3,4
			else{
				direction1=0;
				direction2=1;
			}
			if(count==5){
				printf("Vince il giocatore %c!\n",turn);
				exit(1);
			}
		}

		i=r;
		j=c;
		while(direction2){
			//Example run: r=1, c=1, i=1, j=1, k=1, count=4
			i-=moves[k][0];
			j-=moves[k][1];
			//i=0, j=1		//NORD
			res=check_move(map,i,j);

			if(res==turn)
				count++;
				//count=2,3,4,5
			else{
				direction1=1;
				direction2=0;
			}
			if(count==5){
				printf("Vince il giocatore %c!\n",turn);
				exit(1);
			}
		}
	}

	return 0;
}

