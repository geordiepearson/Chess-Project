#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBoard(int *turn);

void getInputPiece(char piece_location[], int* piece_input_flag);
void getArrayPiece(char piece_location[], int* arrayIndex);
void selectTile(char piece_location[], int* arrayIndex, int* piece_input_flag);

void getTeamPiece(int* arrayIndex, int* piece_team_flag, int* turn);
void selectPiece(int* turn, int* arrayIndex, char piece_location[]);

void movePiece(int* turn, int* arrayIndex, char piece_location[]);

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

void printBoard(int* turn){
	int i;
	if(*turn %  2 == 0){
		printf("Black's Turn.\n");
	}else{
		printf("White's Turn.\n");
	}

	for (int i = 0; i < 64; ++i){
		printf("%s ", *gameBoard[i]);
		if((i+1) % 8 == 0){ 
			printf("\n");
		}
	}
	printf("\n");
}

void getInputPiece(char piece_location[], int* piece_input_flag){
	int i;
	int j;
	char ch;
	
	for(i = 0; (i < 80) && ((ch = getchar()) != EOF) && (ch != '\n'); i++){
		piece_location[i] = ch;
	}
	piece_location[i] = '\0';

	for (i = 0; i < 16; ++i)
	{
		if(piece_location[0] == boardColumns[i]){
			for (j = 0; j < 8; ++j){
				if((piece_location[1] - '0') == boardRows[j]){	
					*piece_input_flag = 1;
				}
			}
		}
	}
}

void getArrayPiece(char piece_location[], int* arrayIndex){
	*arrayIndex = 64-((piece_location[1] - '0') * 8);
	if(piece_location[0] == 'b' || piece_location[0] == 'B'){
		*arrayIndex +=1;
	}

	else if(piece_location[0] == 'c' || piece_location[0] == 'C'){
		*arrayIndex +=2;
	}

	else if(piece_location[0] == 'd' || piece_location[0] == 'D'){
		*arrayIndex +=3;
	}

	else if(piece_location[0] == 'e' || piece_location[0] == 'E'){
		*arrayIndex +=4;
	}

	else if(piece_location[0] == 'f' || piece_location[0] == 'F'){
		*arrayIndex +=5;
	}

	else if(piece_location[0] == 'g' || piece_location[0] == 'G'){
		*arrayIndex +=6;
	}

	else if(piece_location[0] == 'h' || piece_location[0] == 'H'){
		*arrayIndex +=7;
	}
}

void selectTile(char piece_location[], int* arrayIndex, int* piece_input_flag){
	while(*piece_input_flag == 0){
		*piece_input_flag = 0;
		printf("Please select a valid tile: ");
		getInputPiece(piece_location, piece_input_flag);
	}
	getArrayPiece(piece_location, arrayIndex);
}

void getTeamPiece(int* arrayIndex, int* piece_team_flag, int* turn){
	char team = *gameBoard[*arrayIndex][0];

	if(team == 'W' && (*turn % 2) == 1){
		*piece_team_flag = 1;
	}

	else if(team == 'B' && (*turn % 2) == 0){
		*piece_team_flag = 1;
	}	
}

void selectPiece(int* turn, int* arrayIndex, char piece_location[]){
	int piece_input_flag = 0;
	int piece_team_flag = 0;

	while(piece_team_flag == 0){
		piece_input_flag = 0;
		selectTile(piece_location, arrayIndex, &piece_input_flag);
		getTeamPiece(arrayIndex, &piece_team_flag, turn);
	}

	printf("\nSelected piece is %s at %c%c.\n\n", *gameBoard[*arrayIndex],piece_location[0]
		,piece_location[1]);
}

void movePiece(int* turn, int* arrayIndex, char piece_location[]){
	int piece_input_flag = 0;
	int piece_move_flag = 0;

	while(piece_move_flag == 0){
		piece_input_flag = 0;
		selectTile(piece_location, arrayIndex, &piece_input_flag);
	}
}

int main(int argc, char** argv){
	int turn = 1;
	int arrayIndex = 0;
	int piece_input_flag = 0;

	char piece_location[3];
	char piece_movement[3];

	printBoard(&turn);
	selectPiece(&turn, &arrayIndex, piece_location);
	printBoard(&turn);
	selectTile(piece_location, &arrayIndex, &piece_input_flag);
}

/* 
-
-seg fault if only 1 char input from player
*/