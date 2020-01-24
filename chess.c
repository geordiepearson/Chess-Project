/*
** chess.c
**
** Author: Geordie Pearson
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "chess.h"

/* 
Defines all of the potential inputs a user could enter for a valid colummn 
or row on a chess board.
*/
const char boardColumns[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'A', 'B', 
							'C', 'D', 'E', 'F', 'G', 'H'};
const int boardRows[] = {1, 2, 3, 4, 5, 6, 7, 8};

// Intialises the chess board as an array in its default state.
char gameBoard[64][3] = {
	"BR", "BN", "BB", "BQ", "BK", "BB", "BN", "BR",
	"BP", "BP", "BP", "BP", "BP", "BP", "BP", "BP",
	"O ", "O ", "O ", "O ", "O ", "O ", "O ", "O ",
	"O ", "O ", "O ", "O ", "O ", "O ", "O ", "O ",
	"O ", "O ", "O ", "O ", "O ", "O ", "O ", "O ",
	"O ", "O ", "O ", "O ", "O ", "O ", "O ", "O ",
	"WP", "WP", "WP", "WP", "WP", "WP", "WP", "WP",
	"WR", "WN", "WB", "WQ", "WK", "WB", "WN", "WR"
};

void printBoard(int* turn){
	if(*turn %  2 == 0){ // If it is blacks turn
		printf("Black's Turn.\n");
	}

	else{ // If it is whites turn 
		printf("White's Turn.\n");
	}

	//Iterates through the array and prints every value. After every 8 values,
	//starts a new line.
	for (int i = 0; i < 64; ++i){
		printf("%s ", gameBoard[i]);
		if((i+1) % 8 == 0){ 
			printf("\n");
		}
	}
	printf("\n");
}

void getInputTile(char piece_location[], int* piece_input_flag, 
	int* piece_cancel_flag){

	// Intialise 2 integers which will be used to iterate through the users 
	// input and iterate through the arrays of valid rows and columns on the 
	// board. Also intialise a temporary character which will store each 
	//character in the input line before it is moved to a permenant variable. 
	int i;
	int j;
	char ch;
	
	// Get every character in the line of user input and create a string.
	for(i = 0; (i < 80) && ((ch = getchar()) != EOF) && (ch != '\n'); i++){
		piece_location[i] = ch;
	}
	piece_location[i] = '\0';

	//Checks if the input contains one of the 8 valid rows and 16 valid columns. 
	for (i = 0; i < 16; ++i)
	{
		// Checks if input possesses a valid column.
		if(piece_location[0] == boardColumns[i]){
			for (j = 0; j < 8; ++j){
				// Converts input to an integer and checks if it possesses a 
				// valid row.
				if((piece_location[1] - '0') == boardRows[j]){	
					*piece_input_flag = 1; //Indicates input is a valid tile.
				}
			}
		}
	}
}

void getArrayTile(char piece_location[], int* arrayIndex){
	// Gets index based on row.
	*arrayIndex = 64-((piece_location[1] - '0') * 8);
	
	// Adds to index based on column.
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

void selectTile(char piece_location[], int* arrayIndex, int* piece_input_flag, 
	int* piece_cancel_flag){

	// While the inputted tile is not valid
	while(*piece_input_flag == 0){
		*piece_input_flag = 0;
		printf("Please select a valid tile: ");
		// Gets user input and checks if tile is valid.
		getInputTile(piece_location, piece_input_flag, piece_cancel_flag);
	}
	
	// Computes corresponding array index.
	getArrayTile(piece_location, arrayIndex);
}

void isTeamPiece(int* arrayIndex, int* piece_team_flag, int* turn){
	// Initialises a character that represents the team of the selected piece.
	char team = gameBoard[*arrayIndex][0];

	// If a white piece is selected and it is white's turn.
	if(team == 'W' && (*turn % 2) == 1){
		*piece_team_flag = 1; // Indicates valid piece selection.
	}

	// If a black piece is selected and it is black's turn.
	else if(team == 'B' && (*turn % 2) == 0){
		*piece_team_flag = 1; // Indicates valid piece selection
	}	
}

void selectPiece(int* turn, int* arrayIndexPiece, char piece_location[], 
	int* piece_cancel_flag){

	// Intialises the flags to check for valid user input and valid piece 
	// selection. Set them to false. 
	int piece_input_flag = 0;
	int piece_team_flag = 0;

	// While a valid piece hasn't been selected, continuously prompt the user 
	// for input and check if the given tile contains a valid piece.
	while(piece_team_flag == 0){
		piece_input_flag = 0;
		selectTile(piece_location, arrayIndexPiece, &piece_input_flag, 
			piece_cancel_flag);
		isTeamPiece(arrayIndexPiece, &piece_team_flag, turn);
	}

	// prints the type of piece selected and its location.
	printf("\nSelected piece is %s at %c%c.\n\n", gameBoard[*arrayIndexPiece]
		,piece_location[0],piece_location[1]); 
}

void movePiece(int* turn, int* arrayIndexPiece, int* arrayIndexMove, 
	char piece_movement[], int* piece_cancel_flag){

	// Intialises the flags to check for valid tile selection. 
	int tile_input_flag;
	int valid_move_flag = 0;
	
	

	while(!valid_move_flag){
		// Resets the flag so a new tile can be selected.
		tile_input_flag = 0;

		// Prompts the user to enter the tile to move the selected piece to.
		selectTile(piece_movement, arrayIndexMove, &tile_input_flag, piece_cancel_flag);

		if(*piece_cancel_flag){
			return;
		}

		// Depending on the type of piece selected, check if the intended move is 
		// valid and if so, update the gameBoard.
 		if(gameBoard[*arrayIndexPiece][1] == 'P'){
 			movePawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
 				&valid_move_flag);
 		}

 		else if(gameBoard[*arrayIndexPiece][1] == 'R'){
 			moveRook(gameBoard, arrayIndexPiece, arrayIndexMove, 
 				&valid_move_flag);
 		}

 		else if(gameBoard[*arrayIndexPiece][1] == 'N'){
 			moveKnight(gameBoard, arrayIndexPiece, arrayIndexMove, 
 				&valid_move_flag);
 		}

 		else if(gameBoard[*arrayIndexPiece][1] == 'B'){
 			moveBishop(gameBoard, arrayIndexPiece, arrayIndexMove, 
 				&valid_move_flag);
 		}

 		else if(gameBoard[*arrayIndexPiece][1] == 'Q'){
 			moveQueen(gameBoard, arrayIndexPiece, arrayIndexMove, 
 				&valid_move_flag);
 		}

 		else if(gameBoard[*arrayIndexPiece][1] == 'K'){
 			moveKing(gameBoard, arrayIndexPiece, arrayIndexMove, 
 				&valid_move_flag);
 		}
 	}
 }


int main(int argc, char** argv){
	int turn = 1;
	int arrayIndexPiece = 0;
	int arrayIndexMove = 0;
	int piece_cancel_flag = 0;

	char piece_location[4];
	char piece_movement[4];
	printBoard(&turn);

	while(1){
		piece_cancel_flag = 0;
		selectPiece(&turn, &arrayIndexPiece, piece_location, &piece_cancel_flag);
		printBoard(&turn);
		movePiece(&turn, &arrayIndexPiece, &arrayIndexMove, piece_movement, 
			&piece_cancel_flag);
		printBoard(&turn);
	}
}

/*

Add ability to deselect piece
Add checkmate functionality 
Proper logic for normal turn flow
reset game
*/