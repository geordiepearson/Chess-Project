#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Declarations
void printBoard(int *turn);
void getInputTile(char piece_location[], int* piece_input_flag);
void getArrayTile(char piece_location[], int* arrayIndex);
void selectTile(char piece_location[], int* arrayIndex, int* piece_input_flag);

void isTeamPiece(int* arrayIndex, int* piece_team_flag, int* turn);
void selectPiece(int* turn, int* arrayIndex, char piece_location[]);

void movePiece(int* turn, int*arrayIndexPiece, int* arrayIndexMove, 
	char piece_location[]);
void movePawn(int* arrayIndexPiece, int* arrayIndexMove);
/* 
Defines all of the potential inputs a user could enter for a valid colummn 
or row on a chess board.
*/
const char boardColumns[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'A', 'B', 
							'C', 'D', 'E', 'F', 'G', 'H'};
const int boardRows[] = {1, 2, 3, 4, 5, 6, 7, 8};

// Intialises the chess board in its default state
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
	// Prints the gameboard in its current state
	int i;
	if(*turn %  2 == 0){ //If it is blacks turn
		printf("Black's Turn.\n");
	}else{ 
		printf("White's Turn.\n");
	}

	/*
	Iterates through the array and print every value and after every 8 values,
	start a new line
	*/
	for (int i = 0; i < 64; ++i){
		printf("%s ", *gameBoard[i]);
		if((i+1) % 8 == 0){ 
			printf("\n");
		}
	}
	printf("\n");
}

void getInputTile(char piece_location[], int* piece_input_flag){
	/*
	Gets the input of the user and checks if it is a valid tile on the board
	*/
	int i;
	int j;
	char ch;
	
	// Get every character in the line of user input and create a string
	for(i = 0; (i < 80) && ((ch = getchar()) != EOF) && (ch != '\n'); i++){
		piece_location[i] = ch;
	}
	piece_location[i] = '\0';

	//Checks if the input contains one of the 8 valid rows and 16 valid columns 
	for (i = 0; i < 16; ++i)
	{
		if(piece_location[0] == boardColumns[i]){
			for (j = 0; j < 8; ++j){
				if((piece_location[1] - '0') == boardRows[j]){	
					*piece_input_flag = 1; //Indicates input is a valid tile
				}
			}
		}
	}
}

void getArrayTile(char piece_location[], int* arrayIndex){
	/*
	Gets the index of the gameBoard array corresponding to the inputted value
	*/
	*arrayIndex = 64-((piece_location[1] - '0') * 8);// Gets index based on row
	
	// Adds to index based on column
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
	/*
	Selects a tile by prompting user for a valid tile and computing the 
	corresponding index
	*/
	while(*piece_input_flag == 0){// While inputted tile is not valid
		*piece_input_flag = 0;
		printf("Please select a valid tile: ");
		getInputTile(piece_location, piece_input_flag);// Checks if tile is valid
	}
	getArrayTile(piece_location, arrayIndex);// Computes corresponding index
}

void isTeamPiece(int* arrayIndex, int* piece_team_flag, int* turn){
	/*
	Checks whether there is one of the current players pieces at the given 
	position on the board
	*/
	char team = *gameBoard[*arrayIndex][0];

	if(team == 'W' && (*turn % 2) == 1){
		// Indicates there is a white piece and it is white's turn
		*piece_team_flag = 1;
	}

	else if(team == 'B' && (*turn % 2) == 0){
		// Indicates there is a black piece and it is black's turn
		*piece_team_flag = 1;
	}	
}

void selectPiece(int* turn, int* arrayIndexPiece, char piece_location[]){
	/*
	Continuosly gets user input until a valid piece is selected and then 
	prints this piece and its location
	*/

	int piece_input_flag = 0;// Intialise flag to check for valid input
	int piece_team_flag = 0;// Intialise flag to check for valid piece

	while(piece_team_flag == 0){
		piece_input_flag = 0;
		selectTile(piece_location, arrayIndexPiece, &piece_input_flag);
		isTeamPiece(arrayIndexPiece, &piece_team_flag, turn);
	}

	// prints the type of piece and its location
	printf("\nSelected piece is %s at %c%c.\n\n", *gameBoard[*arrayIndexPiece]
		,piece_location[0],piece_location[1]); 
}

void movePawn(int* arrayIndexPiece, int* arrayIndexMove){
	// If the selected pawn is white
	if(*gameBoard[*arrayIndexPiece][0] == 'W'){
		// Case for when player moves two on first movement
		if(*arrayIndexPiece - *arrayIndexMove == 16 && // Checks that new position is 2 spaces in front
		 *gameBoard[*arrayIndexMove] == "O " && // Checks that new position is empty
		 *gameBoard[*arrayIndexMove + 8] == "O " && // Checks that tile directly in front is empty
		 47 < *arrayIndexPiece && *arrayIndexPiece < 56){ // Checks that it is still pawns first move
			
			*gameBoard[*arrayIndexPiece] = "O ";
			*gameBoard[*arrayIndexMove] = "WP";
		}

		//Case for regular foward movment
		if(*arrayIndexPiece - *arrayIndexMove == 8 && *gameBoard[*arrayIndexMove]
		 == "O "){ //Checks the piece is moving forward one tile and that the new position is empty
			*gameBoard[*arrayIndexPiece] = "O ";
			*gameBoard[*arrayIndexMove] = "WP";
		}
	}

	// If the selected pawn is black
	else if(*gameBoard[*arrayIndexPiece][0] == 'B'){
		// Case for when player moves two on first movement
		if(*arrayIndexPiece - *arrayIndexMove == -16 && // Checks that new position is 2 spaces in front
		 *gameBoard[*arrayIndexMove] == "O " && // Checks that new position is empty
		 *gameBoard[*arrayIndexMove - 8] == "O " && // Checks that tile directly in front is empty
		 7 < *arrayIndexPiece && *arrayIndexPiece < 16){ // Checks that it is still pawns first move
			
			*gameBoard[*arrayIndexPiece] = "O ";
			*gameBoard[*arrayIndexMove] = "BP";
		}

		//Case for regular foward movment
		if(*arrayIndexPiece - *arrayIndexMove == -8 && *gameBoard[*arrayIndexMove]
		 == "O "){//Checks the piece is moving forward one tile and that the new position is empty
			*gameBoard[*arrayIndexPiece] = "O ";
			*gameBoard[*arrayIndexMove] = "BP";
		}
	}
}

void movePiece(int* turn, int* arrayIndexPiece, int* arrayIndexMove, 
	char piece_movement[]){
	int piece_input_flag = 0;
	int piece_move_flag = 0;

	selectTile(piece_movement, arrayIndexMove, &piece_input_flag);
	printf("%s\n", *gameBoard[*arrayIndexPiece]);

	movePawn(arrayIndexPiece, arrayIndexMove);
	
}

int main(int argc, char** argv){
	int turn = 1;
	int arrayIndexPiece = 0;
	int arrayIndexMove = 0;

	char piece_location[3];
	char piece_movement[3];

	printBoard(&turn);
	selectPiece(&turn, &arrayIndexPiece, piece_location);
	printBoard(&turn);
	movePiece(&turn, &arrayIndexPiece, &arrayIndexMove, piece_movement);
	printBoard(&turn);

	selectPiece(&turn, &arrayIndexPiece, piece_location);
	printBoard(&turn);
	movePiece(&turn, &arrayIndexPiece, &arrayIndexMove, piece_movement);
	printBoard(&turn);
}

/* 
-how to index string array so no seg fault
-diagonal pawn movement
-seg fault if only 1 char input from player
*/