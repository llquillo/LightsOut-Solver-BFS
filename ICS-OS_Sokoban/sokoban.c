#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define up_key 'w'
#define down_key 's'
#define right_key 'd'
#define left_key 'a'
#define reset 'r'
#define quit 'q'
#define enter '\n'
#define one '1'
#define two '2'
#define three 3
#define four 4
#define five 5
#define zero 0

#define YELLOW 54
#define BLUE 9
#define BLACK 70
#define ORANGE 38
#define GREEN 18
#define GRAY 56
#define MAROON 4
#define WHITE 63
#define BROWN 20
#define RED 36

#define size 8

int storedMap[size][size];
char globalMap[size][size]; //current state of map
char playMap[size][size]; //edited map
int playerX=0;
int playerY=0;
int best1A = 30;
int best1B = 17;
int best1C = 18;
int best2A = 31;
int best2B = 33;
int best2C = 34;
int best3A = 35;
int best3B = 37;
int best3C = 37;
int best4A = 37;
int best4B = 40;
int best4C = 47;
int best5A = 47;
int best5B = 30;
int best5C = 62;
int moves, bestMove=0, level=1, stage=0;
char oneA[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', 'G', 'B', '_', '_', '_', 'G', '+'},
			  {'+', '_', '_', '+', '_', '_', '_', '+'},
			  {'+', '+', '+', '+', '+', '_', '+', '+'},
			  {'+', '+', '+', '+', '_', 'B', '+', '+'},
			  {'+', 'G', 'B', 'P', '_', '_', '+', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char oneB[8][8]  = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', 'P', '_', '+', '+', '+', '+'},
			  {'+', '+', '_', 'G', '+', '+', '+', '+'},
			  {'+', '+', '+', '_', '+', '+', '+', '+'},
			  {'+', 'G', '_', 'B', '+', '+', '+', '+'},
			  {'+', '_', 'B', '_', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char oneC[8][8]  = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', 'G', '_', 'G', '+', '+', '+', '+'},
			  {'+', 'B', '+', 'B', '+', '+', '+', '+'},
			  {'+', '_', 'P', '_', '+', '+', '+', '+'},
			  {'+', '+', '_', '+', 'G', '_', '_', '+'},
			  {'+', '+', '_', '_', '_', 'B', '_', '+'},
			  {'+', '+', '+', '+', '_', '_', '_', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char twoA[8][8]  = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', 'G', '_', '+', '+', '+'},
			  {'+', '+', '+', 'G', '_', 'P', '+', '+'},
			  {'+', '+', '+', '_', 'B', '_', '+', '+'},
			  {'+', '_', '_', 'B', '+', '+', '+', '+'},
			  {'+', '_', '+', '_', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char twoB[8][8]  = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', '_', 'G', '+', '+'},
			  {'+', '+', '+', '+', '+', '_', '+', '+'},
			  {'+', '+', '+', '_', '_', 'B', '+', '+'},
			  {'+', '_', 'B', 'P', 'B', '_', '+', '+'},
			  {'+', 'G', 'G', '_', '_', '_', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };
char twoC[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', 'G', 'B', 'G', '_', '_', '_', '+'},
			  {'+', '_', '_', '+', '_', '_', '_', '+'},
			  {'+', '+', '+', '+', '+', 'B', '+', '+'},
			  {'+', '+', '+', '+', '_', '_', '+', '+'},
			  {'+', 'P', 'B', '_', 'G', '_', '+', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char threeA[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '_', 'P', 'G', '+'},
			  {'+', '+', '+', '+', 'B', '_', 'G', '+'},
			  {'+', '_', '_', '_', 'B', '_', '_', '+'},
			  {'+', '_', '_', '_', '+', '_', '_', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char threeB[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '_', '_', '_', '+'},
			  {'+', '+', '+', '+', 'P', 'B', '_', '+'},
			  {'+', '+', '+', '+', 'G', 'B', '_', '+'},
			  {'+', '+', '+', '+', '+', 'B', 'G', '+'},
			  {'+', '+', '+', '+', '+', '_', 'G', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char threeC[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '_', 'G', '+', '+'},
			  {'+', '+', '+', '+', 'G', '_', '_', '+'},
			  {'+', '+', '+', '+', '+', 'B', '_', '+'},
			  {'+', '_', '_', '_', '_', '_', '+', '+'},
			  {'+', 'P', '+', '_', 'B', 'B', '_', '+'},
			  {'+', '_', '_', '_', '+', 'G', '_', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char fourA[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', '_', '_', '+', '+'},
			  {'+', '_', '+', '_', '_', 'B', '_', '+'},
			  {'+', 'G', '_', '_', '_', '_', 'P', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', 'G', '_', 'B', '+', '+', '+', '+'},
			  {'+', '+', '_', '_', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char fourB[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', 'B', 'G', '+', '+'},
			  {'+', '+', '+', '+', '+', 'P', '+', '+'},
			  {'+', '+', '+', 'G', 'B', '_', '+', '+'},
			  {'+', '_', 'B', '_', '_', '_', '+', '+'},
			  {'+', 'G', '_', '_', '_', '_', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char fourC[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '_', '_', '_', '+'},
			  {'+', '+', '+', '+', 'P', '+', '_', '+'},
			  {'+', '+', '+', '+', '_', 'B', '_', '+'},
			  {'+', '+', '+', '+', '+', '_', 'G', '+'},
			  {'+', '+', '_', 'B', '_', 'B', '_', '+'},
			  {'+', '+', 'G', '_', 'G', '_', '_', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char fiveA[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '_', 'B', '_', 'G', 'G', '+'},
			  {'+', '+', '_', '_', '+', '_', '_', '+'},
			  {'+', '+', '+', 'G', '+', '+', '+', '+'},
			  {'+', '_', '_', '_', '+', '+', '+', '+'},
			  {'+', '_', 'B', 'B', '+', '+', '+', '+'},
			  {'+', '_', 'P', '_', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char fiveB[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', 'G', '_', '_', 'G', '_', '_', '+'},
			  {'+', '_', 'B', '+', '_', 'B', '_', '+'},
			  {'+', '_', 'P', '+', '+', 'G', '_', '+'},
			  {'+', 'B', '_', '+', '+', '+', '+', '+'},
			  {'+', '_', '_', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

char fiveC[8][8] = { {'+', '+', '+', '+', '+', '+', '+', '+'},
			  {'+', '_', '_', 'P', '+', '+', '+', '+'},
			  {'+', '_', '+', 'B', '+', '_', '_', '+'},
			  {'+', '_', 'B', '_', '_', '_', '_', '+'},
			  {'+', '+', '+', '+', 'B', '_', 'G', '+'},
			  {'+', '+', '+', '+', '_', '_', 'G', '+'},
			  {'+', '+', '+', '+', '_', 'G', '+', '+'},
			  {'+', '+', '+', '+', '+', '+', '+', '+'} };

void loadMap(char stage, int level){
	int i, j;
	switch(stage){
		case '1': switch(level){
					case 1: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=oneA[i][j];
								}
							}
							bestMove=best1A;
							break;
					case 2: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=oneB[i][j];
								}
							}
							bestMove=best1B;
							break;
					case 3: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=oneC[i][j];
								}
							}
							bestMove=best1C;
							break;
				}
				break;
		case '2': switch(level){
					case 1: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=twoA[i][j];
								}
							}
							bestMove=best2A;
							break;
					case 2: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=twoB[i][j];
								}
							}
							bestMove=best2B;
							break;
					case 3: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=twoC[i][j];
								}
							}
							bestMove=best2C;
							break;
				}
				break;
		case '3': switch(level){
					case 1: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=threeA[i][j];
								}
							}
							bestMove=best3A;
							break;
					case 2: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=threeB[i][j];
								}
							}
							bestMove=best3B;
							break;
					case 3: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=threeC[i][j];
								}
							}
							bestMove=best3C;
							break;
				}
				break;
		case '4': switch(level){
					case 1: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=fourA[i][j];
								}
							}
							bestMove=best4A;
							break;
					case 2: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=fourB[i][j];
								}
							}
							bestMove=best4B;
							break;
					case 3: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=fourC[i][j];
								}
							}
							bestMove=best4C;
							break;
				}
				break;
		case '5': switch(level){
					case 1: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=fiveA[i][j];
								}
							}
							bestMove=best5C;
							break;
					case 2: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=fiveB[i][j];
								}
							}
							bestMove=best5B;
							break;
					case 3: for(i=0; i<size; i++){
								for(j=0; j<size; j++){
									globalMap[i][j]=fiveC[i][j];
								}
							}
							bestMove=best5C;
							break;
				}
				break;
		default: printf("\nINVALID\n");
	}
}

int checkGameState(){
	int i, j, flag=0;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(playMap[i][j]=='G' || playMap[i][j]=='Y') flag++;
		}
	}

	if(flag>0) return 0;
	else{
		printf("\n\nWin!\n");
		printf("Number of Moves: %d \n\n", moves);
		return 1;
	} 
}

void screen(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

void moveS(){
	if(playMap[playerX][playerY]=='Y'){
		if(playMap[playerX+1][playerY]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX+1][playerY]=='_'){
			playMap[playerX][playerY]='G';
			playMap[playerX+1][playerY]='P';
			playerX=playerX+1;
		}else if(playMap[playerX+1][playerY]=='B'){
			if(playMap[playerX+2][playerY]=='_'){
				playMap[playerX+2][playerY]='B';
				playMap[playerX+1][playerY]='P';
				playMap[playerX][playerY]='G';
				playerX=playerX+1;
			}else if(playMap[playerX+2][playerY]=='G'){
				playMap[playerX+2][playerY]='X';
				playMap[playerX+1][playerY]='P';
				playMap[playerX][playerY]='G';
				playerX=playerX+1;
			}else if(playMap[playerX+2][playerY]=='+'){
				moves--;
			}
		}else if(playMap[playerX+1][playerY]=='G'){
			playMap[playerX][playerY]='G';
			playMap[playerX+1][playerY]='Y';
			playerX=playerX+1;
		}else if(playMap[playerX+1][playerY]=='X'){
			if(playMap[playerX+2][playerY]=='_'){
				playMap[playerX][playerY]='G';
				playMap[playerX+1][playerY]='Y';
				playMap[playerX+2][playerY]='B';
				playerX=playerX+1;
			}else if(playMap[playerX+2][playerY]=='G'){
				playMap[playerX][playerY]='G';
				playMap[playerX+1][playerY]='Y';
				playMap[playerX+2][playerY]='X';
				playerX=playerX+1;
			}else if(playMap[playerX+2][playerY]=='+'){
				moves--;
			}
		}
	}else if(playMap[playerX+1][playerY]=='X'){
		if(playMap[playerX+2][playerY]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX+2][playerY]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX+1][playerY]='Y';
			playMap[playerX+2][playerY]='B';
			playerX=playerX+1;
		}else if(playMap[playerX+2][playerY]=='B'){
			printf("\n\nCannot move 2 boxes! \n\n");
			moves--;
		}else if(playMap[playerX+2][playerY]=='G'){
			playMap[playerX+1][playerY]='Y';
			playMap[playerX+2][playerY]='X';
			playMap[playerX][playerY]='_';
			playerX=playerX+1;
		}else if(playMap[playerX+2][playerY]=='+'){
				moves--;
		}
	}else{
		if(playMap[playerX+1][playerY]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX+1][playerY]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX+1][playerY]='P';
			playerX=playerX+1;
		}else if(playMap[playerX+1][playerY]=='B'){
			if(playMap[playerX+2][playerY]=='_'){
				playMap[playerX+2][playerY]='B';
				playMap[playerX+1][playerY]='P';
				playMap[playerX][playerY]='_';
				playerX=playerX+1;
			}else if(playMap[playerX+2][playerY]=='G'){
				playMap[playerX+2][playerY]='X';
				playMap[playerX+1][playerY]='P';
				playMap[playerX][playerY]='_';
				playerX=playerX+1;
			}else if(playMap[playerX+2][playerY]=='+'){
				moves--;
			}else if(playMap[playerX+2][playerY]=='B'){
				moves--;
			}
		}else if(playMap[playerX+1][playerY]=='G'){
			playMap[playerX][playerY]='_';
			playMap[playerX+1][playerY]='Y';
			playerX=playerX+1;
		}
	}
}

void moveW(){
	if(playMap[playerX][playerY]=='Y'){
		if(playMap[playerX-1][playerY]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX-1][playerY]=='_'){
			playMap[playerX][playerY]='G';
			playMap[playerX-1][playerY]='P';
			playerX=playerX-1;
		}else if(playMap[playerX-1][playerY]=='B'){
			if(playMap[playerX-2][playerY]=='_'){
				playMap[playerX-2][playerY]='B';
				playMap[playerX-1][playerY]='P';
				playMap[playerX][playerY]='G';
				playerX=playerX-1;
			}else if(playMap[playerX-2][playerY]=='G'){
				playMap[playerX-2][playerY]='X';
				playMap[playerX-1][playerY]='P';
				playMap[playerX][playerY]='G';
				playerX=playerX-1;
			}else if(playMap[playerX-2][playerY]=='+'){
				moves--;
			}
		}else if(playMap[playerX-1][playerY]=='G'){
			playMap[playerX][playerY]='G';
			playMap[playerX-1][playerY]='Y';
			playerX=playerX-1;
		}else if(playMap[playerX-1][playerY]=='X'){
			if(playMap[playerX-2][playerY]=='_'){
				playMap[playerX][playerY]='G';
				playMap[playerX-1][playerY]='Y';
				playMap[playerX-2][playerY]='B';
				playerX=playerX-1;
			}else if(playMap[playerX-2][playerY]=='G'){
				playMap[playerX][playerY]='G';
				playMap[playerX-1][playerY]='Y';
				playMap[playerX-2][playerY]='X';
				playerX=playerX-1;
			}else if(playMap[playerX-2][playerY]=='+'){
				moves--;
			}
		}	
	}else if(playMap[playerX-1][playerY]=='X'){
		if(playMap[playerX-2][playerY]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX-2][playerY]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX-1][playerY]='Y';
			playMap[playerX-2][playerY]='B';
			playerX=playerX-1;
		}else if(playMap[playerX-2][playerY]=='B'){
			printf("\n\nCannot move 2 boxes! \n\n");
			moves--;
		}else if(playMap[playerX-2][playerY]=='G'){
			playMap[playerX][playerY]='_';
			playMap[playerX-2][playerY]='X';
			playMap[playerX-1][playerY]='Y';
			playerX=playerX-1;
		}else if(playMap[playerX-2][playerY]=='+'){
				moves--;
		}
	}else{
		if(playMap[playerX-1][playerY]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX-1][playerY]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX-1][playerY]='P';
			playerX=playerX-1;
		}else if(playMap[playerX-1][playerY]=='B'){
			if(playMap[playerX-2][playerY]=='_'){
				playMap[playerX-2][playerY]='B';
				playMap[playerX-1][playerY]='P';
				playMap[playerX][playerY]='_';
				playerX=playerX-1;
			}else if(playMap[playerX-2][playerY]=='G'){
				playMap[playerX-2][playerY]='X';
				playMap[playerX-1][playerY]='P';
				playMap[playerX][playerY]='_';
				playerX=playerX-1;
			}else if(playMap[playerX-2][playerY]=='+'){
				moves--;
			}else if(playMap[playerX-2][playerY]=='B'){
				moves--;
			}
		}else if(playMap[playerX-1][playerY]=='G'){
			playMap[playerX][playerY]='_';
			playMap[playerX-1][playerY]='Y';
			playerX=playerX-1;
		}
	}
	
}

void moveA(){
	if(playMap[playerX][playerY]=='Y'){
		if(playMap[playerX][playerY-1]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX][playerY-1]=='_'){
			playMap[playerX][playerY]='G';
			playMap[playerX][playerY-1]='P';
			playerY=playerY-1;
		}else if(playMap[playerX][playerY-1]=='B'){
			if(playMap[playerX][playerY-2]=='_'){
				playMap[playerX][playerY-2]='B';
				playMap[playerX][playerY-1]='P';
				playMap[playerX][playerY]='G';
				playerY=playerY-1;
			}else if(playMap[playerX][playerY-2]=='G'){
				playMap[playerX][playerY-2]='X';
				playMap[playerX][playerY-1]='P';
				playMap[playerX][playerY]='G';
				playerY=playerY-1;
			}else if(playMap[playerX][playerY-2]=='+'){
				moves--;
			}
		}else if(playMap[playerX][playerY-1]=='G'){
			playMap[playerX][playerY]='G';
			playMap[playerX][playerY-1]='Y';
			playerY=playerY-1;
		}else if(playMap[playerX][playerY-1]=='X'){
			if(playMap[playerX][playerY-2]=='_'){
				playMap[playerX][playerY]='G';
				playMap[playerX][playerY-1]='Y';
				playMap[playerX][playerY-2]='B';
				playerY=playerY-1;
			}else if(playMap[playerX][playerY-2]=='G'){
				playMap[playerX][playerY]='G';
				playMap[playerX][playerY-1]='Y';
				playMap[playerX][playerY-2]='X';
				playerY=playerY-1;
			}else if(playMap[playerX][playerY-2]=='+'){
				moves--;
			}
		}
	}else if(playMap[playerX][playerY-1]=='X'){
		if(playMap[playerX][playerY-2]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX][playerY-2]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY-1]='Y';
			playMap[playerX][playerY-2]='B';
			playerY=playerY-1;
		}else if(playMap[playerX][playerY-2]=='B'){
			printf("\n\nCannot move 2 boxes! \n\n");
			moves--;
		}else if(playMap[playerX][playerY-2]=='G'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY-2]='X';
			playMap[playerX][playerY-1]='Y';
			playerY=playerY-1;
		}else if(playMap[playerX][playerY-2]=='+'){
				moves--;
		}
	}else{
		if(playMap[playerX][playerY-1]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX][playerY-1]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY-1]='P';
			playerY=playerY-1;
		}else if(playMap[playerX][playerY-1]=='B'){
			if(playMap[playerX][playerY-2]=='_'){
				playMap[playerX][playerY-2]='B';
				playMap[playerX][playerY-1]='P';
				playMap[playerX][playerY]='_';
				playerY=playerY-1;
			}else if(playMap[playerX][playerY-2]=='G'){
				playMap[playerX][playerY-2]='X';
				playMap[playerX][playerY-1]='P';
				playMap[playerX][playerY]='_';
				playerY=playerY-1;
			}else if(playMap[playerX][playerY-2]=='+'){
				moves--;
			}else if(playMap[playerX][playerY-2]=='B'){
				moves--;
			}
		}else if(playMap[playerX][playerY-1]=='G'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY-1]='Y';
			playerY=playerY-1;
		}
	}
}

void moveD(){
	if(playMap[playerX][playerY]=='Y'){
		if(playMap[playerX][playerY+1]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX][playerY+1]=='_'){
			playMap[playerX][playerY]='G';
			playMap[playerX][playerY+1]='P';
			playerY=playerY+1;
		}else if(playMap[playerX][playerY+1]=='B'){
			if(playMap[playerX][playerY+2]=='_'){
				playMap[playerX][playerY+2]='B';
				playMap[playerX][playerY+1]='P';
				playMap[playerX][playerY]='G';
				playerY=playerY+1;
			}else if(playMap[playerX][playerY+2]=='G'){
				playMap[playerX][playerY+2]='X';
				playMap[playerX][playerY+1]='P';
				playMap[playerX][playerY]='G';
				playerY=playerY+1;
			}else if(playMap[playerX][playerY+2]=='+'){
				moves--;
			}
		}else if(playMap[playerX][playerY+1]=='G'){
			playMap[playerX][playerY]='G';
			playMap[playerX][playerY+1]='Y';
			playerY=playerY+1;
		}else if(playMap[playerX][playerY+1]=='X'){
			if(playMap[playerX][playerY+2]=='_'){
				playMap[playerX][playerY]='G';
				playMap[playerX][playerY+1]='Y';
				playMap[playerX][playerY+2]='B';
				playerY=playerY+1;
			}else if(playMap[playerX][playerY+2]=='G'){
				playMap[playerX][playerY]='G';
				playMap[playerX][playerY+1]='Y';
				playMap[playerX][playerY+2]='X';
				playerY=playerY+1;
			}else if(playMap[playerX][playerY+2]=='+'){
				moves--;
			}
		}
	}else if(playMap[playerX][playerY+1]=='X'){
		if(playMap[playerX][playerY+2]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX][playerY+2]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY+1]='Y';
			playMap[playerX][playerY+2]='B';
			playerY=playerY+1;
		}else if(playMap[playerX][playerY+2]=='B'){
			printf("\n\nCannot move 2 boxes! \n\n");
			moves--;
		}else if(playMap[playerX][playerY+2]=='G'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY+2]='X';
			playMap[playerX][playerY+1]='Y';
			playerY=playerY+1;
		}else if(playMap[playerX][playerY+2]=='+'){
				moves--;
		}
	}else{
		if(playMap[playerX][playerY+1]=='+'){
			printf("\n\nOut of Bounds! \n\n");
			moves--;
		}else if(playMap[playerX][playerY+1]=='_'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY+1]='P';
			playerY=playerY+1;
		}else if(playMap[playerX][playerY+1]=='B'){
			if(playMap[playerX][playerY+2]=='_'){
				playMap[playerX][playerY+2]='B';
				playMap[playerX][playerY+1]='P';
				playMap[playerX][playerY]='_';
				playerY=playerY+1;
			}else if(playMap[playerX][playerY+2]=='G'){
				playMap[playerX][playerY+2]='X';
				playMap[playerX][playerY+1]='P';
				playMap[playerX][playerY]='_';
				playerY=playerY+1;
			}else if(playMap[playerX][playerY+2]=='+'){
				moves--;
			}else if(playMap[playerX][playerY+2]=='B'){
				moves--;
			}
		}else if(playMap[playerX][playerY+1]=='G'){
			playMap[playerX][playerY]='_';
			playMap[playerX][playerY+1]='Y';
			playerY=playerY+1;
		}
	}
	
}

void drawDots(){
   int i,j, x=10, y=10, a, b;
   for(i=0; i<14; i++, b+=16){
	for(j=0; j<20; j++, a+=16){
		screen(a, b, 0.1, 0.1, WHITE);
	}
	a=x;
   }
}

void drawLine2(int x, int y){
   int i,j, a=x, b=y;
   for(i=0; i<5; i++, b+=3){
	for(j=0; j<14; j++, a+=1){
		screen(a, b, 0.1, 0.1, BLACK);
	}
	a=x;
   }
}


void drawLineVert(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(x+2, i+2,color);
}

void drawLineHor(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j+2, y+2,color);
}

void drawLinesHor(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(x, j, color);
	 y++;
	 x++;
}

void drawX(int x, int y, int w, int h, int color){
	

}

void printCongrats(){
	screen(0, 0, 320, 200, BLACK);
	write_text("      CONGRATS :-)   ", 100, 50, YELLOW, 2);
	write_text("                +              ", 20, 110, RED, 0);
	write_text("  +                    +         ", 20, 120, RED, 0);
	write_text("        +                    +   ", 20, 130, RED, 0);
	write_text("                +       +        ", 20, 140, RED, 0);
	write_text("          +                    ) + ", 20, 150, RED, 0);
	write_text("  +           (  ( (  +   ) ( /(    ", 20, 160, RED, 0);
	write_text("  (  (   (  + )\))()(  ( /( )\()|  +", 20, 170, ORANGE, 0);
	write_text("  )\ )\  )\ )((_))(()\ )(_)|_))/)\  ", 20, 180, ORANGE, 0);
	write_text(" ((_|(_)_(_/( (()(_|(_|(_)_| |_((_) ", 20, 190, YELLOW, 0);
	//http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
	delay(300);
	main();

}

void printMap(){
	char str[3];
	int x=140, y=50, i, j;
	int a=x, b=y;
	for(i=0; i<size; i++, b+=15){
		for(j=0; j<size; j++, a+=15)
			if(playMap[i][j]=='+'){
				screen(a, b, 13, 13, MAROON);
				drawLineVert(a, b, 9, 9, BLACK);
				drawLineHor(a, b, 9, 9, BLACK);
			}else if(playMap[i][j]=='_'){
				screen(a, b, 13, 13, WHITE);
			}else if(playMap[i][j]=='P'){
				screen(a, b, 13, 13, YELLOW);
			}else if(playMap[i][j]=='G'){
				screen(a, b, 13, 13, GRAY);
			}else if(playMap[i][j]=='B'){
				screen(a, b, 13, 13, BROWN);
				drawLine2(a, b);
			}else if(playMap[i][j]=='Y'){
				screen(a, b, 13, 13, ORANGE);
			}else if(playMap[i][j]=='X'){
				screen(a, b, 13, 13, GREEN);
				drawLine2(a, b);
			}else{
			}
		a=x;
	}
}

main(){
	level=1;
	char str[10];
	char stg[10];
	char bst[10];
	int choice, i, j;
	set_graphics(VGA_320X200X256);
	screen(0, 0, 320, 200, BLACK);
	drawDots();
	//write_text("         _       _           ", 20, 15, YELLOW, 0);
	//write_text(" ___ ___| |_ ___| |_ ___ ___ ", 20, 23, YELLOW, 0);
	//write_text("|_ -| . | '_| . | . | .'|   |", 20, 31, YELLOW, 0);
	//write_text("|___|___|_,_|___|___|__,|_|_|", 20, 39, YELLOW, 0);
	
	write_text(" ____", 180, 80, RED, 0);
	write_text("|____|", 180, 90, RED, 0);
	write_text("|____|", 180, 100, RED, 0);
	write_text("|____|", 180, 110, RED, 0);
	write_text("|____|", 180, 120, RED, 0);
	
	write_text(" ___", 210, 100, GREEN, 0);
	write_text("|___|", 210, 110, GREEN, 0);
	write_text("|___|", 210, 120, GREEN, 0);
	write_text("|___|", 210, 130, GREEN, 0);

	write_text(" __", 200, 115, BLUE, 0);
	write_text("|__|", 200, 125, BLUE, 0);
	write_text("|__|", 200, 135, BLUE, 0);
	//art from: https://www.asciiart.eu/miscellaneous/boxes

	write_text("SOKOBAN", 125, 30, YELLOW, 1);

	write_text("Choose level: ", 45, 65, MAROON, 0);
	write_text("[1] Level 1 ", 45, 75, MAROON, 0);
	write_text("[2] Level 2 ", 45, 85, MAROON, 0);
	write_text("[3] Level 3 ", 45, 95, MAROON, 0);
	write_text("[4] Level 4 ", 45, 105, MAROON, 0);
	write_text("[5] Level 5 ", 45, 115, MAROON, 0);
	write_text("[q] Quit ", 45, 130, MAROON, 0);
	write_text("Move the boxes to the goals!", 40, 155, YELLOW, 0);
	choice=getch();
	while(choice!=quit){
		while(level<4){
		screen(0, 0, 320, 200, BLACK);
		moves=0;
		loadMap(choice, level);
		for(i=0; i<size; i++){
			for(j=0; j<size; j++){
				if(globalMap[i][j]=='P'){
					playerX=i;
					playerY=j;
					playMap[i][j]=globalMap[i][j];
				}
				playMap[i][j]=globalMap[i][j];
			}
		}
		write_text("BEST MOVES: ", 10, 10, BLUE, 0);
		sprintf(str,"%d",bestMove);
		write_text(str, 120, 10, BLUE, 0);
		write_text("CURRENT MOVES: ", 10, 20, BLUE, 0);
		sprintf(str,"%d",moves);
		write_text(str, 140, 20, BLUE, 0);
		sprintf(str,"Stage %d",level);
		write_text(str, 168, 40, GREEN, 0);
		write_text("Up: W", 10, 40, YELLOW, 0);
		write_text("Down: S", 10, 50, YELLOW, 0);
		write_text("Left: A", 10, 60, YELLOW, 0);
		write_text("Right: D", 10, 70, YELLOW, 0);
		write_text("Quit: Q", 10, 90, WHITE, 0);
		write_text("Reset: R", 10, 100, WHITE, 0);

		write_text("Player", 10, 130, YELLOW, 0);
		write_text("Box", 10, 140, BROWN, 0);
		write_text("Goal", 10, 150, GRAY, 0);
		write_text("Wall", 10, 160, MAROON, 0);
		printMap();
		do{
			char move=getch();
			switch(move){
				case up_key: moveW(); moves++; break;
				case down_key: moveS(); moves++; break;
				case right_key: moveD(); moves++; break;
				case left_key: moveA(); moves++; break;
				case quit: main(); break;
				case reset: for(i=0; i<size; i++){
						for(j=0; j<size; j++){
							if(globalMap[i][j]=='P'){
								playerX=i;
								playerY=j;
								playMap[i][j]=globalMap[i][j];
							}
							playMap[i][j]=globalMap[i][j];
						}
					}
					moves=0;
					break;
				default: break;
			}
			screen(140, 20, 15, 15, BLACK);
			sprintf(str,"%d",moves);
			write_text(str, 140, 20, BLUE, 0);
			screen(168, 40, 15, 15, BLACK);
			sprintf(str,"Stage %d",level);
			write_text(str, 168, 40, GREEN, 0);
			printMap();
		}while(checkGameState()!=1);
		if(bestMove > moves){
			switch(choice){
				case '1':
						if(level == 1){
							best1A = moves;
						}
						if(level == 2){
							best1B = moves;
						}
						if(level == 3){
							best1C = moves;
						}
						break;
				case '2':
						if(level == 1){
							best2A = moves;
						}
						if(level == 2){
							best2B = moves;
						}
						if(level == 3){
							best2C = moves;
						}
						break;
				case '3':
						if(level == 1){
							best3A = moves;
						}
						if(level == 2){
							best3B = moves;
						}
						if(level == 3){
							best3C = moves;
						}
						break;
				case '4':
						if(level == 1){
							best4A = moves;
						}
						if(level == 2){
							best4B = moves;
						}
						if(level == 3){
							best4C = moves;
						}
						break;
				case '5':
						if(level == 1){
							best5A = moves;
						}
						if(level == 2){
							best5B = moves;
						}
						if(level == 3){
							best5C = moves;
						}
						break;
			}
		}
		level+=1;
		}
		printCongrats();
	}
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	exit(0);
}
