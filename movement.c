#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"

void checkFowardTwoPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int twoTilesInfront, int oneTileInfront, 
	int rowStart, int rowEnd, int* valid_move_flag, int* turn){
	
	// Checks that all the following criteria are met:
	//   - The new tile is 2 spaces directly in front of the pawn
	//   - The new tile is empty
	//   - The tile directly in front of the pawn is empty
	//   - It is still the pawns first move (located in starting row)

	if(
		*arrayIndexPiece - *arrayIndexMove == twoTilesInfront 
		&& strcmp(gameBoard[*arrayIndexMove], "O ") == 0
		&& strcmp(gameBoard[*arrayIndexMove + oneTileInfront], "O ") == 0  
		&& rowStart < *arrayIndexPiece && *arrayIndexPiece < rowEnd){ 

		// Updates the gameBoard to show movement foward of 2 tiles.
		strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
		strcpy(gameBoard[*arrayIndexPiece], "O ");
		//Indicates the a succesful move and changes players turn.
		*valid_move_flag = 1;
		*turn += 1;
	}
}

void checkFowardOnePawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int oneTileInfront, int* valid_move_flag, int* turn){
	
	// Checks that all the following criteria are met:
	//   - The new tile is 1 space directly in front of the pawn
	//   - The tile directly in front of the pawn is empty

	if(
		*arrayIndexPiece - *arrayIndexMove == oneTileInfront 
		&& strcmp(gameBoard[*arrayIndexMove], "O ") == 0){ 
		
		// Updates the gameBoard to show movement foward of 1 tile.
		strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
		strcpy(gameBoard[*arrayIndexPiece], "O ");
		//Indicates the a succesful move and changes players turn.
		*valid_move_flag = 1;
		*turn += 1;
	}
}

void checkDiagonalsPawn(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int rowLocation, int oneTileInDiagonal, 
	char opposingTeam, int* valid_move_flag, int* turn){

	// Checks that all the following criteria are met:
	//   - The piece is located in a specfied row (necessary to handle cases 
	//	   of diagonal movment from the edge columns)
	//   - The new tile is 1 space directly diagonal in front of the pawn
	//   - The new tile contains a piece of the opponents

	if(
		(*arrayIndexPiece + rowLocation) % 8  == 0 
		&& *arrayIndexPiece - *arrayIndexMove == oneTileInDiagonal
	 	&& gameBoard[*arrayIndexMove][0] == opposingTeam){
		
		// Updates the gameBoard to show movement diagonally foward of 1 tile.
		strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
		strcpy(gameBoard[*arrayIndexPiece], "O ");
		//Indicates the a succesful move and changes players turn.
		*valid_move_flag = 1;
		*turn += 1;
	}
}

void movePawn(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove, 
	int* valid_move_flag, int* turn){
	// If the selected pawn is white's.
	if(gameBoard[*arrayIndexPiece][0] == 'W'){
		// Check if the pawn has been moved forward two spaces with the inputs:
		//   - 16, represents two tiles directly foward in the array
		//   - 8, represents one tile directly foward in the array
		//   - 47 and 56, represents row 2 on the board, starting position for 
		//	   white pawns
		checkFowardTwoPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
			16, 8, 47, 56, valid_move_flag, turn);

		// Checks if the pawn has moved foward one space with 8 representing one 
		// tile directly foward in the array
		checkFowardOnePawn(gameBoard, arrayIndexPiece, arrayIndexMove, 8,
			valid_move_flag, turn);
		
		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 0, represent that the selected piece is in the left most column
		//   - 7, represents on tile diagonally right in the array
		//   - B, represents that the opposition team is black  
		checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 0, 7,
			'B', valid_move_flag, turn);
		
		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 2-8, represents the selected piece is not on the edge of the board, 
		//     doesn't include 1 as that represents the right most column
		//   - Other inputs are same as above
		for (int rowLocation = 2; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
				rowLocation, 7, 'B', valid_move_flag, turn);
		}

		// Checks if the selected piece has moved diagonally left with the inputs:
		//   - 1-8, represent that the selected piece isn't is the left most column
		//     doesn't include 0 as that represents the left most column
		//   - 9, represents on tile diagonally left in the array
		//   - B, represents that the opposition team is black  
		for (int rowLocation = 1; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
				rowLocation, 9, 'B', valid_move_flag, turn);
		}		
	}
	
	// If the selected pawn is black's.
	else{
		// Check if the pawn has been moved forward two spaces with the inputs:
		//   - -16, represents two tiles directly foward in the array
		//   - -8, represents one tile directly foward in the array
		//   - 7 and 16, represents row 2 on the board, starting position for 
		//	   white pawns
		checkFowardTwoPawn(gameBoard, arrayIndexPiece, arrayIndexMove,
			-16, -8, 7, 16, valid_move_flag, turn);
		
		// Checks if the pawn has moved foward one space with -8 representing one 
		// tile directly foward in the array
		checkFowardOnePawn(gameBoard, arrayIndexPiece, arrayIndexMove, -8,
			valid_move_flag, turn);

		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 0, represent that the selected piece is in the left most column
		//   - -9, represents on tile diagonally right in the array
		//   - W, represents that the opposition team is white  
		checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 0, -9, 
			'W', valid_move_flag, turn);
		
		// Checks if the selected piece has moved diagonally right with the inputs:
		//   - 2-8, represents the selected piece is not on the edge of the board, 
		//     doesn't include 1 as that represents the right most column
		//   - Other inputs are same as above
		for (int rowLocation = 2; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
				rowLocation, -9, 'W', valid_move_flag, turn);
		}

		// Checks if the selected piece has moved diagonally left with the inputs:
		//   - 1-8, represent that the selected piece isn't is the left most column
		//     doesn't include 0 as that represents the left most column
		//   - -7, represents on tile diagonally left in the array
		//   - W, represents that the opposition team is white
		for (int rowLocation = 1; rowLocation < 8; ++rowLocation){
			checkDiagonalsPawn(gameBoard, arrayIndexPiece, arrayIndexMove, 
				rowLocation, -7, 'W', valid_move_flag, turn);
		}		
	}
}

void checkVerticalRook(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int direction, int* valid_move_flag, int* turn){
	
	// Initialises variables to count the number of succesful iterations 
	// through the loop, the number of spaces between positions and the character
	// representing the opposing team.
	int count = 0; 
	int numberOfSpaces;
	char opposingTeam;

	// If its white's turn, sets the opposing team to black and vice versa.
	if(gameBoard[*arrayIndexPiece][0] == 'W'){
		opposingTeam = 'B';
	}else{
		opposingTeam = 'W';
	}

	// If the new position is in the same column as the current position.
	if((*arrayIndexPiece - *arrayIndexMove) % 8 == 0){
		// Calculates the number of spaces vertically between the two positions.
		numberOfSpaces = abs((*arrayIndexPiece - *arrayIndexMove)/8);

		// Checks that every space between the two positions (not including them) 
		// is empty.
		for(int i = 0; i < numberOfSpaces - 1; ++i){
			if(strcmp(gameBoard[*arrayIndexPiece + (direction * (i + 1))],"O ") == 0){
				count += 1;
			}
		}

		// If every space between the two positions is empty and the new position
		// is empty or contains an opposition piece.
		if((count == numberOfSpaces - 1) && ((strcmp(gameBoard[*arrayIndexMove],
		 "O ") == 0) || (gameBoard[*arrayIndexMove][0] == opposingTeam))){

			// Move the rook to the new position and leave the old position empty.
			strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
			strcpy(gameBoard[*arrayIndexPiece], "O ");
			//Indicates the a succesful move and changes players turn.
			*valid_move_flag = 1;
			*turn += 1;
		}
	}
}

void checkHorizontalRook(char gameBoard[64][3], int* arrayIndexPiece, 
	int* arrayIndexMove, int direction, int* valid_move_flag, int* turn){

	// Initialises variables to count the number of succesful iterations 
	// through the loop, the number of spaces between positions and the character
	// representing the opposing team.
	int count = 0;
	int numberOfSpaces = abs(*arrayIndexPiece - *arrayIndexMove);;
	char opposingTeam;
	
	// If its white's turn, sets the opposing team to black and vice versa.
	if(gameBoard[*arrayIndexPiece][0] == 'W'){
		opposingTeam = 'B';
	}else{
		opposingTeam = 'W';
	}

	// If the new position is in the same row as the current position. 
	if((numberOfSpaces < 8) && (*arrayIndexPiece/8 == *arrayIndexMove/8)){
		// Checks that every space between the two positions (not including them) 
		// is empty.
		for(int i = 0; i < numberOfSpaces - 1; ++i){
			if(strcmp(gameBoard[*arrayIndexPiece + (direction * (i + 1))],"O ") == 0){
				count += 1;
			}
		}

		// If every space between the two positions is empty and the new position
		// is empty or contains an opposition piece.
		if((count == numberOfSpaces - 1) && ((strcmp(gameBoard[*arrayIndexMove],
		 "O ") == 0) || (gameBoard[*arrayIndexMove][0] == opposingTeam))){

			// Checks if the player is attempting to move between column A and G
			// by moving only one space in the array. This means they are 
			// attempting to loop around the board array. 
			if(!((abs(*arrayIndexPiece - *arrayIndexMove) == 1) &&
			 ((((*arrayIndexPiece - 7) % 8 == 0) && (*arrayIndexMove % 8 == 0)) 
			 ||(((*arrayIndexMove - 7) % 8 == 0) && (*arrayIndexPiece % 8 == 0))))){
				
				// Move the rook to the new position and leave the old position empty.
				strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
				strcpy(gameBoard[*arrayIndexPiece], "O ");
				//Indicates the a succesful move and changes players turn.
				*valid_move_flag = 1;
				*turn += 1;
			}	
		}	
	}
}

void moveRook(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove, 
	int* valid_move_flag, int* turn){
	// If the player is moving north or west on the board.
	if(*arrayIndexMove < *arrayIndexPiece){
		// Checks if a valid vertical move has been attempted.
		checkVerticalRook(gameBoard, arrayIndexPiece, arrayIndexMove, -8, 
			valid_move_flag, turn);
		// Checks if a valid horizontal move has been attempted.
		checkHorizontalRook(gameBoard, arrayIndexPiece, arrayIndexMove, -1, 
			valid_move_flag, turn);
	}

	// If the player is moving south or east on the board. 
	else{
		// Checks if a valid vertical move has been attempted.
		checkVerticalRook(gameBoard, arrayIndexPiece, arrayIndexMove, 8, 
			valid_move_flag, turn);
		// Checks if a valid horizontal move has been attempted.
		checkHorizontalRook(gameBoard, arrayIndexPiece, arrayIndexMove, 1, 
			valid_move_flag, turn);
	}
}

void moveKnight(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove, 
	int* valid_move_flag, int* turn){
	// Intialises and computes the number of tiles in the array between the 
	// current and new position. Also intalises a character to represent
	//  the opposition team.
	int tileDifference = abs(*arrayIndexMove - *arrayIndexPiece);
	char opposingTeam;

	// If its white's turn, sets the opposing team to black and vice versa.
	if(gameBoard[*arrayIndexPiece][0] == 'W'){
		opposingTeam = 'B';
	}else{
		opposingTeam = 'W';
	}

	// If the new position is located in one of the 8 potentially valid places 
	// for the knight's movement.
	if((tileDifference == 17) || (tileDifference == 15) || (tileDifference == 10) ||
	 (tileDifference == 6)){
		
		// If the new position is empty or contains an opposition piece. 
		if(((strcmp(gameBoard[*arrayIndexMove],"O ") == 0) || 
			(gameBoard[*arrayIndexMove][0] == opposingTeam))){
			
			// Move the knight to the new position and leave the old position 
			// empty.
			strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
			strcpy(gameBoard[*arrayIndexPiece], "O ");
			//Indicates the a succesful move and changes players turn.
			*valid_move_flag = 1;
			*turn += 1;
		}
	}
}

void checkBishopMove(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove,
 int verticalDirection, int* valid_move_flag, int* turn){
	// Intialises: 
	//  - The number of tiles in the array between the new and current position
	//  - A character to represent the opposition team
	//  - The number of spaces the bishop travels on the board
	//  - The horizontal direction the bishop travels in
	//  - An integer to count the number of succesful iterations of the foor loop
	int tileDifference = abs(*arrayIndexMove - *arrayIndexPiece);
	char opposingTeam;
	int numberOfSpaces;
	int Horizontaldirection;
	int count = 0;

	// If its white's turn, sets the opposing team to black and vice versa.
	if(gameBoard[*arrayIndexPiece][0] == 'W'){
		opposingTeam = 'B';
	}else{
		opposingTeam = 'W';
	}

	// If the new position is located along the diagonal paths.
	if(((tileDifference % 7) == 0) || ((tileDifference % 9) == 0)){
		// Determines how many spaces diagonally the bishop will travel and in 
		// which direction.
		if((tileDifference % 7) ==0){
			numberOfSpaces = tileDifference / 7;
			Horizontaldirection = 7;
		}

		else{
			numberOfSpaces = tileDifference / 9;
			Horizontaldirection = 9;
		}

		// Checks that every space between the two positions (not including them) 
		// is empty.
		for(int i = 1; i < numberOfSpaces; ++i){
			if(strcmp(gameBoard[*arrayIndexPiece + (i * Horizontaldirection * 
				verticalDirection)], "O ") == 0){
				
				count += 1;
			}
		}

		// If every space between the two positions is empty and the new position
		// is empty or contains an opposition piece.
		if((count + 1 == numberOfSpaces) && ((strcmp(gameBoard[*arrayIndexMove],"O ") == 0) 
			|| (gameBoard[*arrayIndexMove][0] == opposingTeam))){
			
			// Move the bishop to the new position and leave the old position 
			// empty.
			strcpy(gameBoard[*arrayIndexMove], gameBoard[*arrayIndexPiece]);
			strcpy(gameBoard[*arrayIndexPiece], "O ");
			//Indicates the a succesful move and changes players turn.
			*valid_move_flag = 1;
			*turn += 1;
		}
	}
}

void moveBishop(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove, 
	int* valid_move_flag, int* turn){
	// If the bishop is moving diagonally north on the board.
	if(*arrayIndexMove < *arrayIndexPiece){
		checkBishopMove(gameBoard, arrayIndexPiece, arrayIndexMove, -1, 
			valid_move_flag, turn);
	}

	// If the bishop is moving diagonally south on the board.
	else{
		checkBishopMove(gameBoard, arrayIndexPiece, arrayIndexMove, 1, 
			valid_move_flag, turn);
	}
}

void moveQueen(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove, 
	int* valid_move_flag, int* turn){
	if(*arrayIndexMove < *arrayIndexPiece){
		// Checks if a valid vertical move has been attempted.
		checkVerticalRook(gameBoard, arrayIndexPiece, arrayIndexMove, -8, 
			valid_move_flag, turn);
		// Checks if a valid horizontal move has been attempted.
		checkHorizontalRook(gameBoard, arrayIndexPiece, arrayIndexMove, -1, 
			valid_move_flag, turn);
		// Checks if a valid diagonal move has been attempted.
		checkBishopMove(gameBoard, arrayIndexPiece, arrayIndexMove, -1, 
			valid_move_flag, turn);
	}

	else{
		// Checks if a valid vertical move has been attempted.
		checkVerticalRook(gameBoard, arrayIndexPiece, arrayIndexMove, 8, 
			valid_move_flag, turn);
		// Checks if a valid horizontal move has been attempted.
		checkHorizontalRook(gameBoard, arrayIndexPiece, arrayIndexMove, 1, 
			valid_move_flag, turn);
		// Checks if a valid diagonal move has been attempted.
		checkBishopMove(gameBoard, arrayIndexPiece, arrayIndexMove, 1, 
			valid_move_flag, turn);	
	}
}

void moveKing(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove, 
	int* valid_move_flag, int* turn){
	// Intialises an integer to represent the number of tiles in the array the 
	// king travels.
	int tileDifference = abs(*arrayIndexMove - *arrayIndexPiece);

	// If the new position is located in one of the 8 potentially valid places 
	// for the king's movement.
	if((tileDifference == 1) || (tileDifference == 7) || (tileDifference == 8) 
		|| (tileDifference == 9)){
		
		// Check if the movement was valid in any direction but only 1 tile away.
		moveQueen(gameBoard, arrayIndexPiece, arrayIndexMove, valid_move_flag,
			turn);
	}
}

void deselectPiece(char gameBoard[64][3], int* arrayIndexPiece, int* arrayIndexMove, 
	int* valid_move_flag){
	
	// If the piece has been selected again, deslect it and indicate a move has
	// happened, allowing the user to selct a new piece.
	if(*arrayIndexMove - *arrayIndexPiece == 0){
		printf("\nPiece deselected.\n\n");
		*valid_move_flag = 1;
	}
}