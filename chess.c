#include <stdio.h>
#include <stdlib.h>

void printBoard();
void selectPiece();

const char boardColumns[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'A', 'B', 
							'C', 'D', 'E', 'F', 'G', 'H'};
const int boardRows[] = {1, 2, 3, 4, 5, 6, 7, 8};

char* gameBoard[64][2] = {
	{"BR"}, {"BN"}, {"BB"}, {"BQ"}, {"BK"}, {"BB"}, {"BN"}, {"BR"},
	{"BP"}, {"BP"}, {"BP"}, {"BP"}, {"BP"}, {"BP"}, {"BP"}, {"BP"},
	{"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "},
	{"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "},
	{"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "},
	{"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "}, {"O "},
	{"WP"}, {"WP"}, {"WP"}, {"WP"}, {"WP"}, {"WP"}, {"WP"}, {"WP"},
	{"WR"}, {"WN"}, {"WB"}, {"WQ"}, {"WK"}, {"WB"}, {"WN"}, {"WR"}
};



void printBoard(){
	int i;
	for (int i = 0; i < 64; ++i){
		printf("%s ", *gameBoard[i]);
		if((i+1) % 8 == 0){ 
			printf("\n");
		}
	}
}

void selectPiece(){
	int i;
	int j;
	char ch;
	char location[3];
	printf("\nPlease select a piece: ");
	
	for(i = 0; (i < 2) && ((ch = getchar()) != EOF) && (ch != '\n'); i++){
		location[i] = ch;
	}
	location[i] = '\0';

	for (i = 0; i < 16; ++i)
	{
		if(location[0] == boardColumns[i]){
			for (j = 0; j < 8; ++j){
				if((location[1] - '0') == boardRows[j]){
					printf("%s\n", location);
				}
			}
		}
	}
}

int main(int argc, char** argv){
	printBoard();
	selectPiece();
}
