#include <stdio.h>
#include <stdlib.h>
#define SIZE 100 
int menu(int *M,int *N);
void newGame(int tetris[][SIZE],int M ,int N,int *score);
void printTetris(int tetris[][SIZE],int M ,int N,int score, int hscore, int piece[][3]);
int getMove(int tetris[][SIZE],int *M ,int *N,int score, int hscore, int piece[][3],int pieces[][3][3]);
void rotatePiece(int piece[][3]);
int putPiece(int tetris[][SIZE],int M ,int N, int piece[][3]);
void randomPiece(int tmp,int piece[][3],int pieces[][3][3]);
void check(int tetris[][SIZE],int M,int N,int *score);
int checkGame(int tetris[][SIZE],int N);
int menu(int *M,int *N){
	int choose;
	//Print menu
	printf("MENU\n1-Oyundaki satir sayisi=%d\n2-Oyundaki sutun sayisi=%d\nOyun icin 0 girin.\n",*M,*N);
	scanf("%d",&choose);
	switch(choose){
		case 0:
			return 0;
		case 1:
			printf("Yeni deger giriniz:");
			scanf("%d",M);
			break;
		case 2:
			printf("Yeni deger giriniz:");
			scanf("%d",N);
			break;
		default:
			system("cls");
			printf("Hatali girdi!!\n");
			choose=404;
			break;
	}
	if(choose!=404){
		system("cls");
	}
	return 1;
}
void newGame(int tetris[][SIZE],int M ,int N,int *score){
	int i,j;
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			tetris[i][j]=0;
		}
	}
	for(j=0;j<N;j++){
			tetris[M][j]=1;
	}
	score=0;
}
void printTetris(int tetris[][SIZE],int M ,int N,int score, int hscore, int piece[][3]){
	int i,j;
	system("cls");
	printf("\nScore:%d HighScore:%d\n",score,hscore);
	for(i=0;i<=2*N;i++){
		printf("_");
	}
	printf("\n");
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf("|");
                if(tetris[i][j]==1){
                    printf("1");
                }
                else{
                	printf(" ");
				}
		}
		printf("|");
		if(i<3){
			printf("\t\t\t");
			for(j=0;j<3;j++){
			printf("|");
                if(piece[i][j]==1){
                    printf("1");
                }
                else{
                	printf(" ");
				}
			}
			printf("|");
		}
		if(i==4){
			printf("\t\t\t Piece:");
		}
		printf("\n");
	}
	for(i=0;i<=2*N;i++){
		printf("/");
	}
}
int getMove(int tetris[][SIZE],int *M ,int *N,int score, int hscore, int piece[][3],int pieces[][3][3]){
	char move;
	if(checkGame(tetris,*N)){
		return 0;
	}
	printf("\nHamle oynamak icin P\nDondurme R\nYeni oyun N\nMenu M (Menuye gitmek oyunu sifirlar)\nCikis E\n");
	scanf(" %c",&move);
	switch(move){
		case 'M':
		case 'm':
			while(menu(M,N));
			newGame(tetris,*M,*N,&score);
			return 1;
		case 'P':
		case 'p':
			if(putPiece(tetris,*M,*N,piece)){
				randomPiece(rand()%6,piece,pieces);
				if(rand()%2){
					rotatePiece(piece);
				}
			}
			return 1;
		case 'E':
		case 'e':
			return 0;
		case 'N':
		case 'n': 
			newGame(tetris,*M,*N,&score);
			break;
		case 'R':
		case 'r':
			rotatePiece(piece);
			return 1;
		default:
			printf("\nHatali girdi!!");
			return 1;
	}
}
void rotatePiece(int piece[][3]){
	int i,j,temp,found=0,k=0;
	int tmp[3][3]={0,0,0,0,0,0,0,0,0};
	for(j=2;j>=0&&(!found);j--){
		temp=0;
		for(i=0;i<3;i++){
			temp+=piece[i][j];
		}
		if(temp!=0){
			found=1;
			j++;
		}
	}
	for(;j>=0;j--){
		temp=0;
		for(i=0;i<3;i++){
			tmp[k][i]=piece[i][j];
		}
		k++;
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			piece[i][j]=tmp[i][j];
		}
	}
}
int putPiece(int tetris[][SIZE],int M ,int N, int piece[][3]){
	int found=0,i,j,lenght,temp,x,y,full=0;
	for(j=2;j>=0&&(!found);j--){
		temp=0;
		for(i=0;i<3;i++){
			temp+=piece[i][j];
		}
		if(temp!=0){
			found=1;
			lenght=j+1;
		}
	}
	printf("Parcanin koyulacagi koordinatlari giriniz:(Orn:0 3)\n");
	scanf("%d %d",&x,&y);
	if(y+lenght-1>=N || x>M){
		printf("Sectiginiz koordinat oyunun duvarini asiyor!!");
		getch();
		return 0;
	}
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(piece[i][j]*tetris[x+i][y+j]){
				full=1;
			}
		}
	}
	if(full==1){
		printf("Sectiginiz koordinat dolu!!");
		getch();
		return 0;
	}
	while(full==0 && x<M){
		x++;
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(piece[i][j]*tetris[x+i][y+j]){
					full=1;
				}
			}
		}
	}
	x--;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			tetris[x+i][y+j]+=piece[i][j];
		}
	}
	return 1;
}
void randomPiece(int tmp,int piece[][3],int pieces[][3][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			piece[i][j]=pieces[tmp][i][j];
		}
	}
}
void check(int tetris[][SIZE],int M,int N,int *score){
	int i,j,k,t,tmp;
	for(i=M-1;i>=0;i--){
		tmp=1;
		for(j=0;j<N;j++){
			tmp*=tetris[i][j];
		}
		if(tmp==1){
			*score+=N;
			for(k=i;k>=1;k--){
				for(t=0;t<N;t++){
					tetris[k][t]=tetris[k-1][t];
				}
			}
			for(t=0;t<N;t++){
					tetris[0][t]=0;
			}
			i++;
		}
	}
}
int checkGame(int tetris[][SIZE],int N){
	int i,temp=0;
	for(i=0;i<N;i++){
		temp+=tetris[0][i];
	}
	if(temp>0){
		return 1;
	}
	return 0;
}
int main() {
	int M=20,N=10,tetris[SIZE][SIZE],score=0,hscore=0,tmp,i,j;
	int piece[3][3];
	int pieces[6][3][3]={1,1,1,
	                     0,0,0,
						 0,0,0,
						 1,1,0,
						 1,1,0,
						 0,0,0,
						 1,0,0,
						 0,0,0,
						 0,0,0,
						 1,1,0,
						 0,0,0,
						 0,0,0,
						 1,0,0,
						 1,0,0,
						 1,1,0,
						 0,1,1,
						 1,1,0,
						 0,0,0};
	while(menu(&M,&N));//Menu uzerinden degisiklikler.
	system("cls");
	
	newGame(tetris,M,N,&score);
	
	srand(time(NULL));
	randomPiece(rand()%6,piece,pieces);
	
	printTetris(tetris,M,N,score,hscore,piece);
	
	while(getMove(tetris,&M,&N,score,hscore,piece,pieces)){
		check(tetris,M,N,&score);
		if(score>hscore){
			hscore=score;
		}
		printTetris(tetris,M,N,score,hscore,piece);
	}
	printf("GAME OVER");
}
